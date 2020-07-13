#include <nearestToCell.hxx>

#include <polyMesh.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(nearestToCell, 0);
	addToRunTimeSelectionTable(topoSetSource, nearestToCell, word);
	addToRunTimeSelectionTable(topoSetSource, nearestToCell, istream);
}


tnbLib::topoSetSource::addToUsageTable tnbLib::nearestToCell::usage_
(
	nearestToCell::typeName,
	"\n    Usage: nearestToCell (pt0 .. ptn)\n\n"
	"    Select the nearest cell for each of the points pt0 ..ptn\n\n"
);


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::nearestToCell::combine(topoSet& set, const bool add) const
{
	forAll(points_, pointi)
	{
		addOrDelete(set, mesh_.findNearestCell(points_[pointi]), add);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::nearestToCell::nearestToCell
(
	const polyMesh& mesh,
	const pointField& points
)
	:
	topoSetSource(mesh),
	points_(points)
{}


tnbLib::nearestToCell::nearestToCell
(
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	topoSetSource(mesh),
	points_(dict.lookup("points"))
{}


tnbLib::nearestToCell::nearestToCell
(
	const polyMesh& mesh,
	Istream& is
)
	:
	topoSetSource(mesh),
	points_(checkIs(is))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::nearestToCell::~nearestToCell()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::nearestToCell::applyToSet
(
	const topoSetSource::setAction action,
	topoSet& set
) const
{
	if ((action == topoSetSource::NEW) || (action == topoSetSource::ADD))
	{
		Info << "    Adding cells nearest to " << points_ << endl;

		combine(set, true);
	}
	else if (action == topoSetSource::DELETE)
	{
		Info << "    Removing cells nearest to " << points_ << endl;

		combine(set, false);
	}
}


// ************************************************************************* //