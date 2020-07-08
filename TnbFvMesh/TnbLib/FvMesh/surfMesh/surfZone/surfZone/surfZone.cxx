#include <surfZone.hxx>

#include <dictionary.hxx>
#include <word.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(surfZone, 0);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::surfZone::surfZone()
	:
	surfZoneIdentifier(),
	size_(0),
	start_(0)
{}


tnbLib::surfZone::surfZone
(
	const word& name,
	const label size,
	const label start,
	const label index,
	const word& geometricType
)
	:
	surfZoneIdentifier(name, index, geometricType),
	size_(size),
	start_(start)
{}


tnbLib::surfZone::surfZone(Istream& is, const label index)
	:
	surfZoneIdentifier(),
	size_(0),
	start_(0)
{
	word name(is);
	dictionary dict(is);

	operator=(surfZone(name, dict, index));
}


tnbLib::surfZone::surfZone
(
	const word& name,
	const dictionary& dict,
	const label index
)
	:
	surfZoneIdentifier(name, dict, index),
	size_(readLabel(dict.lookup("nFaces"))),
	start_(readLabel(dict.lookup("startFace")))
{}


tnbLib::surfZone::surfZone(const surfZone& zone, const label index)
	:
	surfZoneIdentifier(zone, index),
	size_(zone.size()),
	start_(zone.start())
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::surfZone::write(Ostream& os) const
{
	writeDict(os);
}


void tnbLib::surfZone::writeDict(Ostream& os) const
{
	os << indent << name() << nl
		<< indent << token::BEGIN_BLOCK << incrIndent << nl;

	surfZoneIdentifier::write(os);
	writeEntry(os, "nFaces", size());
	writeEntry(os, "startFace", start());

	os << decrIndent << indent << token::END_BLOCK << endl;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

bool tnbLib::surfZone::operator!=(const surfZone& rhs) const
{
	return !(*this == rhs);
}


bool tnbLib::surfZone::operator==(const surfZone& rhs) const
{
	return
		(
			size() == rhs.size()
			&& start() == rhs.start()
			&& geometricType() == rhs.geometricType()
			);
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

tnbLib::Istream& tnbLib::operator>>(Istream& is, surfZone& zone)
{
	zone = surfZone(is, 0);

	is.check("Istream& operator>>(Istream&, surfZone&)");
	return is;
}


tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const surfZone& zone)
{
	zone.write(os);
	os.check("Ostream& operator<<(Ostream&, const surfZone&");
	return os;
}


// ************************************************************************* //