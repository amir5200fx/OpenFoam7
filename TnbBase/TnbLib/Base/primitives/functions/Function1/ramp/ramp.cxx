#include <ramp.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

void tnbLib::Function1Types::ramp::read(const dictionary& coeffs)
{
	start_ = coeffs.lookupOrDefault<scalar>("start", 0);
	duration_ = coeffs.lookupType<scalar>("duration");
}


tnbLib::Function1Types::ramp::ramp
(
	const word& entryName,
	const dictionary& dict
)
	:
	Function1<scalar>(entryName)
{
	read(dict);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::Function1Types::ramp::~ramp()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::Function1Types::ramp::writeData(Ostream& os) const
{
	Function1<scalar>::writeData(os);
	os << token::END_STATEMENT << nl;
	os << indent << word(this->name() + "Coeffs") << nl;
	os << indent << token::BEGIN_BLOCK << incrIndent << nl;
	writeEntry(os, "start", start_);
	writeEntry(os, "duration", duration_);
	os << decrIndent << indent << token::END_BLOCK << endl;
}


// ************************************************************************* //