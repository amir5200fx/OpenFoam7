#include <probes.hxx>

#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <IOmanip.hxx>
#include <interpolation.hxx>
#include <probesIsNotEqOp.h>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

//namespace tnbLib
//{
//
//	template<class T>
//	class isNotEqOp
//	{
//	public:
//
//		void operator()(T& x, const T& y) const
//		{
//			const T unsetVal(-vGreat * pTraits<T>::one);
//
//			if (x != unsetVal)
//			{
//				// Keep x.
//
//				// Note: should check for y != unsetVal but multiple sample cells
//				// already handled in read().
//			}
//			else
//			{
//				// x is not set. y might be.
//				x = y;
//			}
//		}
//	};
//
//}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class Type>
void tnbLib::probes::sampleAndWrite
(
	const GeometricField<Type, fvPatchField, volMesh>& vField
)
{
	Field<Type> values(sample(vField));

	if (Pstream::master())
	{
		unsigned int w = IOstream::defaultPrecision() + 7;
		OFstream& os = *probeFilePtrs_[vField.name()];

		os << setw(w) << vField.time().timeToUserTime(vField.time().value());

		forAll(values, probei)
		{
			os << ' ' << setw(w) << values[probei];
		}
		os << endl;
	}
}


template<class Type>
void tnbLib::probes::sampleAndWrite
(
	const GeometricField<Type, fvsPatchField, surfaceMesh>& sField
)
{
	Field<Type> values(sample(sField));

	if (Pstream::master())
	{
		unsigned int w = IOstream::defaultPrecision() + 7;
		OFstream& os = *probeFilePtrs_[sField.name()];

		os << setw(w) << sField.time().timeToUserTime(sField.time().value());

		forAll(values, probei)
		{
			os << ' ' << setw(w) << values[probei];
		}
		os << endl;
	}
}


template<class Type>
void tnbLib::probes::sampleAndWrite(const fieldGroup<Type>& fields)
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
void tnbLib::probes::sampleAndWriteSurfaceFields(const fieldGroup<Type>& fields)
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
tnbLib::probes::sample
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

	if (fixedLocations_)
	{
		autoPtr<interpolation<Type>> interpolator
		(
			interpolation<Type>::New(interpolationScheme_, vField)
		);

		forAll(*this, probei)
		{
			if (elementList_[probei] >= 0)
			{
				const vector& position = operator[](probei);

				values[probei] = interpolator().interpolate
				(
					position,
					elementList_[probei],
					-1
				);
			}
		}
	}
	else
	{
		forAll(*this, probei)
		{
			if (elementList_[probei] >= 0)
			{
				values[probei] = vField[elementList_[probei]];
			}
		}
	}

	Pstream::listCombineGather(values, isNotEqOp<Type>());
	Pstream::listCombineScatter(values);

	return tValues;
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::probes::sample(const word& fieldName) const
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
tnbLib::probes::sample
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

	forAll(*this, probei)
	{
		if (faceList_[probei] >= 0)
		{
			values[probei] = sField[faceList_[probei]];
		}
	}

	Pstream::listCombineGather(values, isNotEqOp<Type>());
	Pstream::listCombineScatter(values);

	return tValues;
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::probes::sampleSurfaceFields(const word& fieldName) const
{
	return sample
	(
		mesh_.lookupObject<GeometricField<Type, fvsPatchField, surfaceMesh>>
		(
			fieldName
			)
	);
}

// ************************************************************************* //