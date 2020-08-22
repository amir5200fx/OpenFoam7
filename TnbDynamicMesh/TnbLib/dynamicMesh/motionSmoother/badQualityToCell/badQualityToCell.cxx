#include <badQualityToCell.hxx>

#include <polyMesh.hxx>
#include <motionSmoother.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <faceSet.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{

	defineTypeNameAndDebug(badQualityToCell, 0);

	addToRunTimeSelectionTable(topoSetSource, badQualityToCell, word);

	addToRunTimeSelectionTable(topoSetSource, badQualityToCell, istream);

}


tnbLib::topoSetSource::addToUsageTable tnbLib::badQualityToCell::usage_
(
	badQualityToCell::typeName,
	"\n    Usage: badQualityToCell mesh-quality-dictionary\n\n"
	"    Select all cells that do not satisfy the selection criterion\n\n"
);


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::badQualityToCell::combine(topoSet& set, const bool add) const
{
	faceSet faces(mesh_, "meshQualityFaces", mesh_.nFaces() / 100 + 1);
	motionSmoother::checkMesh(false, mesh_, dict_, faces);
	faces.sync(mesh_);

	forAllConstIter(faceSet, faces, iter)
	{
		label facei = iter.key();
		addOrDelete(set, mesh_.faceOwner()[facei], add);
		if (mesh_.isInternalFace(facei))
		{
			addOrDelete(set, mesh_.faceNeighbour()[facei], add);
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Construct from dictionary
tnbLib::badQualityToCell::badQualityToCell
(
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	topoSetSource(mesh),
	dict_(dict)
{}


// Construct from Istream
tnbLib::badQualityToCell::badQualityToCell
(
	const polyMesh& mesh,
	Istream& is
)
	:
	topoSetSource(mesh),
	dict_(is)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::badQualityToCell::~badQualityToCell()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::badQualityToCell::applyToSet
(
	const topoSetSource::setAction action,
	topoSet& set
) const
{
	if ((action == topoSetSource::NEW) || (action == topoSetSource::ADD))
	{
		Info << "    Adding bad-quality cells" << endl;
		combine(set, true);
	}
	else if (action == topoSetSource::DELETE)
	{
		Info << "    Removing bad-quality cells" << endl;
		combine(set, false);
	}
}


// ************************************************************************* //