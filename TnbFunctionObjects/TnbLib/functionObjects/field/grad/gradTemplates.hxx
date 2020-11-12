#pragma once

// .cxx

#include <fvcGrad.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class Type>
bool tnbLib::functionObjects::grad::calcGrad()
{
	typedef GeometricField<Type, fvPatchField, volMesh> VolFieldType;
	typedef GeometricField<Type, fvsPatchField, surfaceMesh> SurfaceFieldType;

	if (foundObject<VolFieldType>(fieldName_))
	{
		return store
		(
			resultName_,
			fvc::grad(lookupObject<VolFieldType>(fieldName_)),
			mesh_.changing() && mesh_.cache(resultName_)
		);
	}
	else if (foundObject<SurfaceFieldType>(fieldName_))
	{
		return store
		(
			resultName_,
			fvc::grad(lookupObject<SurfaceFieldType>(fieldName_)),
			mesh_.changing() && mesh_.cache(resultName_)
		);
	}
	else
	{
		return false;
	}
}


// ************************************************************************* //