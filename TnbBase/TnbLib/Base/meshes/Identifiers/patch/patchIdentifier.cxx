#include <patchIdentifier.hxx>

#include <dictionary.hxx>
#include <ListOps.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::patchIdentifier::patchIdentifier
(
	const word& name,
	const label index,
	const word& physicalType,
	const wordList& inGroups
)
	:
	name_(name),
	index_(index),
	physicalType_(physicalType),
	inGroups_(inGroups)
{}


tnbLib::patchIdentifier::patchIdentifier
(
	const word& name,
	const dictionary& dict,
	const label index
)
	:
	name_(name),
	index_(index)
{
	dict.readIfPresent("physicalType", physicalType_);
	dict.readIfPresent("inGroups", inGroups_);
}


tnbLib::patchIdentifier::patchIdentifier
(
	const patchIdentifier& p,
	const label index
)
	:
	name_(p.name_),
	index_(index),
	physicalType_(p.physicalType_),
	inGroups_(p.inGroups_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::patchIdentifier::~patchIdentifier()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::patchIdentifier::inGroup(const word& name) const
{
	return findIndex(inGroups_, name) != -1;
}


void tnbLib::patchIdentifier::write(Ostream& os) const
{
	if (physicalType_.size())
	{
		writeEntry(os, "physicalType", physicalType_);
	}
	if (inGroups_.size())
	{
		writeEntry(os, "inGroups", inGroups_);
	}
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const patchIdentifier& pi)
{
	pi.write(os);
	os.check("Ostream& operator<<(Ostream&, const patchIdentifier&)");
	return os;
}


// ************************************************************************* //