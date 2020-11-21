#pragma once
#ifndef _gatherScatterHelper_Header
#define _gatherScatterHelper_Header

#include <label.hxx>
#include <List.hxx>

namespace tnbLib
{

	class IPstream;
	class OPstream;

	FoamBase_EXPORT IPstream CreateIPstream(const int toProcNo, const label bufSize, const int tag, const label comm);

	FoamBase_EXPORT OPstream CreateOPstream(const int toProcNo, const label bufSize, const int tag, const label comm);

	template<class T>
	void writeToOPstream(const int toProcNo, const label bufSize, const int tag, const label comm, const T& Value);

	template<class T>
	void writeToOPstream(const int toProcNo, const label bufSize, const int tag, const label comm, const List<T>& Values);

	template<class T>
	void readFromIPstream(const int toProcNo, const label bufSize, const int tag, const label comm, T& Value);

	template<class T>
	void readFromIPstream(const int toProcNo, const label bufSize, const int tag, const label comm, List<T>& Values);

	template<class T>
	T readFromIPstream(const int toProcNo, const label bufSize, const int tag, const label comm);

	template<class T>
	List<T> readListFromIPstream(const int toProcNo, const label bufSize, const int tag, const label comm);
}

#include <PstreamHelperI.hxx>

#endif // !_gatherScatterHelper_Header
