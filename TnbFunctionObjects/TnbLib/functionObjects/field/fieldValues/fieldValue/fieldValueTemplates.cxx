#include <fieldValue.hxx>

//#include <ListListOps.hxx>
//#include <Pstream.hxx>
//
//// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //
//
//template<class Type>
//void tnbLib::functionObjects::fieldValue::combineFields(Field<Type>& field)
//{
//	List<Field<Type>> allValues(Pstream::nProcs());
//
//	allValues[Pstream::myProcNo()] = field;
//
//	Pstream::gatherList(allValues);
//
//	if (Pstream::master())
//	{
//		field =
//			ListListOps::combine<Field<Type>>
//			(
//				allValues,
//				accessOp<Field<Type>>()
//				);
//	}
//}
//
//
//template<class Type>
//void tnbLib::functionObjects::fieldValue::combineFields(tmp<Field<Type>>& field)
//{
//	combineFields(field());
//}
//
//
//// ************************************************************************* //