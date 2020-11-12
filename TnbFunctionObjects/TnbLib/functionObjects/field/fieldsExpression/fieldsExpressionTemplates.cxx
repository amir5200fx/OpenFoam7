#include <fieldsExpression.hxx>

//#include <volFields.hxx>
//#include <surfaceFields.hxx>
//
//// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //
//
//template<class Type, class FOType>
//bool tnbLib::functionObjects::fieldsExpression::calcFieldTypes(FOType& fo)
//{
//	typedef GeometricField<Type, fvPatchField, volMesh> VolFieldType;
//	typedef GeometricField<Type, fvsPatchField, surfaceMesh> SurfaceFieldType;
//
//	if (foundObject<VolFieldType>(fieldNames_[0]))
//	{
//		return store
//		(
//			resultName_,
//			fo.template calcFieldType<VolFieldType>()
//		);
//	}
//	else if (foundObject<SurfaceFieldType>(fieldNames_[0]))
//	{
//		return store
//		(
//			resultName_,
//			fo.template calcFieldType<SurfaceFieldType>()
//		);
//	}
//	else
//	{
//		return false;
//	}
//}
//
//
//template<class Type, class FOType>
//bool tnbLib::functionObjects::fieldsExpression::calcType(FOType& fo)
//{
//	return calcFieldTypes<Type>(fo);
//}
//
//
//template<class FOType>
//bool tnbLib::functionObjects::fieldsExpression::calcAllTypes(FOType& fo)
//{
//	bool processed = false;
//
//	processed = processed || fo.template calcType<scalar>(fo);
//	processed = processed || fo.template calcType<vector>(fo);
//	processed = processed || fo.template calcType<sphericalTensor>(fo);
//	processed = processed || fo.template calcType<symmTensor>(fo);
//	processed = processed || fo.template calcType<tensor>(fo);
//
//	return processed;
//}
//
//
//// ************************************************************************* //