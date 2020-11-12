#include <magSqr.hxx>

//#include <volFields.hxx>
//#include <surfaceFields.hxx>
//
//// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //
//
//template<class Type>
//bool tnbLib::functionObjects::magSqr::calcMagSqr()
//{
//	typedef GeometricField<Type, fvPatchField, volMesh> VolFieldType;
//	typedef GeometricField<Type, fvsPatchField, surfaceMesh> SurfaceFieldType;
//
//	if (foundObject<VolFieldType>(fieldName_))
//	{
//		return store
//		(
//			resultName_,
//			tnbLib::magSqr(lookupObject<VolFieldType>(fieldName_))
//		);
//	}
//	else if (foundObject<SurfaceFieldType>(fieldName_))
//	{
//		return store
//		(
//			resultName_,
//			tnbLib::magSqr(lookupObject<SurfaceFieldType>(fieldName_))
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