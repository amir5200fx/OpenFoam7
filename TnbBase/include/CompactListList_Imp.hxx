#pragma once
// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

template<class T, class Container>
tnbLib::CompactListList<T, Container>::CompactListList(const List<Container>& ll)
	:
	size_(ll.size()),
	offsets_(ll.size() + 1)
{
	label sumSize = 0;
	offsets_[0] = 0;
	forAll(ll, i)
	{
		sumSize += ll[i].size();
		offsets_[i + 1] = sumSize;
	}

	m_.setSize(sumSize);

	label k = 0;
	forAll(ll, i)
	{
		const Container& lli = ll[i];

		forAll(lli, j)
		{
			m_[k++] = lli[j];
		}
	}
}


template<class T, class Container>
tnbLib::CompactListList<T, Container>::CompactListList
(
	const labelUList& rowSizes
)
	:
	size_(rowSizes.size()),
	offsets_(rowSizes.size() + 1)
{
	label sumSize = 0;
	offsets_[0] = 0;
	forAll(rowSizes, i)
	{
		sumSize += rowSizes[i];
		offsets_[i + 1] = sumSize;
	}

	m_.setSize(sumSize);
}


template<class T, class Container>
tnbLib::CompactListList<T, Container>::CompactListList
(
	const labelUList& rowSizes,
	const T& t
)
	:
	size_(rowSizes.size()),
	offsets_(rowSizes.size() + 1)
{
	label sumSize = 0;
	offsets_[0] = 0;
	forAll(rowSizes, i)
	{
		sumSize += rowSizes[i];
		offsets_[i + 1] = sumSize;
	}

	m_.setSize(sumSize, t);
}


template<class T, class Container>
tnbLib::CompactListList<T, Container>::CompactListList
(
	CompactListList<T, Container>&& lst
)
{
	transfer(lst);
}


template<class T, class Container>
tnbLib::CompactListList<T, Container>::CompactListList
(
	CompactListList<T, Container>& lst,
	bool reuse
)
	:
	size_(lst.size()),
	offsets_(lst.offsets_, reuse),
	m_(lst.m_, reuse)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class T, class Container>
void tnbLib::CompactListList<T, Container>::setSize(const label mRows)
{
	if (mRows == 0)
	{
		clear();
	}
	if (mRows < size())
	{
		size_ = mRows;
		offsets_.setSize(mRows + 1);
		m_.setSize(offsets_[mRows]);
	}
	else if (mRows > size())
	{
		FatalErrorInFunction
			<< "Cannot be used to extend the list from " << offsets_.size()
			<< " to " << mRows << nl
			<< "    Please use one of the other setSize member functions"
			<< abort(FatalError);
	}
}


template<class T, class Container>
void tnbLib::CompactListList<T, Container>::setSize
(
	const label mRows,
	const label nData
)
{
	size_ = mRows;
	offsets_.setSize(mRows + 1);
	m_.setSize(nData);
}


template<class T, class Container>
void tnbLib::CompactListList<T, Container>::setSize
(
	const label mRows,
	const label nData,
	const T& t
)
{
	size_ = mRows;
	offsets_.setSize(mRows + 1);
	m_.setSize(nData, t);
}


template<class T, class Container>
void tnbLib::CompactListList<T, Container>::setSize(const labelUList& rowSizes)
{
	size_ = rowSizes.size();
	offsets_.setSize(rowSizes.size() + 1);

	label sumSize = 0;
	offsets_[0] = 0;
	forAll(rowSizes, i)
	{
		sumSize += rowSizes[i];
		offsets_[i + 1] = sumSize;
	}

	m_.setSize(sumSize);
}


template<class T, class Container>
tnbLib::labelList tnbLib::CompactListList<T, Container>::sizes() const
{
	labelList rowSizes(size());

	if (rowSizes.size() > 0)
	{
		forAll(rowSizes, i)
		{
			rowSizes[i] = offsets_[i + 1] - offsets_[i];
		}
	}
	return rowSizes;
}


template<class T, class Container>
void tnbLib::CompactListList<T, Container>::clear()
{
	size_ = 0;
	offsets_.clear();
	m_.clear();
}


template<class T, class Container>
void tnbLib::CompactListList<T, Container>::transfer
(
	CompactListList<T, Container>& a
)
{
	size_ = a.size_;
	offsets_.transfer(a.offsets_);
	m_.transfer(a.m_);

	a.size_ = 0;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class T, class Container>
tnbLib::List<Container> tnbLib::CompactListList<T, Container>::operator()()
const
{
	List<Container> ll(size());

	forAll(ll, i)
	{
		ll[i] = Container(operator[](i));
	}

	return ll;
}


// * * * * * * * * * * * * * * * *  IOStream operators * * * * * * * * * * * //