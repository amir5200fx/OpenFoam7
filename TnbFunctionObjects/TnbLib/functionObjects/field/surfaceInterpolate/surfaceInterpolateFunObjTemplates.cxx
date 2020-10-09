#include <surfaceInterpolateFunObj.hxx>

#include <volFields.hxx>
#include <linear.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type>
void tnbLib::functionObjects::surfaceInterpolate::interpolateFields
(
	PtrList<GeometricField<Type, fvsPatchField, surfaceMesh>>& sflds
) const
{
	typedef GeometricField<Type, fvPatchField, volMesh> VolFieldType;
	typedef GeometricField<Type, fvsPatchField, surfaceMesh> SurfaceFieldType;

	// Convert field to map
	HashTable<word> fieldMap(2 * fieldSet_.size());
	forAll(fieldSet_, i)
	{
		fieldMap.insert(fieldSet_[i].first(), fieldSet_[i].second());
	}


	HashTable<const VolFieldType*> flds(obr_.lookupClass<VolFieldType>());

	forAllConstIter(typename HashTable<const VolFieldType*>, flds, iter)
	{
		const VolFieldType& fld = *iter();

		if (fieldMap.found(fld.name()))
		{
			// const word sName = "interpolate(" + fld.name() + ')';
			const word& sName = fieldMap[fld.name()];

			if (obr_.found(sName))
			{
				Info << "        surface field " << sName << " already exists"
					<< endl;
			}
			else
			{
				label sz = sflds.size();
				sflds.setSize(sz + 1);
				sflds.set
				(
					sz,
					new SurfaceFieldType(sName, linearInterpolate(fld))
				);

				Info << "        interpolated " << fld.name() << " to create "
					<< sflds[sz].name() << endl;
			}
		}
	}
}


// ************************************************************************* //