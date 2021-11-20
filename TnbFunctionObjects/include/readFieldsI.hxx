#pragma once
#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <Time.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type>
void tnbLib::functionObjects::readFields::loadField
(
	const word& fieldName,
	PtrList<GeometricField<Type, fvPatchField, volMesh>>& vflds,
	PtrList<GeometricField<Type, fvsPatchField, surfaceMesh>>& sflds
) const
{
	typedef GeometricField<Type, fvPatchField, volMesh> VolFieldType;
	typedef GeometricField<Type, fvsPatchField, surfaceMesh> SurfaceFieldType;

	if (obr_.foundObject<VolFieldType>(fieldName))
	{
		DebugInfo
			<< "readFields : Field " << fieldName << " already in database"
			<< endl;
	}
	else if (obr_.foundObject<SurfaceFieldType>(fieldName))
	{
		DebugInfo
			<< "readFields : Field " << fieldName
			<< " already in database" << endl;
	}
	else
	{
		tnbLib::IOobject fieldHeader
		(
			fieldName,
			mesh_.time().timeName(),
			mesh_,
			tnbLib::IOobject::MUST_READ,
			tnbLib::IOobject::NO_WRITE
		);

		if
			(
				fieldHeader.typeHeaderOk<VolFieldType>(false)
				&& fieldHeader.headerClassName() == VolFieldType::typeName
				)
		{
			// Store field locally
			TnbLog << "    Reading " << fieldName << endl;

			label sz = vflds.size();
			vflds.setSize(sz + 1);
			vflds.set(sz, new VolFieldType(fieldHeader, mesh_));
		}
		else if
			(
				fieldHeader.typeHeaderOk<SurfaceFieldType>(false)
				&& fieldHeader.headerClassName() == SurfaceFieldType::typeName
				)
		{
			// Store field locally
			TnbLog << "    Reading " << fieldName << endl;

			label sz = sflds.size();
			sflds.setSize(sz + 1);
			sflds.set(sz, new SurfaceFieldType(fieldHeader, mesh_));
		}
	}
}


// ************************************************************************* //