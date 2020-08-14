#include <PengRobinsonGas.hxx>

#include <IOstreams.hxx>
#include <dictionary.hxx>  // added by amir
#include <thermodynamicConstants.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Specie>
tnbLib::PengRobinsonGas<Specie>::PengRobinsonGas
(
	const dictionary& dict
)
	:
	Specie(dict),
	Tc_(readScalar(dict.subDict("equationOfState").lookup("Tc"))),
	Vc_(readScalar(dict.subDict("equationOfState").lookup("Vc"))),
	Zc_(1.0),
	Pc_(readScalar(dict.subDict("equationOfState").lookup("Pc"))),
	omega_(readScalar(dict.subDict("equationOfState").lookup("omega")))
{
	Zc_ = Pc_ * Vc_ / (constant::thermodynamic::RR*Tc_);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //


template<class Specie>
void tnbLib::PengRobinsonGas<Specie>::write(Ostream& os) const
{
	Specie::write(os);
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

template<class Specie>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const PengRobinsonGas<Specie>& pg
	)
{
	pg.write(os);
	return os;
}


// ************************************************************************* //