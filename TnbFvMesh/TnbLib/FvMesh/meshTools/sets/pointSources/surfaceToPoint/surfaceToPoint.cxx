#include <surfaceToPoint.hxx>

#include <polyMesh.hxx>
#include <triSurfaceSearch.hxx>
#include <triSurface.hxx>
#include <cpuTime.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(surfaceToPoint, 0);
	addToRunTimeSelectionTable(topoSetSource, surfaceToPoint, word);
	addToRunTimeSelectionTable(topoSetSource, surfaceToPoint, istream);
}


tnbLib::topoSetSource::addToUsageTable tnbLib::surfaceToPoint::usage_
(
	surfaceToPoint::typeName,
	"\n    Usage: surfaceToPoint <surface> <near> <inside> <outside>\n\n"
	"    <surface> name of triSurface\n"
	"    <near> scalar; include points with coordinate <= near to surface\n"
	"    <inside> boolean; whether to include points on opposite side of"
	" surface normal\n"
	"    <outside> boolean; whether to include points on this side of"
	" surface normal\n\n"
);


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::surfaceToPoint::combine(topoSet& set, const bool add) const
{
	cpuTime timer;

	triSurface surf(surfName_);

	Info << "    Read surface from " << surfName_
		<< " in = " << timer.cpuTimeIncrement() << " s" << endl << endl;

	// Construct search engine on surface
	triSurfaceSearch querySurf(surf);

	if (includeInside_ || includeOutside_)
	{
		boolList pointInside(querySurf.calcInside(mesh_.points()));

		forAll(pointInside, pointi)
		{
			bool isInside = pointInside[pointi];

			if ((isInside && includeInside_) || (!isInside && includeOutside_))
			{
				addOrDelete(set, pointi, add);
			}
		}
	}

	if (nearDist_ > 0)
	{
		const pointField& meshPoints = mesh_.points();

		// Box dimensions to search in octree.
		const vector span(nearDist_, nearDist_, nearDist_);

		forAll(meshPoints, pointi)
		{
			const point& pt = meshPoints[pointi];

			pointIndexHit inter = querySurf.nearest(pt, span);

			if (inter.hit() && (mag(inter.hitPoint() - pt) < nearDist_))
			{
				addOrDelete(set, pointi, add);
			}
		}
	}
}


void tnbLib::surfaceToPoint::checkSettings() const
{
	if (nearDist_ < 0 && !includeInside_ && !includeOutside_)
	{
		FatalErrorInFunction
			<< "Illegal point selection specification."
			<< " Result would be either all or no points." << endl
			<< "Please set one of includeInside or includeOutside"
			<< " to true, set nearDistance to a value > 0"
			<< exit(FatalError);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::surfaceToPoint::surfaceToPoint
(
	const polyMesh& mesh,
	const fileName& surfName,
	const scalar nearDist,
	const bool includeInside,
	const bool includeOutside
)
	:
	topoSetSource(mesh),
	surfName_(surfName),
	nearDist_(nearDist),
	includeInside_(includeInside),
	includeOutside_(includeOutside)
{
	checkSettings();
}


tnbLib::surfaceToPoint::surfaceToPoint
(
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	topoSetSource(mesh),
	surfName_(fileName(dict.lookup("file")).expand()),
	nearDist_(readScalar(dict.lookup("nearDistance"))),
	includeInside_(readBool(dict.lookup("includeInside"))),
	includeOutside_(readBool(dict.lookup("includeOutside")))
{
	checkSettings();
}


tnbLib::surfaceToPoint::surfaceToPoint
(
	const polyMesh& mesh,
	Istream& is
)
	:
	topoSetSource(mesh),
	surfName_(checkIs(is)),
	nearDist_(readScalar(checkIs(is))),
	includeInside_(readBool(checkIs(is))),
	includeOutside_(readBool(checkIs(is)))
{
	checkSettings();
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::surfaceToPoint::~surfaceToPoint()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::surfaceToPoint::applyToSet
(
	const topoSetSource::setAction action,
	topoSet& set
) const
{
	if ((action == topoSetSource::NEW) || (action == topoSetSource::ADD))
	{
		Info << "    Adding points in relation to surface " << surfName_
			<< " ..." << endl;

		combine(set, true);
	}
	else if (action == topoSetSource::DELETE)
	{
		Info << "    Removing points in relation to surface " << surfName_
			<< " ..." << endl;

		combine(set, false);
	}
}


// ************************************************************************* //