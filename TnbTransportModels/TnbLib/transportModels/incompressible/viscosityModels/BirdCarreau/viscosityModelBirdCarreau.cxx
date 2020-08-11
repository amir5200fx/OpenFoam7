#include <viscosityModelBirdCarreau.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <surfaceFields.hxx>

#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace viscosityModels
	{
		defineTypeNameAndDebug(BirdCarreau, 0);
		addToRunTimeSelectionTable
		(
			viscosityModel,
			BirdCarreau,
			dictionary
		);
	}
}


// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField>
tnbLib::viscosityModels::BirdCarreau::calcNu() const
{
	return
		nuInf_
		+ (nu0_ - nuInf_)
		*pow(scalar(1) + pow(k_*strainRate(), a_), (n_ - 1.0) / a_);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::viscosityModels::BirdCarreau::BirdCarreau
(
	const word& name,
	const dictionary& viscosityProperties,
	const volVectorField& U,
	const surfaceScalarField& phi
)
	:
	viscosityModel(name, viscosityProperties, U, phi),
	BirdCarreauCoeffs_
	(
		viscosityProperties.optionalSubDict(typeName + "Coeffs")
	),
	nu0_("nu0", dimViscosity, BirdCarreauCoeffs_),
	nuInf_("nuInf", dimViscosity, BirdCarreauCoeffs_),
	k_("k", dimTime, BirdCarreauCoeffs_),
	n_("n", dimless, BirdCarreauCoeffs_),
	a_
	(
		BirdCarreauCoeffs_.lookupOrDefault
		(
			"a",
			dimensionedScalar("a", dimless, 2)
		)
	),
	nu_
	(
		IOobject
		(
			"nu",
			U_.time().timeName(),
			U_.db(),
			IOobject::NO_READ,
			IOobject::AUTO_WRITE
		),
		calcNu()
	)
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool tnbLib::viscosityModels::BirdCarreau::read
(
	const dictionary& viscosityProperties
)
{
	viscosityModel::read(viscosityProperties);

	BirdCarreauCoeffs_ =
		viscosityProperties.optionalSubDict(typeName + "Coeffs");

	BirdCarreauCoeffs_.lookup("nu0") >> nu0_;
	BirdCarreauCoeffs_.lookup("nuInf") >> nuInf_;
	BirdCarreauCoeffs_.lookup("k") >> k_;
	BirdCarreauCoeffs_.lookup("n") >> n_;
	a_ = BirdCarreauCoeffs_.lookupOrDefault
	(
		"a",
		dimensionedScalar("a", dimless, 2)
	);

	return true;
}


// ************************************************************************* //