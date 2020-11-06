#include <PstreamHelper.hxx>

#include <OPstream.hxx>
#include <IPstream.hxx>

#include <bool.hxx>
#include <label.hxx>
#include <scalar.hxx>
#include <vector.hxx>
#include <sphericalTensor.hxx>
#include <symmTensor.hxx>
#include <tensor.hxx>
#include <triad.hxx>
#include <fileName.hxx>

tnbLib::IPstream 
tnbLib::CreateIPstream
(
	const int toProcNo,
	const label bufSize,
	const int tag,
	const label comm
)
{
	IPstream s
	(
		UPstream::commsTypes::scheduled,
		toProcNo,
		bufSize,
		tag,
		comm
	);
	return std::move(s);
}

tnbLib::OPstream 
tnbLib::CreateOPstream
(
	const int toProcNo,
	const label bufSize, 
	const int tag,
	const label comm
)
{
	OPstream s
	(
		UPstream::commsTypes::scheduled,
		toProcNo,
		bufSize,
		tag,
		comm
	);
	return std::move(s);
}

//template<class T>
//void tnbLib::writeToOPstream
//(
//	const int toProcNo,
//	const label bufSize,
//	const int tag, 
//	const label comm, 
//	const T & Value
//)
//{
//	OPstream s
//	(
//		UPstream::commsTypes::scheduled,
//		toProcNo,
//		bufSize,
//		tag,
//		comm
//	);
//	s << Value;
//}
//
//template<class T>
//void tnbLib::writeToOPstream
//(
//	const int toProcNo,
//	const label bufSize,
//	const int tag, 
//	const label comm, 
//	const List<T>& Values
//)
//{
//	OPstream s
//	(
//		UPstream::commsTypes::scheduled,
//		toProcNo,
//		bufSize,
//		tag,
//		comm
//	);
//	s << Values;
//}
//
//template<class T>
//void tnbLib::readFromIPstream
//(
//	const int toProcNo,
//	const label bufSize, 
//	const int tag,
//	const label comm, 
//	T & Value
//)
//{
//	IPstream s
//	(
//		tnbLib::UPstream::commsTypes::scheduled,
//		toProcNo,
//		bufSize,
//		tag,
//		comm
//	);
//
//	s >> Value;
//}
//
//template<class T>
//void tnbLib::readFromIPstream
//(
//	const int toProcNo, 
//	const label bufSize, 
//	const int tag, 
//	const label comm, 
//	List<T>& Values
//)
//{
//	IPstream s
//	(
//		tnbLib::UPstream::commsTypes::scheduled,
//		toProcNo,
//		bufSize,
//		tag,
//		comm
//	);
//
//	s >> Values;
//}
//
//namespace tnbLib
//{
//	template<class T>
//	T readFromIPstream
//	(
//		const int toProcNo,
//		const label bufSize,
//		const int tag,
//		const label comm
//	)
//	{
//		IPstream s
//		(
//			tnbLib::UPstream::commsTypes::scheduled,
//			toProcNo,
//			bufSize,
//			tag,
//			comm
//		);
//
//		T value;
//		s >> value;
//		return std::move(value);
//	}
//}
//
//template<class T>
//tnbLib::List<T>
//tnbLib::readListFromIPstream
//(
//	const int toProcNo,
//	const label bufSize, 
//	const int tag, 
//	const label comm
//)
//{
//	IPstream s
//	(
//		tnbLib::UPstream::commsTypes::scheduled,
//		toProcNo,
//		bufSize,
//		tag,
//		comm
//	);
//
//	List<T> values(s);
//	return std::move(values);
//}
//
//#define writeToOPstreamIMPL(Type)  \
//	template void writeToOPstream<Type>(const int toProcNo, const label bufSize, const int tag, const label comm, const Type& Value);	\
//	template void writeToOPstream<Type>(const int toProcNo, const label bufSize, const int tag, const label comm, const List<Type>& Values)
//
//#define readFromIPstreamIMPL(Type) \
//	template void readFromIPstream<Type>(const int toProcNo, const label bufSize, const int tag, const label comm, Type& Value);	\
//	template void readFromIPstream<Type>(const int toProcNo, const label bufSize, const int tag, const label comm, List<Type>& Value);	\
//	template Type readFromIPstream<Type>(const int toProcNo, const label bufSize, const int tag, const label comm);	\
//	template List<Type> readListFromIPstream<Type>(const int toProcNo, const label bufSize, const int tag, const label comm)
//
//#include <instant.hxx>
//#include <vectorTensorTransform.hxx>
//#include <vectorField.hxx>
//#include <fieldTypes.hxx>
//
//namespace tnbLib
//{
//	writeToOPstreamIMPL(bool);
//	writeToOPstreamIMPL(int);
//	writeToOPstreamIMPL(unsigned);
//	writeToOPstreamIMPL(long);
//	writeToOPstreamIMPL(float);
//	writeToOPstreamIMPL(double);
//	writeToOPstreamIMPL(label);
//	writeToOPstreamIMPL(scalar);
//	writeToOPstreamIMPL(vector);
//	writeToOPstreamIMPL(Vector<double>);
//	writeToOPstreamIMPL(sphericalTensor);
//	writeToOPstreamIMPL(symmTensor);
//	writeToOPstreamIMPL(tensor);
//	writeToOPstreamIMPL(triad);
//	writeToOPstreamIMPL(string);
//	writeToOPstreamIMPL(word);
//	writeToOPstreamIMPL(fileName);
//	writeToOPstreamIMPL(instant);
//	writeToOPstreamIMPL(vectorTensorTransform);
//	writeToOPstreamIMPL(vectorField);
//	writeToOPstreamIMPL(labelField);
//
//	readFromIPstreamIMPL(bool);
//	readFromIPstreamIMPL(int);
//	readFromIPstreamIMPL(unsigned);
//	readFromIPstreamIMPL(long);
//	readFromIPstreamIMPL(float);
//	readFromIPstreamIMPL(double);
//	readFromIPstreamIMPL(label);
//	readFromIPstreamIMPL(scalar);
//	readFromIPstreamIMPL(vector);
//	readFromIPstreamIMPL(Vector<double>);
//	readFromIPstreamIMPL(sphericalTensor);
//	readFromIPstreamIMPL(symmTensor);
//	readFromIPstreamIMPL(tensor);
//	readFromIPstreamIMPL(triad);
//	readFromIPstreamIMPL(string);
//	readFromIPstreamIMPL(word);
//	readFromIPstreamIMPL(fileName);
//	readFromIPstreamIMPL(instant);
//	readFromIPstreamIMPL(vectorTensorTransform);
//	readFromIPstreamIMPL(vectorField);
//	readFromIPstreamIMPL(labelField);
//}