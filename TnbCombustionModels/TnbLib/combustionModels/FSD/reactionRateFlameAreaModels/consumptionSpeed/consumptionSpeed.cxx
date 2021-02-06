#include <consumptionSpeed.hxx>

/* * * * * * * * * * * * * * * private static data * * * * * * * * * * * * * */

namespace tnbLib
{
	defineTypeNameAndDebug(consumptionSpeed, 0);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::consumptionSpeed::consumptionSpeed
(
	const dictionary& dict
)
	: omega0_(readScalar(dict.lookup("omega0"))),
	eta_(readScalar(dict.lookup("eta"))),
	sigmaExt_(readScalar(dict.lookup("sigmaExt"))),
	omegaMin_(readScalar(dict.lookup("omegaMin")))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::consumptionSpeed::~consumptionSpeed()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

tnbLib::scalar tnbLib::consumptionSpeed::omega0Sigma
(
	scalar sigma,
	scalar a
) const
{
	scalar omega0 = 0.0;

	if (sigma < sigmaExt_)
	{
		omega0 = max
		(
			a*omega0_*(1.0 - exp(eta_*max(sigma, 0.0))),
			omegaMin_
		);
	}

	return omega0;
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::consumptionSpeed::omega0Sigma
(
	const volScalarField& sigma
)
{
	tmp<volScalarField> tomega0
	(
		volScalarField::New
		(
			"omega0",
			sigma.mesh(),
			dimensionedScalar
			(
				dimensionSet(1, -2, -1, 0, 0, 0, 0),
				0
			)
		)
	);

	volScalarField& omega0 = tomega0.ref();

	volScalarField::Internal& iomega0 = omega0;

	forAll(iomega0, celli)
	{
		iomega0[celli] = omega0Sigma(sigma[celli], 1.0);
	}

	volScalarField::Boundary& bomega0 = omega0.boundaryFieldRef();

	forAll(bomega0, patchi)
	{
		forAll(bomega0[patchi], facei)
		{
			bomega0[patchi][facei] =
				omega0Sigma
				(
					sigma.boundaryField()[patchi][facei],
					1.0
				);
		}
	}

	return tomega0;
}


void  tnbLib::consumptionSpeed::read(const dictionary& dict)
{
	dict.lookup("omega0") >> omega0_;
	dict.lookup("eta") >> eta_;
	dict.lookup("sigmaExt") >> sigmaExt_;
	dict.lookup("omegaMin") >> omegaMin_;
}


// ************************************************************************* //