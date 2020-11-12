#pragma once

// .cxx

#include <fvcDdt.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class Type>
bool tnbLib::functionObjects::ddt::calcDdt()
{
	typedef GeometricField<Type, fvPatchField, volMesh> VolFieldType;

	if (foundObject<VolFieldType>(fieldName_))
	{
		return store
		(
			resultName_,
			fvc::ddt(lookupObject<VolFieldType>(fieldName_))
		);
	}
	else
	{
		return false;
	}
}


// ************************************************************************* //