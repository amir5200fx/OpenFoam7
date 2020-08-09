#include <curve.hxx>

#include <Ostream.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::curve::curve
(
	const string& name,
	const curveStyle& style,
	const label l
)
	:
	scalarField(l, 0.0),
	name_(name),
	style_(style)
{}


tnbLib::curve::curve
(
	const string& name,
	const curveStyle& style,
	const scalarField& y
)
	:
	scalarField(y),
	name_(name),
	style_(style)
{}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const curve& c)
{
	os << nl
		<< c.name_ << nl
		<< c.style_ << nl
		<< static_cast<const scalarField&>(c);

	os.check("Ostream& operator>>(Ostream&, const curve&)");

	return os;
}


// ************************************************************************* //