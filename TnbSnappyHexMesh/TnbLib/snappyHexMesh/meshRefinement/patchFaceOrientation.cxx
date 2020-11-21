#include <patchFaceOrientation.hxx>

// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

FoamSnappyHexMesh_EXPORT tnbLib::Ostream& tnbLib::operator<<
(
	tnbLib::Ostream& os,
	const tnbLib::patchFaceOrientation& wDist
	)
{
	return os << wDist.flipStatus_;
}


FoamSnappyHexMesh_EXPORT tnbLib::Istream& tnbLib::operator>>
(
	tnbLib::Istream& is,
	tnbLib::patchFaceOrientation& wDist
	)
{
	return is >> wDist.flipStatus_;
}


// ************************************************************************* //