#pragma once
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

template<class T>
void tnbLib::writeToOPstream
(
	const int toProcNo,
	const label bufSize,
	const int tag,
	const label comm,
	const T& Value
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
	s << Value;
}

template<class T>
void tnbLib::writeToOPstream
(
	const int toProcNo,
	const label bufSize,
	const int tag,
	const label comm,
	const List<T>& Values
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
	s << Values;
}

template<class T>
void tnbLib::readFromIPstream
(
	const int toProcNo,
	const label bufSize,
	const int tag,
	const label comm,
	T& Value
)
{
	IPstream s
	(
		tnbLib::UPstream::commsTypes::scheduled,
		toProcNo,
		bufSize,
		tag,
		comm
	);

	s >> Value;
}

template<class T>
void tnbLib::readFromIPstream
(
	const int toProcNo,
	const label bufSize,
	const int tag,
	const label comm,
	List<T>& Values
)
{
	IPstream s
	(
		tnbLib::UPstream::commsTypes::scheduled,
		toProcNo,
		bufSize,
		tag,
		comm
	);

	s >> Values;
}

namespace tnbLib
{
	template<class T>
	T readFromIPstream
	(
		const int toProcNo,
		const label bufSize,
		const int tag,
		const label comm
	)
	{
		IPstream s
		(
			tnbLib::UPstream::commsTypes::scheduled,
			toProcNo,
			bufSize,
			tag,
			comm
		);

		T value;
		s >> value;
		return std::move(value);
	}
}

template<class T>
tnbLib::List<T>
tnbLib::readListFromIPstream
(
	const int toProcNo,
	const label bufSize,
	const int tag,
	const label comm
)
{
	IPstream s
	(
		tnbLib::UPstream::commsTypes::scheduled,
		toProcNo,
		bufSize,
		tag,
		comm
	);

	List<T> values(s);
	return std::move(values);
}