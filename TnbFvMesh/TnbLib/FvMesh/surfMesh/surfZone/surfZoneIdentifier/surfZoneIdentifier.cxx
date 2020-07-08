#include <surfZoneIdentifier.hxx>

#include <dictionary.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::surfZoneIdentifier::surfZoneIdentifier()
	:
	name_(word::null),
	index_(0),
	geometricType_(word::null)
{}


tnbLib::surfZoneIdentifier::surfZoneIdentifier
(
	const word& name,
	const label index,
	const word& geometricType
)
	:
	name_(name),
	index_(index),
	geometricType_(geometricType)
{}


tnbLib::surfZoneIdentifier::surfZoneIdentifier
(
	const word& name,
	const dictionary& dict,
	const label index
)
	:
	name_(name),
	index_(index)
{
	dict.readIfPresent("geometricType", geometricType_);
}


tnbLib::surfZoneIdentifier::surfZoneIdentifier
(
	const surfZoneIdentifier& p,
	const label index
)
	:
	name_(p.name()),
	index_(index),
	geometricType_(p.geometricType())
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::surfZoneIdentifier::~surfZoneIdentifier()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //


void tnbLib::surfZoneIdentifier::write(Ostream& os) const
{
	if (geometricType_.size())
	{
		writeEntry(os, "geometricType", geometricType_);
	}
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

// bool tnbLib::surfZoneIdentifier::operator!=
// (
//     const surfZoneIdentifier& p
// ) const
// {
//     return !(*this == p);
// }
//
//
// bool tnbLib::surfZoneIdentifier::operator==
// (
//     const surfZoneIdentifier& p
// ) const
// {
//     return geometricType() == p.geometricType() && name() == p.name();
// }


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

// tnbLib::Istream& tnbLib::operator>>(Istream& is, surfZoneIdentifier& p)
// {
//     is >> p.name_ >> p.geometricType_;
//
//     return is;
// }


tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const surfZoneIdentifier& p)
{
	p.write(os);
	os.check
	(
		"Ostream& operator<<(Ostream&, const surfZoneIdentifier&)"
	);
	return os;
}


// ************************************************************************* //