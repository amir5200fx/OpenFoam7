#include <perfectFluid.hxx>

#include <IOstreams.hxx>
#include <dictionary.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Specie>
tnbLib::perfectFluid<Specie>::perfectFluid(const dictionary& dict)
	:
	Specie(dict),
	R_(readScalar(dict.subDict("equationOfState").lookup("R"))),
	rho0_(readScalar(dict.subDict("equationOfState").lookup("rho0")))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Specie>
void tnbLib::perfectFluid<Specie>::write(Ostream& os) const
{
	Specie::write(os);

	dictionary dict("equationOfState");
	dict.add("R", R_);
	dict.add("rho0", rho0_);

	os << indent << dict.dictName() << dict;
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

template<class Specie>
tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const perfectFluid<Specie>& pf)
{
	pf.write(os);
	return os;
}


// ************************************************************************* //