#pragma once
#include <ListOps.hxx>
#include <SubList.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class T, class Container>
inline tnbLib::CompactListList<T, Container>::CompactListList()
	:
	size_(0)
{}


template<class T, class Container>
inline tnbLib::CompactListList<T, Container>::CompactListList
(
	const label mRows,
	const label nData
)
	:
	size_(mRows),
	offsets_(mRows + 1, 0),
	m_(nData)
{}


template<class T, class Container>
inline tnbLib::CompactListList<T, Container>::CompactListList
(
	const label mRows,
	const label nData,
	const T& t
)
	:
	size_(mRows),
	offsets_(mRows + 1, 0),
	m_(nData, t)
{}


template<class T, class Container>
inline tnbLib::autoPtr<tnbLib::CompactListList<T, Container>>
tnbLib::CompactListList<T, Container>::clone() const
{
	return autoPtr<CompactListList<T, Container>>
		(
			new CompactListList<T, Container>(*this)
			);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class T, class Container>
inline const tnbLib::CompactListList<T, Container>&
tnbLib::CompactListList<T, Container>::null()
{
	return NullObjectRef<CompactListList<T, Container>>();
}


template<class T, class Container>
inline tnbLib::label tnbLib::CompactListList<T, Container>::size() const
{
	return size_;
}


template<class T, class Container>
inline bool tnbLib::CompactListList<T, Container>::empty() const
{
	return !size_;
}


template<class T, class Container>
inline const tnbLib::List<tnbLib::label>&
tnbLib::CompactListList<T, Container>::offsets() const
{
	return offsets_;
}


template<class T, class Container>
inline tnbLib::List<tnbLib::label>& tnbLib::CompactListList<T, Container>::offsets()
{
	return offsets_;
}


template<class T, class Container>
inline const tnbLib::List<T>& tnbLib::CompactListList<T, Container>::m()
const
{
	return m_;
}


template<class T, class Container>
inline tnbLib::List<T>& tnbLib::CompactListList<T, Container>::m()
{
	return m_;
}


template<class T, class Container>
inline tnbLib::label tnbLib::CompactListList<T, Container>::index
(
	const label i,
	const label j
) const
{
	return offsets_[i] + j;
}


template<class T, class Container>
inline tnbLib::label tnbLib::CompactListList<T, Container>::whichRow(const label i)
const
{
	if (i < 0 || i >= m_.size())
	{
		FatalErrorInFunction
			<< "Index " << i << " outside 0.." << m_.size()
			<< abort(FatalError);
	}

	return findLower(offsets_, i + 1);
}


template<class T, class Container>
inline tnbLib::label tnbLib::CompactListList<T, Container>::whichColumn
(
	const label row,
	const label i
) const
{
	return i - index(row, 0);
}


template<class T, class Container>
inline void tnbLib::CompactListList<T, Container>::resize(const label mRows)
{
	this->setSize(mRows);
}


template<class T, class Container>
inline void tnbLib::CompactListList<T, Container>::resize
(
	const label mRows,
	const label nData
)
{
	this->setSize(mRows, nData);
}


template<class T, class Container>
inline void tnbLib::CompactListList<T, Container>::resize
(
	const label mRows,
	const label nData,
	const T& t
)
{
	this->setSize(mRows, nData, t);
}


template<class T, class Container>
inline void tnbLib::CompactListList<T, Container>::resize
(
	const labelUList& rowSizes
)
{
	this->setSize(rowSizes);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class T, class Container>
inline tnbLib::UList<T> tnbLib::CompactListList<T, Container>::operator[]
(
	const label i
	)
{
	label start = offsets_[i];
	return UList<T>(m_.begin() + start, offsets_[i + 1] - start);
}


template<class T, class Container>
inline const tnbLib::UList<T>
tnbLib::CompactListList<T, Container>::operator[]
(
	const label i
	) const
{
	label start = offsets_[i];
	return UList<T>
		(
			const_cast<T*>(m_.begin() + start),
			offsets_[i + 1] - start
			);
}


template<class T, class Container>
inline T& tnbLib::CompactListList<T, Container>::operator()
(
	const label i,
	const label j
	)
{
	return m_[index(i, j)];
}


template<class T, class Container>
inline const T& tnbLib::CompactListList<T, Container>::operator()
(
	const label i,
	const label j
	) const
{
	return m_[index(i, j)];
}


template<class T, class Container>
inline void tnbLib::CompactListList<T, Container>::operator=
(
	CompactListList<T, Container>&& cll
	)
{
	transfer(cll);
}


template<class T, class Container>
inline void tnbLib::CompactListList<T, Container>::operator=(const T& t)
{
	m_ = t;
}


// ************************************************************************* //
