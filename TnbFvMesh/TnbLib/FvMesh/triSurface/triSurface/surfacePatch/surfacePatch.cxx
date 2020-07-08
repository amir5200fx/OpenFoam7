#include <surfacePatch.hxx>

#include <dictionary.hxx>
#include <word.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(surfacePatch, 0);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::surfacePatch::surfacePatch()
	:
	geometricSurfacePatch("", "", -1),
	size_(0),
	start_(0)
{}


tnbLib::surfacePatch::surfacePatch
(
	const word& geometricType,
	const word& name,
	const label size,
	const label start,
	const label index
)
	:
	geometricSurfacePatch(geometricType, name, index),
	size_(size),
	start_(start)
{}


tnbLib::surfacePatch::surfacePatch(Istream& is, const label index)
	:
	geometricSurfacePatch(is, index),
	size_(0),
	start_(0)
{
	size_ = readLabel(is);
	start_ = readLabel(is);
}


tnbLib::surfacePatch::surfacePatch
(
	const word& name,
	const dictionary& dict,
	const label index
)
	:
	geometricSurfacePatch(name, dict, index),
	size_(readLabel(dict.lookup("nFaces"))),
	start_(readLabel(dict.lookup("startFace")))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::surfacePatch::write(Ostream& os) const
{
	os << nl
		<< static_cast<const geometricSurfacePatch&>(*this) << endl
		<< size() << tab << start();
}

void tnbLib::surfacePatch::writeDict(Ostream& os) const
{
	os << nl << name() << nl << token::BEGIN_BLOCK << nl;

	geometricSurfacePatch::writeDict(os);

	os << "    nFaces " << size() << ';' << nl
		<< "    startFace " << start() << ';' << nl
		<< token::END_BLOCK << endl;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

bool tnbLib::surfacePatch::operator!=(const surfacePatch& p) const
{
	return !(*this == p);
}


bool tnbLib::surfacePatch::operator==(const surfacePatch& p) const
{
	return
		(
		(geometricType() == p.geometricType())
			&& (size() == p.size())
			&& (start() == p.start())
			);
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const surfacePatch& p)
{
	p.write(os);
	os.check("Ostream& operator<<(Ostream& f, const surfacePatch& p");
	return os;
}


// ************************************************************************* //