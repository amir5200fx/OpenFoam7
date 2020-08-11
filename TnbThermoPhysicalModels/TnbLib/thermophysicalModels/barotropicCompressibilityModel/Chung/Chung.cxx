#include <Chung.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace compressibilityModels
	{
		defineTypeNameAndDebug(Chung, 0);
		addToRunTimeSelectionTable
		(
			barotropicCompressibilityModel,
			Chung,
			dictionary
		);
	}
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::compressibilityModels::Chung::Chung
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

void tnbLib::compressibilityModels::Chung::correct()
{
	volScalarField sfa
	(
		sqrt
		(
		(rhovSat_ / psiv_)
			/ ((scalar(1) - gamma_)*rhovSat_ / psiv_ + gamma_ * rholSat_ / psil_)
		)
	);

	psi_ = sqr
	(
		((scalar(1) - gamma_) / sqrt(psiv_) + gamma_ * sfa / sqrt(psil_))
		*sqrt(psiv_*psil_) / sfa
	);
}


bool tnbLib::compressibilityModels::Chung::read
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