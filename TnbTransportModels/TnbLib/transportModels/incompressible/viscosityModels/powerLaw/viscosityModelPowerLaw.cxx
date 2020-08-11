#include <viscosityModelPowerLaw.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <surfaceFields.hxx>

#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace viscosityModels
	{
		defineTypeNameAndDebug(powerLaw, 0);

		addToRunTimeSelectionTable
		(
			viscosityModel,
			powerLaw,
			dictionary
		);
	}
}


// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField>
tnbLib::viscosityModels::powerLaw::calcNu() const
{
	return max
	(
		nuMin_,
		min
		(
			nuMax_,
			k_*pow
			(
				max
				(
					dimensionedScalar(dimTime, 1.0)*strainRate(),
					dimensionedScalar(dimless, small)
				),
				n_.value() - scalar(1)
			)
		)
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::viscosityModels::powerLaw::powerLaw
(
	const word& name,
	const dictionary& viscosityProperties,
	const volVectorField& U,
	const surfaceScalarField& phi
)
	:
	viscosityModel(name, viscosityProperties, U, phi),
	powerLawCoeffs_(viscosityProperties.optionalSubDict(typeName + "Coeffs")),
	k_("k", dimViscosity, powerLawCoeffs_),
	n_("n", dimless, powerLawCoeffs_),
	nuMin_("nuMin", dimViscosity, powerLawCoeffs_),
	nuMax_("nuMax", dimViscosity, powerLawCoeffs_),
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

bool tnbLib::viscosityModels::powerLaw::read
(
	const dictionary& viscosityProperties
)
{
	viscosityModel::read(viscosityProperties);

	powerLawCoeffs_ = viscosityProperties.optionalSubDict(typeName + "Coeffs");

	powerLawCoeffs_.lookup("k") >> k_;
	powerLawCoeffs_.lookup("n") >> n_;
	powerLawCoeffs_.lookup("nuMin") >> nuMin_;
	powerLawCoeffs_.lookup("nuMax") >> nuMax_;

	return true;
}


// ************************************************************************* //