#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline tnbLib::labelRanges::labelRanges()
	:
	ParentType()
{}


inline tnbLib::labelRanges::labelRanges(const label nElem)
	:
	ParentType(nElem)
{}


// * * * * * * * * * * * * * * * * Iterators * * * * * * * * * * * * * * * * //

inline tnbLib::labelRanges::const_iterator::const_iterator()
	:
	list_(endLabelRanges_),
	index_(-1),
	subIndex_(-1)
{}


inline tnbLib::labelRanges::const_iterator::const_iterator(const labelRanges& lst)
	:
	list_(lst),
	index_(0),
	subIndex_(0)
{
	if (list_.empty())
	{
		// equivalent to end iterator
		index_ = subIndex_ = -1;
	}
}


inline bool tnbLib::labelRanges::const_iterator::operator==
(
	const const_iterator& iter
	) const
{
	return
		(
			this->index_ == iter.index_
			&& this->subIndex_ == iter.subIndex_
			);
}


inline bool tnbLib::labelRanges::const_iterator::operator!=
(
	const const_iterator& iter
	) const
{
	return !(this->operator==(iter));
}


inline tnbLib::label tnbLib::labelRanges::const_iterator::operator*()
{
	return list_[index_][subIndex_];
}


inline tnbLib::label tnbLib::labelRanges::const_iterator::operator()()
{
	return list_[index_][subIndex_];
}


inline tnbLib::labelRanges::const_iterator&
tnbLib::labelRanges::const_iterator::operator++()
{
	if (++subIndex_ >= list_[index_].size())
	{
		// go to next list entry
		subIndex_ = 0;
		if (++index_ >= list_.size())
		{
			// equivalent to end iterator
			index_ = subIndex_ = -1;
		}
	}

	return *this;
}


inline tnbLib::labelRanges::const_iterator
tnbLib::labelRanges::const_iterator::operator++(int)
{
	const_iterator old = *this;
	this->operator++();
	return old;
}


inline tnbLib::labelRanges::const_iterator tnbLib::labelRanges::cbegin() const
{
	return const_iterator(*this);
}


inline const tnbLib::labelRanges::const_iterator& tnbLib::labelRanges::cend() const
{
	return endIter_;
}


inline tnbLib::labelRanges::const_iterator tnbLib::labelRanges::begin() const
{
	return const_iterator(*this);
}


inline const tnbLib::labelRanges::const_iterator& tnbLib::labelRanges::end() const
{
	return endIter_;
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline bool tnbLib::labelRanges::contains(const label value) const
{
	forAll(*this, i)
	{
		if (this->ParentType::operator[](i).contains(value))
		{
			return true;
		}
	}

	return false;
}


// ************************************************************************* //