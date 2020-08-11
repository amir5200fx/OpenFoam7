#include <viscosityModelCasson.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <surfaceFields.hxx>

#include <Time.hxx> // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace viscosityModels
	{
		defineTypeNameAndDebug(Casson, 0);
		addToRunTimeSelectionTable
		(
			viscosityModel,
			Casson,
			dictionary
		);
	}
}


// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField>
tnbLib::viscosityModels::Casson::calcNu() const
{
	return max
	(
		nuMin_,
		min
		(
			nuMax_,
			sqr
			(
				sqrt
				(
					tau0_
					/ max
					(
						strainRate(),
						dimensionedScalar(dimless / dimTime, vSmall)
					)
				) + sqrt(m_)
			)
		)
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::viscosityModels::Casson::Casson
(
	const word& name,
	const dictionary& viscosityProperties,
	const volVectorField& U,
	const surfaceScalarField& phi
)
	:
	viscosityModel(name, viscosityProperties, U, phi),
	CassonCoeffs_(viscosityProperties.optionalSubDict(typeName + "Coeffs")),
	m_("m", dimViscosity, CassonCoeffs_),
	tau0_("tau0", dimViscosity / dimTime, CassonCoeffs_),
	nuMin_("nuMin", dimViscosity, CassonCoeffs_),
	nuMax_("nuMax", dimViscosity, CassonCoeffs_),
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

bool tnbLib::viscosityModels::Casson::read
(
	const dictionary& viscosityProperties
)
{
	viscosityModel::read(viscosityProperties);

	CassonCoeffs_ = viscosityProperties.optionalSubDict(typeName + "Coeffs");

	CassonCoeffs_.lookup("m") >> m_;
	CassonCoeffs_.lookup("tau0") >> tau0_;
	CassonCoeffs_.lookup("nuMin_") >> nuMin_;
	CassonCoeffs_.lookup("nuMax_") >> nuMax_;

	return true;
}


// ************************************************************************* //