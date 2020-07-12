#include <gradingDescriptor.hxx>

#include <IOstreams.hxx>
#include <token.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::gradingDescriptor::gradingDescriptor()
	:
	blockFraction_(1),
	nDivFraction_(1),
	expansionRatio_(1)
{}


tnbLib::gradingDescriptor::gradingDescriptor
(
	const scalar blockFraction,
	const scalar nDivFraction,
	const scalar expansionRatio
)
	:
	blockFraction_(blockFraction),
	nDivFraction_(nDivFraction),
	expansionRatio_(expansionRatio)
{}


tnbLib::gradingDescriptor::gradingDescriptor
(
	const scalar expansionRatio
)
	:
	blockFraction_(1.0),
	nDivFraction_(1.0),
	expansionRatio_(expansionRatio)
{}


tnbLib::gradingDescriptor::gradingDescriptor(Istream& is)
{
	is >> *this;
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::gradingDescriptor::~gradingDescriptor()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::gradingDescriptor tnbLib::gradingDescriptor::inv() const
{
	return gradingDescriptor
	(
		blockFraction_,
		nDivFraction_,
		1.0 / expansionRatio_
	);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

bool tnbLib::gradingDescriptor::operator==(const gradingDescriptor& gd) const
{
	return
		equal(blockFraction_, gd.blockFraction_)
		&& equal(nDivFraction_, gd.nDivFraction_)
		&& equal(expansionRatio_, gd.expansionRatio_);
}


bool tnbLib::gradingDescriptor::operator!=(const gradingDescriptor& gd) const
{
	return !operator==(gd);
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

tnbLib::Istream& tnbLib::operator>>(Istream& is, gradingDescriptor& gd)
{
	// Examine next token
	token t(is);

	if (t.isNumber())
	{
		gd.blockFraction_ = 1.0;
		gd.nDivFraction_ = 1.0;
		gd.expansionRatio_ = t.number();
	}
	else if (t.isPunctuation() && t.pToken() == token::BEGIN_LIST)
	{
		is >> gd.blockFraction_ >> gd.nDivFraction_ >> gd.expansionRatio_;
		is.readEnd("gradingDescriptor");
	}

	// Check state of Istream
	is.check("operator>>(Istream&, gradingDescriptor&)");

	return is;
}


tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const gradingDescriptor& gd)
{
	if (equal(gd.blockFraction_, 1))
	{
		os << gd.expansionRatio_;
	}
	else
	{
		os << token::BEGIN_LIST
			<< gd.blockFraction_ << token::SPACE
			<< gd.nDivFraction_ << token::SPACE
			<< gd.expansionRatio_
			<< token::END_LIST;
	}

	return os;
}


// ************************************************************************* //