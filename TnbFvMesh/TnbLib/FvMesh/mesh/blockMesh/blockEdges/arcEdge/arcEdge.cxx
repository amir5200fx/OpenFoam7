#include <arcEdge.hxx>

#include <unitConversion.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace blockEdges
	{
		defineTypeNameAndDebug(arcEdge, 0);
		addToRunTimeSelectionTable(blockEdge, arcEdge, Istream);
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

tnbLib::cylindricalCS tnbLib::blockEdges::arcEdge::calcAngle()
{
	vector a = p2_ - p1_;
	vector b = p3_ - p1_;

	// find centre of arcEdge
	scalar asqr = a & a;
	scalar bsqr = b & b;
	scalar adotb = a & b;

	scalar denom = asqr * bsqr - adotb * adotb;

	if (mag(denom) < vSmall)
	{
		FatalErrorInFunction
			<< denom
			<< abort(FatalError);
	}

	scalar fact = 0.5*(bsqr - adotb) / denom;

	point centre = 0.5*a + fact * ((a ^ b) ^ a);

	centre += p1_;

	// find position vectors w.r.t. the arcEdge centre
	vector r1(p1_ - centre);
	vector r2(p2_ - centre);
	vector r3(p3_ - centre);

	// find angles
	const scalar cosAngle = (r3 & r1) / (mag(r3) * mag(r1));
	angle_ = radToDeg(acos(max(-1, min(cosAngle, 1))));

	// check if the vectors define an exterior or an interior arcEdge
	if (((r1 ^ r2) & (r1 ^ r3)) < 0.0)
	{
		angle_ = 360.0 - angle_;
	}

	vector tempAxis;

	if (angle_ <= 180.0)
	{
		tempAxis = r1 ^ r3;

		if (mag(tempAxis) / (mag(r1)*mag(r3)) < 0.001)
		{
			tempAxis = r1 ^ r2;
		}
	}
	else
	{
		tempAxis = r3 ^ r1;
	}

	radius_ = mag(r3);

	// set up and return the local coordinate system
	return cylindricalCS("arcEdgeCS", centre, tempAxis, r1);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::blockEdges::arcEdge::arcEdge
(
	const pointField& points,
	const label start,
	const label end,
	const point& pMid
)
	:
	blockEdge(points, start, end),
	p1_(points_[start_]),
	p2_(pMid),
	p3_(points_[end_]),
	cs_(calcAngle())
{}


tnbLib::blockEdges::arcEdge::arcEdge
(
	const dictionary& dict,
	const label index,
	const searchableSurfaces& geometry,
	const pointField& points,
	Istream& is
)
	:
	blockEdge(dict, index, points, is),
	p1_(points_[start_]),
	p2_(is),
	p3_(points_[end_]),
	cs_(calcAngle())
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::point tnbLib::blockEdges::arcEdge::position(const scalar lambda) const
{
	if (lambda < -small || lambda > 1 + small)
	{
		FatalErrorInFunction
			<< "Parameter out of range, lambda = " << lambda
			<< abort(FatalError);
	}

	if (lambda < small)
	{
		return p1_;
	}
	else if (lambda > 1 - small)
	{
		return p3_;
	}
	else
	{
		return cs_.globalPosition(vector(radius_, lambda*angle_, 0.0));
	}
}


tnbLib::scalar tnbLib::blockEdges::arcEdge::length() const
{
	return degToRad(angle_*radius_);
}


// ************************************************************************* //