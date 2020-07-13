#include <boundaryToFace.hxx>

#include <polyMesh.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(boundaryToFace, 0);
	addToRunTimeSelectionTable(topoSetSource, boundaryToFace, word);
	addToRunTimeSelectionTable(topoSetSource, boundaryToFace, istream);
}


tnbLib::topoSetSource::addToUsageTable tnbLib::boundaryToFace::usage_
(
	boundaryToFace::typeName,
	"\n    Usage: boundaryToFace\n\n"
	"    Select all boundary faces\n\n"
);


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::boundaryToFace::combine(topoSet& set, const bool add) const
{
	for
		(
			label facei = mesh().nInternalFaces();
			facei < mesh().nFaces();
			facei++
			)
	{
		addOrDelete(set, facei, add);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::boundaryToFace::boundaryToFace(const polyMesh& mesh)
	:
	topoSetSource(mesh)
{}


tnbLib::boundaryToFace::boundaryToFace(const polyMesh& mesh, const dictionary&)
	:
	topoSetSource(mesh)
{}


tnbLib::boundaryToFace::boundaryToFace
(
	const polyMesh& mesh,
	Istream& is
)
	:
	topoSetSource(mesh)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::boundaryToFace::~boundaryToFace()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::boundaryToFace::applyToSet
(
	const topoSetSource::setAction action,
	topoSet& set
) const
{
	if ((action == topoSetSource::NEW) || (action == topoSetSource::ADD))
	{
		Info << "    Adding all boundary faces ..." << endl;

		combine(set, true);
	}
	else if (action == topoSetSource::DELETE)
	{
		Info << "    Removing all boundary faces ..." << endl;

		combine(set, false);
	}
}


// ************************************************************************* //