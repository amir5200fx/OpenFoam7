#pragma once
#include <IOstreams.hxx>  // added by amir
#include <dictionary.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Specie>
tnbLib::linear<Specie>::linear(const dictionary& dict)
	:
	Specie(dict),
	psi_(readScalar(dict.subDict("equationOfState").lookup("psi"))),
	rho0_(readScalar(dict.subDict("equationOfState").lookup("rho0")))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Specie>
void tnbLib::linear<Specie>::write(Ostream& os) const
{
	Specie::write(os);

	dictionary dict("equationOfState");
	dict.add("psi", psi_);
	dict.add("rho0", rho0_);

	os << indent << dict.dictName() << dict;
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

template<class Specie>
tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const linear<Specie>& pf)
{
	pf.write(os);
	return os;
}


// ************************************************************************* //