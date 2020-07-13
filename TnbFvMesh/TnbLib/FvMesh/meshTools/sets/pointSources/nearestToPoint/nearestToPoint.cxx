#include <nearestToPoint.hxx>

#include <polyMesh.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(nearestToPoint, 0);
	addToRunTimeSelectionTable(topoSetSource, nearestToPoint, word);
	addToRunTimeSelectionTable(topoSetSource, nearestToPoint, istream);
}


tnbLib::topoSetSource::addToUsageTable tnbLib::nearestToPoint::usage_
(
	nearestToPoint::typeName,
	"\n    Usage: nearestToPoint (pt0 .. ptn)\n\n"
	"    Select the nearest point for each of the points pt0 ..ptn\n\n"
);


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::nearestToPoint::combine(topoSet& set, const bool add) const
{
	// Do linear search since usually just a few points.

	forAll(points_, pointi)
	{
		const pointField& pts = mesh_.points();

		if (pts.size())
		{
			label minPointi = 0;
			scalar minDistSqr = magSqr(pts[minPointi] - points_[pointi]);

			for (label i = 1; i < pts.size(); i++)
			{
				scalar distSqr = magSqr(pts[i] - points_[pointi]);

				if (distSqr < minDistSqr)
				{
					minDistSqr = distSqr;
					minPointi = i;
				}
			}

			addOrDelete(set, minPointi, add);
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::nearestToPoint::nearestToPoint
(
	const polyMesh& mesh,
	const pointField& points
)
	:
	topoSetSource(mesh),
	points_(points)
{}


tnbLib::nearestToPoint::nearestToPoint
(
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	topoSetSource(mesh),
	points_(dict.lookup("points"))
{}


tnbLib::nearestToPoint::nearestToPoint
(
	const polyMesh& mesh,
	Istream& is
)
	:
	topoSetSource(mesh),
	points_(checkIs(is))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::nearestToPoint::~nearestToPoint()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::nearestToPoint::applyToSet
(
	const topoSetSource::setAction action,
	topoSet& set
) const
{
	if ((action == topoSetSource::NEW) || (action == topoSetSource::ADD))
	{
		Info << "    Adding points nearest to " << points_ << endl;

		combine(set, true);
	}
	else if (action == topoSetSource::DELETE)
	{
		Info << "    Removing points nearest to " << points_ << endl;

		combine(set, false);
	}
}


// ************************************************************************* //