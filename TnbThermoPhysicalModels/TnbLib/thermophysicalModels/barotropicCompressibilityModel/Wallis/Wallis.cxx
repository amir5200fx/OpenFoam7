#include <Wallis.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace compressibilityModels
	{
		defineTypeNameAndDebug(Wallis, 0);
		addToRunTimeSelectionTable
		(
			barotropicCompressibilityModel,
			Wallis,
			dictionary
		);
	}
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::compressibilityModels::Wallis::Wallis
(
	const dictionary& compressibilityProperties,
	const volScalarField& gamma,
	const word& psiName
)
	:
	barotropicCompressibilityModel(compressibilityProperties, gamma, psiName),
	psiv_
	(
		"psiv",
		dimCompressibility,
		compressibilityProperties_.lookup("psiv")
	),
	psil_
	(
		"psil",
		dimCompressibility,
		compressibilityProperties_.lookup("psil")
	),
	rhovSat_
	(
		"rhovSat",
		dimDensity,
		compressibilityProperties_.lookup("rhovSat")
	),
	rholSat_
	(
		"rholSat",
		dimDensity,
		compressibilityProperties_.lookup("rholSat")
	)
{
	correct();
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void tnbLib::compressibilityModels::Wallis::correct()
{
	psi_ =
		(gamma_*rhovSat_ + (scalar(1) - gamma_)*rholSat_)
		*(gamma_*psiv_ / rhovSat_ + (scalar(1) - gamma_)*psil_ / rholSat_);
}


bool tnbLib::compressibilityModels::Wallis::read
(
	const dictionary& compressibilityProperties
)
{
	barotropicCompressibilityModel::read(compressibilityProperties);

	compressibilityProperties_.lookup("psiv") >> psiv_;
	compressibilityProperties_.lookup("psil") >> psil_;
	compressibilityProperties_.lookup("rhovSat") >> rhovSat_;
	compressibilityProperties_.lookup("rholSat") >> rholSat_;

	return true;
}


// ************************************************************************* //