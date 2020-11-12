#include <mag.hxx>

//#include <volFields.hxx>
//#include <surfaceFields.hxx>
//
//// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //
//
//template<class Type>
//bool tnbLib::functionObjects::mag::calcMag()
//{
//	typedef GeometricField<Type, fvPatchField, volMesh> VolFieldType;
//	typedef GeometricField<Type, fvsPatchField, surfaceMesh> SurfaceFieldType;
//
//	if (foundObject<VolFieldType>(fieldName_))
//	{
//		return store
//		(
//			resultName_,
//			tnbLib::mag(lookupObject<VolFieldType>(fieldName_))
//		);
//	}
//	else if (foundObject<SurfaceFieldType>(fieldName_))
//	{
//		return store
//		(
//			resultName_,
//			tnbLib::mag(lookupObject<SurfaceFieldType>(fieldName_))
//		);
//	}
//	else
//	{
//		return false;
//	}
//}
//
//
//// ************************************************************************* //