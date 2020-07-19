#pragma once
// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

inline void tnbLib::faceAreaIntersect::setTriPoints
(
	const point& a,
	const point& b,
	const point& c,
	label& count,
	FixedList<triPoints, 10>& tris
) const
{
	triPoints& tp = tris[count++];
	tp[0] = a;
	tp[1] = b;
	tp[2] = c;
}


inline tnbLib::faceAreaIntersect::triPoints tnbLib::faceAreaIntersect::getTriPoints
(
	const pointField& points,
	const face& f,
	const bool reverse
) const
{
	triPoints result;

	if (reverse)
	{
		result[2] = points[f[0]];
		result[1] = points[f[1]];
		result[0] = points[f[2]];
	}
	else
	{
		result[0] = points[f[0]];
		result[1] = points[f[1]];
		result[2] = points[f[2]];
	}

	return result;
}


inline tnbLib::point tnbLib::faceAreaIntersect::planeIntersection
(
	const FixedList<scalar, 3>& d,
	const triPoints& t,
	const label negI,
	const label posI
) const
{
	return (d[posI] * t[negI] - d[negI] * t[posI]) / (-d[negI] + d[posI]);
}


inline tnbLib::scalar tnbLib::faceAreaIntersect::triArea(const triPoints& t) const
{
	return mag(0.5*((t[1] - t[0]) ^ (t[2] - t[0])));
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

tnbLib::scalar& tnbLib::faceAreaIntersect::tolerance()
{
	return tol;
}


// ************************************************************************* //