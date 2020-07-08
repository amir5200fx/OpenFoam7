#include <searchableSphere.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{

	defineTypeNameAndDebug(searchableSphere, 0);
	addToRunTimeSelectionTable(searchableSurface, searchableSphere, dict);

}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

tnbLib::pointIndexHit tnbLib::searchableSphere::findNearest
(
	const point& sample,
	const scalar nearestDistSqr
) const
{
	pointIndexHit info(false, sample, -1);

	const vector n(sample - centre_);
	scalar magN = mag(n);

	if (nearestDistSqr >= sqr(magN - radius_))
	{
		if (magN < rootVSmall)
		{
			info.rawPoint() = centre_ + vector(1, 0, 0)*radius_;
		}
		else
		{
			info.rawPoint() = centre_ + n / magN * radius_;
		}
		info.setHit();
		info.setIndex(0);
	}

	return info;
}


// From Graphics Gems - intersection of sphere with ray
void tnbLib::searchableSphere::findLineAll
(
	const point& start,
	const point& end,
	pointIndexHit& near,
	pointIndexHit& far
) const
{
	near.setMiss();
	far.setMiss();

	vector dir(end - start);
	scalar magSqrDir = magSqr(dir);

	if (magSqrDir > rootVSmall)
	{
		const vector toCentre(centre_ - start);
		scalar magSqrToCentre = magSqr(toCentre);

		dir /= tnbLib::sqrt(magSqrDir);

		scalar v = (toCentre & dir);

		scalar disc = sqr(radius_) - (magSqrToCentre - sqr(v));

		if (disc >= 0)
		{
			scalar d = tnbLib::sqrt(disc);

			scalar nearParam = v - d;

			if (nearParam >= 0 && sqr(nearParam) <= magSqrDir)
			{
				near.setHit();
				near.setPoint(start + nearParam * dir);
				near.setIndex(0);
			}

			scalar farParam = v + d;

			if (farParam >= 0 && sqr(farParam) <= magSqrDir)
			{
				far.setHit();
				far.setPoint(start + farParam * dir);
				far.setIndex(0);
			}
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::searchableSphere::searchableSphere
(
	const IOobject& io,
	const point& centre,
	const scalar radius
)
	:
	searchableSurface(io),
	centre_(centre),
	radius_(radius)
{
	bounds() = boundBox
	(
		centre_ - radius_ * vector::one,
		centre_ + radius_ * vector::one
	);
}


tnbLib::searchableSphere::searchableSphere
(
	const IOobject& io,
	const dictionary& dict
)
	:
	searchableSurface(io),
	centre_(dict.lookup("centre")),
	radius_(readScalar(dict.lookup("radius")))
{
	bounds() = boundBox
	(
		centre_ - radius_ * vector::one,
		centre_ + radius_ * vector::one
	);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::searchableSphere::~searchableSphere()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::searchableSphere::overlaps(const boundBox& bb) const
{
	return bb.overlaps(centre_, sqr(radius_));
}


const tnbLib::wordList& tnbLib::searchableSphere::regions() const
{
	if (regions_.empty())
	{
		regions_.setSize(1);
		regions_[0] = "region0";
	}
	return regions_;
}



void tnbLib::searchableSphere::boundingSpheres
(
	pointField& centres,
	scalarField& radiusSqr
) const
{
	centres.setSize(1);
	centres[0] = centre_;

	radiusSqr.setSize(1);
	radiusSqr[0] = tnbLib::sqr(radius_);

	// Add a bit to make sure all points are tested inside
	radiusSqr += tnbLib::sqr(small);
}


void tnbLib::searchableSphere::findNearest
(
	const pointField& samples,
	const scalarField& nearestDistSqr,
	List<pointIndexHit>& info
) const
{
	info.setSize(samples.size());

	forAll(samples, i)
	{
		info[i] = findNearest(samples[i], nearestDistSqr[i]);
	}
}


void tnbLib::searchableSphere::findLine
(
	const pointField& start,
	const pointField& end,
	List<pointIndexHit>& info
) const
{
	info.setSize(start.size());

	pointIndexHit b;

	forAll(start, i)
	{
		// Pick nearest intersection. If none intersected take second one.
		findLineAll(start[i], end[i], info[i], b);
		if (!info[i].hit() && b.hit())
		{
			info[i] = b;
		}
	}
}


void tnbLib::searchableSphere::findLineAny
(
	const pointField& start,
	const pointField& end,
	List<pointIndexHit>& info
) const
{
	info.setSize(start.size());

	pointIndexHit b;

	forAll(start, i)
	{
		// Discard far intersection
		findLineAll(start[i], end[i], info[i], b);
		if (!info[i].hit() && b.hit())
		{
			info[i] = b;
		}
	}
}


void tnbLib::searchableSphere::findLineAll
(
	const pointField& start,
	const pointField& end,
	List<List<pointIndexHit>>& info
) const
{
	info.setSize(start.size());

	forAll(start, i)
	{
		pointIndexHit near, far;
		findLineAll(start[i], end[i], near, far);

		if (near.hit())
		{
			if (far.hit())
			{
				info[i].setSize(2);
				info[i][0] = near;
				info[i][1] = far;
			}
			else
			{
				info[i].setSize(1);
				info[i][0] = near;
			}
		}
		else
		{
			if (far.hit())
			{
				info[i].setSize(1);
				info[i][0] = far;
			}
			else
			{
				info[i].clear();
			}
		}
	}
}


void tnbLib::searchableSphere::getRegion
(
	const List<pointIndexHit>& info,
	labelList& region
) const
{
	region.setSize(info.size());
	region = 0;
}


void tnbLib::searchableSphere::getNormal
(
	const List<pointIndexHit>& info,
	vectorField& normal
) const
{
	normal.setSize(info.size());
	normal = Zero;

	forAll(info, i)
	{
		if (info[i].hit())
		{
			normal[i] = info[i].hitPoint() - centre_;

			normal[i] /= mag(normal[i]) + vSmall;
		}
		else
		{
			// Set to what?
		}
	}
}


void tnbLib::searchableSphere::getVolumeType
(
	const pointField& points,
	List<volumeType>& volType
) const
{
	volType.setSize(points.size());
	volType = volumeType::inside;

	forAll(points, pointi)
	{
		const point& pt = points[pointi];

		if (magSqr(pt - centre_) <= sqr(radius_))
		{
			volType[pointi] = volumeType::inside;
		}
		else
		{
			volType[pointi] = volumeType::outside;
		}
	}
}


// ************************************************************************* //