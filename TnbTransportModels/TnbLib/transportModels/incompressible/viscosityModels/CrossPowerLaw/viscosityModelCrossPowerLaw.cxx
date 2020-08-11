#include <viscosityModelCrossPowerLaw.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <surfaceFields.hxx>

#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace viscosityModels
	{
		defineTypeNameAndDebug(CrossPowerLaw, 0);

		addToRunTimeSelectionTable
		(
			viscosityModel,
			CrossPowerLaw,
			dictionary
		);
	}
}


// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField>
tnbLib::viscosityModels::CrossPowerLaw::calcNu() const
{
	return (nu0_ - nuInf_) / (scalar(1) + pow(m_*strainRate(), n_)) + nuInf_;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::viscosityModels::CrossPowerLaw::CrossPowerLaw
(
	const word& name,
	const dictionary& viscosityProperties,
	const volVectorField& U,
	const surfaceScalarField& phi
)
	:
	viscosityModel(name, viscosityProperties, U, phi),
	CrossPowerLawCoeffs_
	(
		viscosityProperties.optionalSubDict(typeName + "Coeffs")
	),
	nu0_("nu0", dimViscosity, CrossPowerLawCoeffs_),
	nuInf_("nuInf", dimViscosity, CrossPowerLawCoeffs_),
	m_("m", dimTime, CrossPowerLawCoeffs_),
	n_("n", dimless, CrossPowerLawCoeffs_),
	nu_
	(
		IOobject
		(
			name,
			U_.time().timeName(),
			U_.db(),
			IOobject::NO_READ,
			IOobject::AUTO_WRITE
		),
		calcNu()
	)
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool tnbLib::viscosityModels::CrossPowerLaw::read
(
	const dictionary& viscosityProperties
)
{
	viscosityModel::read(viscosityProperties);

	CrossPowerLawCoeffs_ =
		viscosityProperties.optionalSubDict(typeName + "Coeffs");

	CrossPowerLawCoeffs_.lookup("nu0") >> nu0_;
	CrossPowerLawCoeffs_.lookup("nuInf") >> nuInf_;
	CrossPowerLawCoeffs_.lookup("m") >> m_;
	CrossPowerLawCoeffs_.lookup("n") >> n_;

	return true;
}


// ************************************************************************* //