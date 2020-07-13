#include <boxToPoint.hxx>

#include <polyMesh.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(boxToPoint, 0);
	addToRunTimeSelectionTable(topoSetSource, boxToPoint, word);
	addToRunTimeSelectionTable(topoSetSource, boxToPoint, istream);
}


tnbLib::topoSetSource::addToUsageTable tnbLib::boxToPoint::usage_
(
	boxToPoint::typeName,
	"\n    Usage: boxToPoint ((minx miny minz) (maxx maxy maxz))\n\n"
	"    Select all points with coordinate within bounding box\n\n"
);


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::boxToPoint::combine(topoSet& set, const bool add) const
{
	const pointField& pts = mesh_.points();

	forAll(pts, pointi)
	{
		forAll(bbs_, i)
		{
			if (bbs_[i].contains(pts[pointi]))
			{
				addOrDelete(set, pointi, add);
			}
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::boxToPoint::boxToPoint
(
	const polyMesh& mesh,
	const treeBoundBoxList& bbs
)
	:
	topoSetSource(mesh),
	bbs_(bbs)
{}


tnbLib::boxToPoint::boxToPoint
(
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	topoSetSource(mesh),
	bbs_
	(
		dict.found("box")
		? treeBoundBoxList(1, treeBoundBox(dict.lookup("box")))
		: dict.lookup("boxes")
	)
{}


tnbLib::boxToPoint::boxToPoint
(
	const polyMesh& mesh,
	Istream& is
)
	:
	topoSetSource(mesh),
	bbs_(1, treeBoundBox(checkIs(is)))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::boxToPoint::~boxToPoint()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::boxToPoint::applyToSet
(
	const topoSetSource::setAction action,
	topoSet& set
) const
{
	if ((action == topoSetSource::NEW) || (action == topoSetSource::ADD))
	{
		Info << "    Adding points that are within boxes " << bbs_ << " ..."
			<< endl;

		combine(set, true);
	}
	else if (action == topoSetSource::DELETE)
	{
		Info << "    Removing points that are within boxes " << bbs_ << " ..."
			<< endl;

		combine(set, false);
	}
}


// ************************************************************************* //