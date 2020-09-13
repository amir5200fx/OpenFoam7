#include <patchFaceOrientation.hxx>

// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<
(
	tnbLib::Ostream& os,
	const tnbLib::patchFaceOrientation& wDist
	)
{
	return os << wDist.flipStatus_;
}


tnbLib::Istream& tnbLib::operator>>
(
	tnbLib::Istream& is,
	tnbLib::patchFaceOrientation& wDist
	)
{
	return is >> wDist.flipStatus_;
}


// ************************************************************************* //