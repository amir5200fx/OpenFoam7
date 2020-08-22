#include <badQualityToFace.hxx>

#include <polyMesh.hxx>
#include <motionSmoother.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <faceSet.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{

	defineTypeNameAndDebug(badQualityToFace, 0);

	addToRunTimeSelectionTable(topoSetSource, badQualityToFace, word);

	addToRunTimeSelectionTable(topoSetSource, badQualityToFace, istream);

}

tnbLib::topoSetSource::addToUsageTable tnbLib::badQualityToFace::usage_
(
	badQualityToFace::typeName,
	"\n    Usage: badQualityToFace mesh-quality-dictionary\n\n"
	"    Select all faces that do not satisfy the selection criterion\n\n"
);


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::badQualityToFace::combine(topoSet& set, const bool add) const
{
	faceSet faces(mesh_, "meshQualityFaces", mesh_.nFaces() / 100 + 1);
	motionSmoother::checkMesh(false, mesh_, dict_, faces);
	faces.sync(mesh_);

	forAllConstIter(faceSet, faces, iter)
	{
		label facei = iter.key();
		addOrDelete(set, facei, add);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Construct from dictionary
tnbLib::badQualityToFace::badQualityToFace
(
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	topoSetSource(mesh),
	dict_(dict)
{}

// Construct from Istream
tnbLib::badQualityToFace::badQualityToFace
(
	const polyMesh& mesh,
	Istream& is
)
	:
	topoSetSource(mesh),
	dict_(is)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::badQualityToFace::~badQualityToFace()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::badQualityToFace::applyToSet
(
	const topoSetSource::setAction action,
	topoSet& set
) const
{
	if ((action == topoSetSource::NEW) || (action == topoSetSource::ADD))
	{
		Info << "    Adding bad-quality faces" << endl;
		combine(set, true);
	}
	else if (action == topoSetSource::DELETE)
	{
		Info << "    Removing bad-quality faces" << endl;
		combine(set, false);
	}
}


// ************************************************************************* //