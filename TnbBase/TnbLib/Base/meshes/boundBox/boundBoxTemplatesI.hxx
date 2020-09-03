#pragma once
#include <FixedList.hxx>
#include <PstreamReduceOps.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<unsigned Size>
tnbLib::boundBox::boundBox
(
	const UList<point>& points,
	const FixedList<label, Size>& indices,
	const bool doReduce
)
	:
	min_(Zero),
	max_(Zero)
{
	// a FixedList is never empty
	if (points.empty())
	{
		if (doReduce && Pstream::parRun())
		{
			// Use values that get overwritten by reduce minOp, maxOp below
			min_ = point(vGreat, vGreat, vGreat);
			max_ = point(-vGreat, -vGreat, -vGreat);
		}
	}
	else
	{
		min_ = points[indices[0]];
		max_ = points[indices[0]];

		for (unsigned i = 1; i < Size; ++i)
		{
			min_ = ::tnbLib::min(min_, points[indices[i]]);
			max_ = ::tnbLib::max(max_, points[indices[i]]);
		}
	}

	// Reduce parallel information
	if (doReduce)
	{
		reduce(min_, minOp<point>());
		reduce(max_, maxOp<point>());
	}
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

template<unsigned Size>
bool tnbLib::boundBox::contains
(
	const UList<point>& points,
	const FixedList<label, Size>& indices
) const
{
	// a FixedList is never empty
	if (points.empty())
	{
		return false;
	}

	forAll(indices, i)
	{
		if (!contains(points[indices[i]]))
		{
			return false;
		}
	}

	return true;
}


template<unsigned Size>
bool tnbLib::boundBox::containsAny
(
	const UList<point>& points,
	const FixedList<label, Size>& indices
) const
{
	// a FixedList is never empty
	if (points.empty())
	{
		return false;
	}

	forAll(indices, i)
	{
		if (contains(points[indices[i]]))
		{
			return true;
		}
	}

	return false;
}


// ************************************************************************* //