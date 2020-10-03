#include <components.hxx>

#include <volFields.hxx>
#include <surfaceFields.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class GeoFieldType>
bool tnbLib::functionObjects::components::calcFieldComponents()
{
	typedef typename GeoFieldType::value_type Type;

	const GeoFieldType& field(lookupObject<GeoFieldType>(fieldName_));

	resultNames_.setSize(Type::nComponents);

	bool stored = true;

	for (direction i = 0; i < Type::nComponents; i++)
	{
		resultName_ = fieldName_ + word(Type::componentNames[i]);
		resultNames_[i] = resultName_;

		stored = stored && store(resultName_, field.component(i));
	}

	return stored;
}


template<class Type>
bool tnbLib::functionObjects::components::calcComponents()
{
	typedef GeometricField<Type, fvPatchField, volMesh> VolFieldType;
	typedef GeometricField<Type, fvsPatchField, surfaceMesh> SurfaceFieldType;

	if (foundObject<VolFieldType>(fieldName_))
	{
		return calcFieldComponents<VolFieldType>();
	}
	else if (foundObject<SurfaceFieldType>(fieldName_))
	{
		return calcFieldComponents<SurfaceFieldType>();
	}
	else
	{
		return false;
	}
}


// ************************************************************************* //