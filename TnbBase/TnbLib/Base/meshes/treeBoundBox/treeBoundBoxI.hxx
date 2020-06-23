#pragma once
#include <Random.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline tnbLib::treeBoundBox::treeBoundBox()
	:
	boundBox()
{}


inline tnbLib::treeBoundBox::treeBoundBox(const point& min, const point& max)
	:
	boundBox(min, max)
{}


inline tnbLib::treeBoundBox::treeBoundBox(const boundBox& bb)
	:
	boundBox(bb)
{}


inline tnbLib::treeBoundBox::treeBoundBox(Istream& is)
	:
	boundBox(is)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline tnbLib::scalar tnbLib::treeBoundBox::typDim() const
{
	return avgDim();
}


inline tnbLib::point tnbLib::treeBoundBox::corner(const direction octant) const
{
	return point
	(
		(octant & octantBit::rightHalf) ? max().x() : min().x(),
		(octant & octantBit::topHalf) ? max().y() : min().y(),
		(octant & octantBit::frontHalf) ? max().z() : min().z()
	);
}


// Returns octant in which point resides. Reverse of subBbox.
inline tnbLib::direction tnbLib::treeBoundBox::subOctant(const point& pt) const
{
	return subOctant(midpoint(), pt);
}


// Returns octant in which point resides. Reverse of subBbox.
// Precalculated midpoint
inline tnbLib::direction tnbLib::treeBoundBox::subOctant
(
	const point& mid,
	const point& pt
)
{
	direction octant = 0;

	if (pt.x() > mid.x())
	{
		octant |= octantBit::rightHalf;
	}

	if (pt.y() > mid.y())
	{
		octant |= octantBit::topHalf;
	}

	if (pt.z() > mid.z())
	{
		octant |= octantBit::frontHalf;
	}

	return octant;
}


// Returns octant in which point resides. Reverse of subBbox.
// Flags point exactly on edge.
inline tnbLib::direction tnbLib::treeBoundBox::subOctant
(
	const point& pt,
	bool& onEdge
) const
{
	return subOctant(midpoint(), pt, onEdge);
}


// Returns octant in which point resides. Reverse of subBbox.
// Precalculated midpoint
inline tnbLib::direction tnbLib::treeBoundBox::subOctant
(
	const point& mid,
	const point& pt,
	bool& onEdge
)
{
	direction octant = 0;
	onEdge = false;

	if (pt.x() > mid.x())
	{
		octant |= octantBit::rightHalf;
	}
	else if (pt.x() == mid.x())
	{
		onEdge = true;
	}

	if (pt.y() > mid.y())
	{
		octant |= octantBit::topHalf;
	}
	else if (pt.y() == mid.y())
	{
		onEdge = true;
	}

	if (pt.z() > mid.z())
	{
		octant |= octantBit::frontHalf;
	}
	else if (pt.z() == mid.z())
	{
		onEdge = true;
	}

	return octant;
}


// Returns octant in which intersection resides.
// Precalculated midpoint. If the point is on the dividing line between
// the octants the direction vector determines which octant to use
// (i.e. in which octant the point would be if it were moved along dir)
inline tnbLib::direction tnbLib::treeBoundBox::subOctant
(
	const point& mid,
	const vector& dir,
	const point& pt,
	bool& onEdge
)
{
	direction octant = 0;
	onEdge = false;

	if (pt.x() > mid.x())
	{
		octant |= octantBit::rightHalf;
	}
	else if (pt.x() == mid.x())
	{
		onEdge = true;
		if (dir.x() > 0)
		{
			octant |= octantBit::rightHalf;
		}
	}

	if (pt.y() > mid.y())
	{
		octant |= octantBit::topHalf;
	}
	else if (pt.y() == mid.y())
	{
		onEdge = true;
		if (dir.y() > 0)
		{
			octant |= octantBit::topHalf;
		}
	}

	if (pt.z() > mid.z())
	{
		octant |= octantBit::frontHalf;
	}
	else if (pt.z() == mid.z())
	{
		onEdge = true;
		if (dir.z() > 0)
		{
			octant |= octantBit::frontHalf;
		}
	}

	return octant;
}


// Returns reference to octantOrder which defines the
// order to do the search.
inline void tnbLib::treeBoundBox::searchOrder
(
	const point& pt,
	FixedList<direction, 8>& octantOrder
) const
{
	vector dist = midpoint() - pt;

	direction octant = 0;

	if (dist.x() < 0)
	{
		octant |= octantBit::rightHalf;
		dist.x() *= -1;
	}

	if (dist.y() < 0)
	{
		octant |= octantBit::topHalf;
		dist.y() *= -1;
	}

	if (dist.z() < 0)
	{
		octant |= octantBit::frontHalf;
		dist.z() *= -1;
	}

	direction min = 0;
	direction mid = 0;
	direction max = 0;

	if (dist.x() < dist.y())
	{
		if (dist.y() < dist.z())
		{
			min = octantBit::rightHalf;
			mid = octantBit::topHalf;
			max = octantBit::frontHalf;
		}
		else if (dist.z() < dist.x())
		{
			min = octantBit::frontHalf;
			mid = octantBit::rightHalf;
			max = octantBit::topHalf;
		}
		else
		{
			min = octantBit::rightHalf;
			mid = octantBit::frontHalf;
			max = octantBit::topHalf;
		}
	}
	else
	{
		if (dist.z() < dist.y())
		{
			min = octantBit::frontHalf;
			mid = octantBit::topHalf;
			max = octantBit::rightHalf;
		}
		else if (dist.x() < dist.z())
		{
			min = octantBit::topHalf;
			mid = octantBit::rightHalf;
			max = octantBit::frontHalf;
		}
		else
		{
			min = octantBit::topHalf;
			mid = octantBit::frontHalf;
			max = octantBit::rightHalf;
		}
	}

	// Primary subOctant
	octantOrder[0] = octant;
	// subOctants joined to the primary by faces.
	octantOrder[1] = octant ^ min;
	octantOrder[2] = octant ^ mid;
	octantOrder[3] = octant ^ max;
	// subOctants joined to the primary by edges.
	octantOrder[4] = octantOrder[1] ^ mid;
	octantOrder[5] = octantOrder[1] ^ max;
	octantOrder[6] = octantOrder[2] ^ max;
	// subOctants joined to the primary by corner.
	octantOrder[7] = octantOrder[4] ^ max;
}


inline tnbLib::treeBoundBox tnbLib::treeBoundBox::extend(const scalar s) const
{
	// Numbers that don't approximate rational fractions with which to make the
	// box asymmetric. These are between one and two.
	static const vector a((sqrt(5.0) + 1) / 2, sqrt(2.0), (sqrt(13.0) - 1) / 2);
	static const vector b(a.y(), a.z(), a.x());

	treeBoundBox bb(*this);

	const scalar delta = s * tnbLib::mag(bb.span());
	bb.min() -= tnbLib::max(delta*a, vector::uniform(rootVSmall));
	bb.max() += tnbLib::max(delta*b, vector::uniform(rootVSmall));

	return bb;
}


// ************************************************************************* //