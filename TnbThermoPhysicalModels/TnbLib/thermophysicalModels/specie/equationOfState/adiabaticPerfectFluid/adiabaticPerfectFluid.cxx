#include <adiabaticPerfectFluid.hxx>

#include <IOstreams.hxx>
#include <dictionary.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Specie>
tnbLib::adiabaticPerfectFluid<Specie>::adiabaticPerfectFluid
(
	const dictionary& dict
)
	:
	Specie(dict),
	p0_(readScalar(dict.subDict("equationOfState").lookup("p0"))),
	rho0_(readScalar(dict.subDict("equationOfState").lookup("rho0"))),
	gamma_(readScalar(dict.subDict("equationOfState").lookup("gamma"))),
	B_(readScalar(dict.subDict("equationOfState").lookup("B")))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Specie>
void tnbLib::adiabaticPerfectFluid<Specie>::write(Ostream& os) const
{
	Specie::write(os);

	dictionary dict("equationOfState");
	dict.add("p0", p0_);
	dict.add("rho0", rho0_);
	dict.add("gamma", gamma_);
	dict.add("B", B_);

	os << indent << dict.dictName() << dict;
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

template<class Specie>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const adiabaticPerfectFluid<Specie>& pf
	)
{
	pf.write(os);
	return os;
}


// ************************************************************************* //