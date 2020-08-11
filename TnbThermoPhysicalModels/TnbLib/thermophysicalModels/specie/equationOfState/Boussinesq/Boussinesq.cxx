#include <Boussinesq.hxx>

#include <IOstreams.hxx>
#include <dictionary.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Specie>
tnbLib::Boussinesq<Specie>::Boussinesq
(
	const dictionary& dict
)
	:
	Specie(dict),
	rho0_(readScalar(dict.subDict("equationOfState").lookup("rho0"))),
	T0_(readScalar(dict.subDict("equationOfState").lookup("T0"))),
	beta_(readScalar(dict.subDict("equationOfState").lookup("beta")))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Specie>
void tnbLib::Boussinesq<Specie>::write(Ostream& os) const
{
	Specie::write(os);
	dictionary dict("equationOfState");
	dict.add("rho0", rho0_);
	dict.add("T0", T0_);
	dict.add("beta", beta_);

	os << indent << dict.dictName() << dict;
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

template<class Specie>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const Boussinesq<Specie>& b
	)
{
	b.write(os);
	return os;
}


// ************************************************************************* //