#include <pointData.hxx>

// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

FoamSnappyHexMesh_EXPORT tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const pointData& wDist)
{
	if (os.format() == IOstream::ASCII)
	{
		return os
			<< static_cast<const pointEdgePoint&>(wDist)
			<< token::SPACE << wDist.s() << token::SPACE << wDist.v();
	}
	else
	{
		return os
			<< static_cast<const pointEdgePoint&>(wDist)
			<< wDist.s() << wDist.v();
	}
}


FoamSnappyHexMesh_EXPORT tnbLib::Istream& tnbLib::operator>>(Istream& is, pointData& wDist)
{
	return is >> static_cast<pointEdgePoint&>(wDist) >> wDist.s_ >> wDist.v_;
}


// ************************************************************************* //