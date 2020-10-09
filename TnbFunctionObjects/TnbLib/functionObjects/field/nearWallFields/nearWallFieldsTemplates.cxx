#include <nearWallFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type>
void tnbLib::functionObjects::nearWallFields::createFields
(
	PtrList<GeometricField<Type, fvPatchField, volMesh>>& sflds
) const
{
	typedef GeometricField<Type, fvPatchField, volMesh> VolFieldType;

	HashTable<const VolFieldType*> flds(obr_.lookupClass<VolFieldType>());

	forAllConstIter(typename HashTable<const VolFieldType*>, flds, iter)
	{
		const VolFieldType& fld = *iter();

		if (fieldMap_.found(fld.name()))
		{
			const word& sampleFldName = fieldMap_[fld.name()];

			if (obr_.found(sampleFldName))
			{
				TnbLog << "    a field " << sampleFldName
					<< " already exists on the mesh."
					<< endl;
			}
			else
			{
				label sz = sflds.size();
				sflds.setSize(sz + 1);

				sflds.set
				(
					sz,
					new VolFieldType
					(
						IOobject
						(
							sampleFldName,
							time_.timeName(),
							mesh_
						),
						fld,
						calculatedFvPatchScalarField::typeName
					)
				);

				TnbLog << "    created " << sflds[sz].name()
					<< " to sample " << fld.name() << endl;
			}
		}
	}
}


template<class Type>
void tnbLib::functionObjects::nearWallFields::sampleBoundaryField
(
	const interpolationCellPoint<Type>& interpolator,
	GeometricField<Type, fvPatchField, volMesh>& fld
) const
{
	// Construct flat fields for all patch faces to be sampled
	Field<Type> sampledValues(getPatchDataMapPtr_().constructSize());

	forAll(cellToWalls_, celli)
	{
		const labelList& cData = cellToWalls_[celli];

		forAll(cData, i)
		{
			const point& samplePt = cellToSamples_[celli][i];
			sampledValues[cData[i]] = interpolator.interpolate(samplePt, celli);
		}
	}

	// Send back sampled values to patch faces
	getPatchDataMapPtr_().reverseDistribute
	(
		getPatchDataMapPtr_().constructSize(),
		sampledValues
	);

	typename GeometricField<Type, fvPatchField, volMesh>::
		Boundary& fldBf = fld.boundaryFieldRef();

	// Pick up data
	label nPatchFaces = 0;
	forAllConstIter(labelHashSet, patchSet_, iter)
	{
		label patchi = iter.key();

		fvPatchField<Type>& pfld = fldBf[patchi];

		Field<Type> newFld(pfld.size());
		forAll(pfld, i)
		{
			newFld[i] = sampledValues[nPatchFaces++];
		}

		pfld == newFld;
	}
}


template<class Type>
void tnbLib::functionObjects::nearWallFields::sampleFields
(
	PtrList<GeometricField<Type, fvPatchField, volMesh>>& sflds
) const
{
	typedef GeometricField<Type, fvPatchField, volMesh> VolFieldType;

	forAll(sflds, i)
	{
		const word& fldName = reverseFieldMap_[sflds[i].name()];
		const VolFieldType& fld = obr_.lookupObject<VolFieldType>(fldName);

		// Take over internal and boundary values
		sflds[i] == fld;

		// Construct interpolation method
		interpolationCellPoint<Type> interpolator(fld);

		// Override sampled values
		sampleBoundaryField(interpolator, sflds[i]);
	}
}


// ************************************************************************* //