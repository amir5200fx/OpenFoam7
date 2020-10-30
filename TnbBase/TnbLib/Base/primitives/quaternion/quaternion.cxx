#include <quaternion.hxx>

#include <UList.hxx> // added by amir
#include <IOstreams.hxx>
#include <OStringStream.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

const char* const tnbLib::quaternion::typeName = "quaternion";
const tnbLib::quaternion tnbLib::quaternion::zero(0, vector(0, 0, 0));
const tnbLib::quaternion tnbLib::quaternion::I(1, vector(0, 0, 0));

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::quaternion::quaternion(Istream& is)
{
	is >> *this;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::word tnbLib::name(const quaternion& q)
{
	OStringStream buf;
	buf << '(' << q.w() << ',' << q.v() << ')';
	return buf.str();
}


tnbLib::quaternion tnbLib::slerp
(
	const quaternion& qa,
	const quaternion& qb,
	const scalar t
)
{
	label sign = 1;

	if ((qa & qb) < 0)
	{
		sign = -1;
	}

	return qa * pow((inv(qa)*sign*qb), t);
}


tnbLib::quaternion tnbLib::average
(
	const UList<quaternion>& qs,
	const UList<scalar> w
)
{
	quaternion qa(w[0] * qs[0]);

	for (label i = 1; i < qs.size(); i++)
	{
		// Invert quaternion if it has the opposite sign to the average
		if ((qa & qs[i]) > 0)
		{
			qa += w[i] * qs[i];
		}
		else
		{
			qa -= w[i] * qs[i];
		}
	}

	return qa;
}


tnbLib::quaternion tnbLib::exp(const quaternion& q)
{
	const scalar magV = mag(q.v());

	if (magV == 0)
	{
		return quaternion(1, Zero);
	}

	const scalar expW = exp(q.w());

	return quaternion
	(
		expW*cos(magV),
		expW*sin(magV)*q.v() / magV
	);
}


tnbLib::quaternion tnbLib::pow(const quaternion& q, const label power)
{
	const scalar magQ = mag(q);
	const scalar magV = mag(q.v());

	quaternion powq(q.v());

	if (magV != 0 && magQ != 0)
	{
		powq /= magV;
		powq *= power * acos(q.w() / magQ);
	}

	return pow(magQ, power)*exp(powq);
}


tnbLib::quaternion tnbLib::pow(const quaternion& q, const scalar power)
{
	const scalar magQ = mag(q);
	const scalar magV = mag(q.v());

	quaternion powq(q.v());

	if (magV != 0 && magQ != 0)
	{
		powq /= magV;
		powq *= power * acos(q.w() / magQ);
	}

	return pow(magQ, power)*exp(powq);
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

FoamBase_EXPORT tnbLib::Istream& tnbLib::operator>>(Istream& is, quaternion& q)
{
	// Read beginning of quaternion
	is.readBegin("quaternion");

	is >> q.w() >> q.v();

	// Read end of quaternion
	is.readEnd("quaternion");

	// Check state of Istream
	is.check("operator>>(Istream&, quaternion&)");

	return is;
}


FoamBase_EXPORT tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const quaternion& q)
{
	os << token::BEGIN_LIST
		<< q.w() << token::SPACE << q.v()
		<< token::END_LIST;

	return os;
}


// ************************************************************************* //