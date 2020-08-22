#include <patchProbes.hxx>

#include <volFields.hxx>
#include <IOmanip.hxx>
#include <probesIsNotEqOp.h>  // added by amir

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class Type>
void tnbLib::patchProbes::sampleAndWrite
(
	const GeometricField<Type, fvPatchField, volMesh>& vField
)
{
	Field<Type> values(sample(vField));

	if (Pstream::master())
	{
		unsigned int w = IOstream::defaultPrecision() + 7;
		OFstream& probeStream = *probeFilePtrs_[vField.name()];

		probeStream
			<< setw(w)
			<< vField.time().timeToUserTime(vField.time().value());

		forAll(values, probei)
		{
			probeStream << ' ' << setw(w) << values[probei];
		}
		probeStream << endl;
	}
}


template<class Type>
void tnbLib::patchProbes::sampleAndWrite
(
	const GeometricField<Type, fvsPatchField, surfaceMesh>& sField
)
{
	Field<Type> values(sample(sField));

	if (Pstream::master())
	{
		unsigned int w = IOstream::defaultPrecision() + 7;
		OFstream& probeStream = *probeFilePtrs_[sField.name()];

		probeStream
			<< setw(w)
			<< sField.time().timeToUserTime(sField.time().value());

		forAll(values, probei)
		{
			probeStream << ' ' << setw(w) << values[probei];
		}
		probeStream << endl;
	}
}


template<class Type>
void tnbLib::patchProbes::sampleAndWrite
(
	const fieldGroup<Type>& fields
)
{
	forAll(fields, fieldi)
	{
		if (loadFromFiles_)
		{
			sampleAndWrite
			(
				GeometricField<Type, fvPatchField, volMesh>
				(
					IOobject
					(
						fields[fieldi],
						mesh_.time().timeName(),
						mesh_,
						IOobject::MUST_READ,
						IOobject::NO_WRITE,
						false
					),
					mesh_
					)
			);
		}
		else
		{
			objectRegistry::const_iterator iter = mesh_.find(fields[fieldi]);

			if
				(
					iter != objectRegistry::end()
					&& iter()->type()
					== GeometricField<Type, fvPatchField, volMesh>::typeName
					)
			{
				sampleAndWrite
				(
					mesh_.lookupObject
					<GeometricField<Type, fvPatchField, volMesh>>
					(
						fields[fieldi]
						)
				);
			}
		}
	}
}


template<class Type>
void tnbLib::patchProbes::sampleAndWriteSurfaceFields
(
	const fieldGroup<Type>& fields
)
{
	forAll(fields, fieldi)
	{
		if (loadFromFiles_)
		{
			sampleAndWrite
			(
				GeometricField<Type, fvsPatchField, surfaceMesh>
				(
					IOobject
					(
						fields[fieldi],
						mesh_.time().timeName(),
						mesh_,
						IOobject::MUST_READ,
						IOobject::NO_WRITE,
						false
					),
					mesh_
					)
			);
		}
		else
		{
			objectRegistry::const_iterator iter = mesh_.find(fields[fieldi]);

			if
				(
					iter != objectRegistry::end()
					&& iter()->type()
					== GeometricField<Type, fvsPatchField, surfaceMesh>::typeName
					)
			{
				sampleAndWrite
				(
					mesh_.lookupObject
					<GeometricField<Type, fvsPatchField, surfaceMesh>>
					(
						fields[fieldi]
						)
				);
			}
		}
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::patchProbes::sample
(
	const GeometricField<Type, fvPatchField, volMesh>& vField
) const
{
	const Type unsetVal(-vGreat * pTraits<Type>::one);

	tmp<Field<Type>> tValues
	(
		new Field<Type>(this->size(), unsetVal)
	);

	Field<Type>& values = tValues.ref();

	const polyBoundaryMesh& patches = mesh_.boundaryMesh();

	forAll(*this, probei)
	{
		label facei = elementList_[probei];

		if (facei >= 0)
		{
			label patchi = patches.whichPatch(facei);
			label localFacei = patches[patchi].whichFace(facei);
			values[probei] = vField.boundaryField()[patchi][localFacei];
		}
	}

	Pstream::listCombineGather(values, isNotEqOp<Type>());
	Pstream::listCombineScatter(values);

	return tValues;
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::patchProbes::sample(const word& fieldName) const
{
	return sample
	(
		mesh_.lookupObject<GeometricField<Type, fvPatchField, volMesh>>
		(
			fieldName
			)
	);
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::patchProbes::sample
(
	const GeometricField<Type, fvsPatchField, surfaceMesh>& sField
) const
{
	const Type unsetVal(-vGreat * pTraits<Type>::one);

	tmp<Field<Type>> tValues
	(
		new Field<Type>(this->size(), unsetVal)
	);

	Field<Type>& values = tValues.ref();

	const polyBoundaryMesh& patches = mesh_.boundaryMesh();

	forAll(*this, probei)
	{
		label facei = elementList_[probei];

		if (facei >= 0)
		{
			label patchi = patches.whichPatch(facei);
			label localFacei = patches[patchi].whichFace(facei);
			values[probei] = sField.boundaryField()[patchi][localFacei];
		}
	}

	Pstream::listCombineGather(values, isNotEqOp<Type>());
	Pstream::listCombineScatter(values);

	return tValues;
}
// ************************************************************************* //