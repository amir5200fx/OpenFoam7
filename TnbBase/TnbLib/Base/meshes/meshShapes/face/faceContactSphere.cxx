#include <face.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::scalar tnbLib::face::contactSphereDiameter
(
	const point& p,
	const vector& n,
	const pointField& meshPoints
) const
{
	scalar magN = tnbLib::mag(n);

	vector n1 = n / (magN + small);
	vector n2 = area(meshPoints);

	n2 /= tnbLib::mag(n2) + small;

	return 2 * ((centre(meshPoints) - p) & n2) / ((n1 & n2) - 1.0);
}


// ************************************************************************* //