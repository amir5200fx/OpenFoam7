#include <labelRange.hxx>

#include <token.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

const tnbLib::labelRange tnbLib::labelRange::endLabelRange_;
const tnbLib::labelRange::const_iterator tnbLib::labelRange::endIter_;
int tnbLib::labelRange::debug(::tnbLib::debug::debugSwitch("labelRange", 0));


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::labelRange::labelRange(Istream& is)
	:
	start_(0),
	size_(0)
{
	is >> *this;
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::labelRange::intersects
(
	const labelRange& range,
	const bool touches
) const
{
	label final = touches ? 1 : 0;

	return
		(
			this->size()
			&& range.size()
			&&
			(
			(
				range.first() >= this->first()
				&& range.first() <= this->last() + final
				)
				||
				(
					this->first() >= range.first()
					&& this->first() <= range.last() + final
					)
				)
			);
}


tnbLib::labelRange tnbLib::labelRange::join(const labelRange& range) const
{
	// trivial cases first
	if (!size_)
	{
		return *this;
	}
	else if (!range.size_)
	{
		return range;
	}

	const label lower = tnbLib::min(this->first(), range.first());
	const label upper = tnbLib::max(this->last(), range.last());
	const label sz = upper - lower + 1;

	return labelRange(lower, sz);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

tnbLib::labelRange& tnbLib::labelRange::operator+=(const labelRange& rhs)
{
	if (!size_)
	{
		// trivial case
		operator=(rhs);
	}
	else if (rhs.size_)
	{
		const label lower = tnbLib::min(this->first(), rhs.first());
		const label upper = tnbLib::max(this->last(), rhs.last());

		start_ = lower;
		size_ = upper - lower + 1;
	}

	return *this;
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

tnbLib::Istream& tnbLib::operator>>(Istream& is, labelRange& range)
{
	is.readBegin("labelRange");
	is >> range.start_ >> range.size_;
	is.readEnd("labelRange");

	is.check("operator>>(Istream&, labelRange&)");

	// disallow invalid sizes
	if (range.size_ <= 0)
	{
		range.clear();
	}

	return is;
}


tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const labelRange& range)
{
	// write ASCII only for now
	os << token::BEGIN_LIST
		<< range.start_ << token::SPACE << range.size_
		<< token::END_LIST;

	//    os  << token::BEGIN_BLOCK
	//        << range.start_ << "-" << range.last()
	//        << token::END_BLOCK;

	os.check("operator<<(Ostream&, const labelRange&)");
	return os;
}


// ************************************************************************* //