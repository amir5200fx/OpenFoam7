#include <solidProperties.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(solidProperties, 0);
	defineRunTimeSelectionTable(solidProperties, );
	defineRunTimeSelectionTable(solidProperties, dictionary);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::solidProperties::solidProperties
(
	scalar rho,
	scalar Cp,
	scalar kappa,
	scalar Hf,
	scalar emissivity
)
	:
	rho_(rho),
	Cp_(Cp),
	kappa_(kappa),
	Hf_(Hf),
	emissivity_(emissivity)
{}


tnbLib::solidProperties::solidProperties(const dictionary& dict)
	:
	rho_(readScalar(dict.lookup("rho"))),
	Cp_(readScalar(dict.lookup("Cp"))),
	kappa_
	(
		dict.found("K")
		? readScalar(dict.lookup("K"))
		: readScalar(dict.lookup("kappa"))
	),
	Hf_(readScalar(dict.lookup("Hf"))),
	emissivity_(readScalar(dict.lookup("emissivity")))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::solidProperties::readIfPresent(const dictionary& dict)
{
	dict.readIfPresent("rho", rho_);
	dict.readIfPresent("Cp", Cp_);
	dict.readIfPresent("K", kappa_);
	dict.readIfPresent("kappa", kappa_);
	dict.readIfPresent("Hf_", Hf_);
	dict.readIfPresent("emissivity", emissivity_);
}


void tnbLib::solidProperties::writeData(Ostream& os) const
{
	os << rho_ << token::SPACE
		<< Cp_ << token::SPACE
		<< kappa_ << token::SPACE
		<< Hf_ << token::SPACE
		<< emissivity_;
}


// * * * * * * * * * * * * * * IOStream operators  * * * * * * * * * * * * * //

FoamThermophysicalModels_EXPORT tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const solidProperties& s)
{
	s.writeData(os);
	return os;
}


// ************************************************************************* //