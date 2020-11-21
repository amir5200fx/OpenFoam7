#include <boundaryPatch.hxx>

#include <dictionary.hxx>
#include <Ostream.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::boundaryPatch::boundaryPatch
(
	const word& name,
	const label index,
	const label size,
	const label start,
	const word& physicalType
)
	:
	patchIdentifier(name, index, physicalType),
	size_(size),
	start_(start)
{}


tnbLib::boundaryPatch::boundaryPatch
(
	const word& name,
	const dictionary& dict,
	const label index
)
	:
	patchIdentifier(name, dict, index),
	size_(readLabel(dict.lookup("nFaces"))),
	start_(readLabel(dict.lookup("startFace")))
{}


tnbLib::boundaryPatch::boundaryPatch(const boundaryPatch& p, const label index)
	:
	patchIdentifier(p.name(), index, p.physicalType()),
	size_(p.size()),
	start_(p.start())
{}


tnbLib::autoPtr<tnbLib::boundaryPatch> tnbLib::boundaryPatch::clone() const
{
	return autoPtr<boundaryPatch>(new boundaryPatch(*this));
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::boundaryPatch::~boundaryPatch()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::boundaryPatch::write(Ostream& os) const
{
	patchIdentifier::write(os);
	writeEntry(os, "nFaces", size_);
	writeEntry(os, "startFace", start_);
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

FoamDynamicMesh_EXPORT tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const boundaryPatch& p)
{
	p.write(os);
	os.check("Ostream& operator<<(Ostream& f, const boundaryPatch&)");
	return os;
}


// ************************************************************************* //