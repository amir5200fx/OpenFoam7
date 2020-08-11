#include <linearBarotropicCompressibilityModel.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace compressibilityModels
	{
		defineTypeNameAndDebug(linear, 0);
		addToRunTimeSelectionTable
		(
			barotropicCompressibilityModel,
			linear,
			dictionary
		);
	}
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::compressibilityModels::linear::linear
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
	)
{
	correct();
	psi_.oldTime();
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void tnbLib::compressibilityModels::linear::correct()
{
	psi_ = gamma_ * psiv_ + (scalar(1) - gamma_)*psil_;
}


bool tnbLib::compressibilityModels::linear::read
(
	const dictionary& compressibilityProperties
)
{
	barotropicCompressibilityModel::read(compressibilityProperties);

	compressibilityProperties_.lookup("psiv") >> psiv_;
	compressibilityProperties_.lookup("psil") >> psil_;

	return true;
}


// ************************************************************************* //