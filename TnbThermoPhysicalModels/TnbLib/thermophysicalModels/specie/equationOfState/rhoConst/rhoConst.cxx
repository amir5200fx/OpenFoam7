#include <rhoConst.hxx>

#include <IOstreams.hxx>
#include <dictionary.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Specie>
tnbLib::rhoConst<Specie>::rhoConst(const dictionary& dict)
	:
	Specie(dict),
	rho_(readScalar(dict.subDict("equationOfState").lookup("rho")))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Specie>
void tnbLib::rhoConst<Specie>::write(Ostream& os) const
{
	Specie::write(os);

	dictionary dict("equationOfState");
	dict.add("rho", rho_);

	os << indent << dict.dictName() << dict;
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

template<class Specie>
tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const rhoConst<Specie>& ico)
{
	ico.write(os);
	return os;
}


// ************************************************************************* //