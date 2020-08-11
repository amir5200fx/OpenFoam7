#include <viscosityModelHerschelBulkley.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <surfaceFields.hxx>

#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace viscosityModels
	{
		defineTypeNameAndDebug(HerschelBulkley, 0);

		addToRunTimeSelectionTable
		(
			viscosityModel,
			HerschelBulkley,
			dictionary
		);
	}
}


// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField>
tnbLib::viscosityModels::HerschelBulkley::calcNu() const
{
	dimensionedScalar tone("tone", dimTime, 1.0);
	dimensionedScalar rtone("rtone", dimless / dimTime, 1.0);

	tmp<volScalarField> sr(strainRate());

	return
		(
			min
			(
				nu0_,
				(tau0_ + k_ * rtone*pow(tone*sr(), n_))
				/ (max(sr(), dimensionedScalar("vSmall", dimless / dimTime, vSmall)))
			)
			);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::viscosityModels::HerschelBulkley::HerschelBulkley
(
	const word& name,
	const dictionary& viscosityProperties,
	const volVectorField& U,
	const surfaceScalarField& phi
)
	:
	viscosityModel(name, viscosityProperties, U, phi),
	HerschelBulkleyCoeffs_
	(
		viscosityProperties.optionalSubDict(typeName + "Coeffs")
	),
	k_("k", dimViscosity, HerschelBulkleyCoeffs_),
	n_("n", dimless, HerschelBulkleyCoeffs_),
	tau0_("tau0", dimViscosity / dimTime, HerschelBulkleyCoeffs_),
	nu0_("nu0", dimViscosity, HerschelBulkleyCoeffs_),
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

bool tnbLib::viscosityModels::HerschelBulkley::read
(
	const dictionary& viscosityProperties
)
{
	viscosityModel::read(viscosityProperties);

	HerschelBulkleyCoeffs_ =
		viscosityProperties.optionalSubDict(typeName + "Coeffs");

	HerschelBulkleyCoeffs_.lookup("k") >> k_;
	HerschelBulkleyCoeffs_.lookup("n") >> n_;
	HerschelBulkleyCoeffs_.lookup("tau0") >> tau0_;
	HerschelBulkleyCoeffs_.lookup("nu0") >> nu0_;

	return true;
}


// ************************************************************************* //