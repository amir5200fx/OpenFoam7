#include <searchablePlane.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <SortableList.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{

	defineTypeNameAndDebug(searchablePlane, 0);
	addToRunTimeSelectionTable(searchableSurface, searchablePlane, dict);

}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

tnbLib::pointIndexHit tnbLib::searchablePlane::findLine
(
	const point& start,
	const point& end
) const
{
	pointIndexHit info(true, Zero, 0);

	linePointRef l(start, end);

	scalar t = lineIntersect(l);

	if (t < 0 || t > 1)
	{
		info.setMiss();
		info.setIndex(-1);
	}
	else
	{
		info.setPoint(start + t * l.vec());
	}

	return info;
}


tnbLib::boundBox tnbLib::searchablePlane::calcBounds() const
{
	point max(vGreat, vGreat, vGreat);

	for (direction dir = 0; dir < vector::nComponents; dir++)
	{
		if (mag(normal()[dir]) - 1 < small)
		{
			max[dir] = 0;

			break;
		}
	}

	point min = -max;

	return boundBox(min, max);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::searchablePlane::searchablePlane
(
	const IOobject& io,
	const point& basePoint,
	const vector& normal
)
	:
	searchableSurface(io),
	plane(basePoint, normal)
{
	bounds() = calcBounds();
}


tnbLib::searchablePlane::searchablePlane
(
	const IOobject& io,
	const dictionary& dict
)
	:
	searchableSurface(io),
	plane(dict)
{
	bounds() = calcBounds();
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::searchablePlane::~searchablePlane()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::wordList& tnbLib::searchablePlane::regions() const
{
	if (regions_.empty())
	{
		regions_.setSize(1);
		regions_[0] = "region0";
	}
	return regions_;
}


void tnbLib::searchablePlane::boundingSpheres
(
	pointField& centres,
	scalarField& radiusSqr
) const
{
	centres.setSize(1);
	centres[0] = refPoint();

	radiusSqr.setSize(1);
	radiusSqr[0] = tnbLib::sqr(great);
}


void tnbLib::searchablePlane::findNearest
(
	const pointField& samples,
	const scalarField& nearestDistSqr,
	List<pointIndexHit>& info
) const
{
	info.setSize(samples.size());

	forAll(samples, i)
	{
		info[i].setPoint(nearestPoint(samples[i]));

		if (magSqr(samples[i] - info[i].rawPoint()) > nearestDistSqr[i])
		{
			info[i].setIndex(-1);
			info[i].setMiss();
		}
		else
		{
			info[i].setIndex(0);
			info[i].setHit();
		}
	}
}


void tnbLib::searchablePlane::findLine
(
	const pointField& start,
	const pointField& end,
	List<pointIndexHit>& info
) const
{
	info.setSize(start.size());

	forAll(start, i)
	{
		info[i] = findLine(start[i], end[i]);
	}
}


void tnbLib::searchablePlane::findLineAny
(
	const pointField& start,
	const pointField& end,
	List<pointIndexHit>& info
) const
{
	findLine(start, end, info);
}


void tnbLib::searchablePlane::findLineAll
(
	const pointField& start,
	const pointField& end,
	List<List<pointIndexHit>>& info
) const
{
	List<pointIndexHit> nearestInfo;
	findLine(start, end, nearestInfo);

	info.setSize(start.size());
	forAll(info, pointi)
	{
		if (nearestInfo[pointi].hit())
		{
			info[pointi].setSize(1);
			info[pointi][0] = nearestInfo[pointi];
		}
		else
		{
			info[pointi].clear();
		}
	}
}


void tnbLib::searchablePlane::getRegion
(
	const List<pointIndexHit>& info,
	labelList& region
) const
{
	region.setSize(info.size());
	region = 0;
}


void tnbLib::searchablePlane::getNormal
(
	const List<pointIndexHit>& info,
	vectorField& n
) const
{
	n.setSize(info.size());
	n = normal();
}


void tnbLib::searchablePlane::getVolumeType
(
	const pointField& points,
	List<volumeType>& volType
) const
{
	FatalErrorInFunction
		<< "Volume type not supported for plane."
		<< exit(FatalError);
}


// ************************************************************************* //