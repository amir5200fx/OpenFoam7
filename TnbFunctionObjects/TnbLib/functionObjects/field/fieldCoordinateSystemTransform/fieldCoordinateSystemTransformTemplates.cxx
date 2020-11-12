#include <fieldCoordinateSystemTransform.hxx>

//#include <volFields.hxx>
//#include <surfaceFields.hxx>
//#include <transformGeometricField.hxx>
//
//// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //
//
//template<class FieldType>
//void tnbLib::functionObjects::fieldCoordinateSystemTransform::transformField
//(
//	const FieldType& field
//)
//{
//	word transFieldName(transformFieldName(field.name()));
//
//	store
//	(
//		transFieldName,
//		tnbLib::transform(dimensionedTensor(coordSys_.R().R()), field)
//	);
//}
//
//
//template<class Type>
//void tnbLib::functionObjects::fieldCoordinateSystemTransform::transform
//(
//	const word& fieldName
//)
//{
//	typedef GeometricField<Type, fvPatchField, volMesh> VolFieldType;
//	typedef GeometricField<Type, fvsPatchField, surfaceMesh> SurfaceFieldType;
//
//	if (mesh_.foundObject<VolFieldType>(fieldName))
//	{
//		DebugInfo
//			<< type() << ": Field " << fieldName << " already in database"
//			<< endl;
//
//		transformField<VolFieldType>
//			(
//				mesh_.lookupObject<VolFieldType>(fieldName)
//				);
//	}
//	else if (mesh_.foundObject<SurfaceFieldType>(fieldName))
//	{
//		DebugInfo
//			<< type() << ": Field " << fieldName << " already in database"
//			<< endl;
//
//		transformField<SurfaceFieldType>
//			(
//				mesh_.lookupObject<SurfaceFieldType>(fieldName)
//				);
//	}
//	else
//	{
//		IOobject fieldHeader
//		(
//			fieldName,
//			mesh_.time().timeName(),
//			mesh_,
//			IOobject::MUST_READ,
//			IOobject::NO_WRITE
//		);
//
//		if
//			(
//				fieldHeader.typeHeaderOk<VolFieldType>(false)
//				&& fieldHeader.headerClassName() == VolFieldType::typeName
//				)
//		{
//			DebugInfo
//				<< type() << ": Field " << fieldName << " read from file"
//				<< endl;
//
//			transformField<VolFieldType>
//				(
//					mesh_.lookupObject<VolFieldType>(fieldName)
//					);
//		}
//		else if
//			(
//				fieldHeader.typeHeaderOk<SurfaceFieldType>(false)
//				&& fieldHeader.headerClassName() == SurfaceFieldType::typeName
//				)
//		{
//			DebugInfo
//				<< type() << ": Field " << fieldName << " read from file"
//				<< endl;
//
//			transformField<SurfaceFieldType>
//				(
//					mesh_.lookupObject<SurfaceFieldType>(fieldName)
//					);
//		}
//	}
//}
//
//
//// ************************************************************************* //