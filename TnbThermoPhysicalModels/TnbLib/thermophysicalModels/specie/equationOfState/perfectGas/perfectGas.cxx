#include <perfectGas.hxx>

#include <IOstreams.hxx>
#include <dictionary.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Specie>
tnbLib::perfectGas<Specie>::perfectGas(const dictionary& dict)
	:
	Specie(dict)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Specie>
void tnbLib::perfectGas<Specie>::write(Ostream& os) const
{
	Specie::write(os);
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

template<class Specie>
tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const perfectGas<Specie>& pg)
{
	pg.write(os);
	return os;
}


// ************************************************************************* //