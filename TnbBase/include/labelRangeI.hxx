#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline tnbLib::labelRange::labelRange()
	:
	start_(0),
	size_(0)
{}


inline tnbLib::labelRange::labelRange(const label start, const label size)
	:
	start_(start),
	size_(size)
{
	// disallow invalid sizes
	if (size_ <= 0)
	{
		this->clear();
	}
}


// * * * * * * * * * * * * * * * * Iterators * * * * * * * * * * * * * * * * //

inline tnbLib::labelRange::const_iterator::const_iterator()
	:
	range_(endLabelRange_),
	index_(-1)
{}


inline tnbLib::labelRange::const_iterator::const_iterator(const labelRange& range)
	:
	range_(range),
	index_(range_.empty() ? -1 : 0)
{}


inline bool tnbLib::labelRange::const_iterator::operator==
(
	const const_iterator& iter
	) const
{
	return (this->index_ == iter.index_);
}


inline bool tnbLib::labelRange::const_iterator::operator!=
(
	const const_iterator& iter
	) const
{
	return !(this->operator==(iter));
}


inline tnbLib::label tnbLib::labelRange::const_iterator::operator*()
{
	return range_[index_];
}


inline tnbLib::label tnbLib::labelRange::const_iterator::operator()()
{
	return range_[index_];
}


inline tnbLib::labelRange::const_iterator&
tnbLib::labelRange::const_iterator::operator++()
{
	if (++index_ >= range_.size())
	{
		// equivalent to end iterator
		index_ = -1;
	}

	return *this;
}


inline tnbLib::labelRange::const_iterator
tnbLib::labelRange::const_iterator::operator++(int)
{
	const_iterator old = *this;
	this->operator++();
	return old;
}


inline tnbLib::labelRange::const_iterator tnbLib::labelRange::cbegin() const
{
	return const_iterator(*this);
}


inline const tnbLib::labelRange::const_iterator& tnbLib::labelRange::cend() const
{
	return endIter_;
}


inline tnbLib::labelRange::const_iterator tnbLib::labelRange::begin() const
{
	return const_iterator(*this);
}


inline const tnbLib::labelRange::const_iterator& tnbLib::labelRange::end() const
{
	return endIter_;
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline void tnbLib::labelRange::clear()
{
	start_ = size_ = 0;
}


inline bool tnbLib::labelRange::empty() const
{
	return !size_;
}


inline tnbLib::label tnbLib::labelRange::size() const
{
	return size_;
}


inline tnbLib::label tnbLib::labelRange::first() const
{
	return start_;
}


inline tnbLib::label tnbLib::labelRange::last() const
{
	return start_ + size_ - 1;
}


inline bool tnbLib::labelRange::contains(const label value) const
{
	return value >= this->first() && value <= this->last();
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

inline tnbLib::label tnbLib::labelRange::operator[](const label i) const
{
	return start_ + i;
}


inline bool tnbLib::labelRange::operator<(const labelRange& rhs) const
{
	return this->first() < rhs.first();
}


inline bool tnbLib::labelRange::operator==(const labelRange& rhs) const
{
	return start_ == rhs.start_ && size_ == rhs.size_;
}


inline bool tnbLib::labelRange::operator!=(const labelRange& rhs) const
{
	return !(operator==(rhs));
}


// ************************************************************************* //