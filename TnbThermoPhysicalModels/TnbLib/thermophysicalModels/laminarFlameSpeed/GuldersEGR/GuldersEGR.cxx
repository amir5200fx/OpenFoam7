#include <GuldersEGR.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace laminarFlameSpeedModels
	{
		defineTypeNameAndDebug(GuldersEGR, 0);

		addToRunTimeSelectionTable
		(
			laminarFlameSpeed,
			GuldersEGR,
			dictionary
		);
	}
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::laminarFlameSpeedModels::GuldersEGR::GuldersEGR
(
	const dictionary& dict,
	const psiuReactionThermo& ct
)
	:
	laminarFlameSpeed(dict, ct),

	coeffsDict_(dict.optionalSubDict(typeName + "Coeffs").subDict(fuel_)),
	W_(readScalar(coeffsDict_.lookup("W"))),
	eta_(readScalar(coeffsDict_.lookup("eta"))),
	xi_(readScalar(coeffsDict_.lookup("xi"))),
	f_(readScalar(coeffsDict_.lookup("f"))),
	alpha_(readScalar(coeffsDict_.lookup("alpha"))),
	beta_(readScalar(coeffsDict_.lookup("beta")))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::laminarFlameSpeedModels::GuldersEGR::~GuldersEGR()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

inline tnbLib::scalar tnbLib::laminarFlameSpeedModels::GuldersEGR::SuRef
(
	scalar phi
) const
{
	if (phi > small)
	{
		return W_ * pow(phi, eta_)*exp(-xi_ * sqr(phi - 1.075));
	}
	else
	{
		return 0.0;
	}
}


inline tnbLib::scalar tnbLib::laminarFlameSpeedModels::GuldersEGR::Su0pTphi
(
	scalar p,
	scalar Tu,
	scalar phi,
	scalar Yres
) const
{
	static const scalar Tref = 300.0;
	static const scalar pRef = 1.013e5;

	return SuRef(phi)*pow((Tu / Tref), alpha_)*pow((p / pRef), beta_)*(1 - f_ * Yres);
}


tnbLib::tmp<tnbLib::volScalarField>
tnbLib::laminarFlameSpeedModels::GuldersEGR::Su0pTphi
(
	const volScalarField& p,
	const volScalarField& Tu,
	scalar phi
) const
{
	tmp<volScalarField> tSu0
	(
		volScalarField::New
		(
			"Su0",
			p.mesh(),
			dimensionedScalar(dimVelocity, 0)
		)
	);

	volScalarField& Su0 = tSu0.ref();

	forAll(Su0, celli)
	{
		Su0[celli] = Su0pTphi(p[celli], Tu[celli], phi, 0.0);
	}

	volScalarField::Boundary& Su0Bf = Su0.boundaryFieldRef();

	forAll(Su0Bf, patchi)
	{
		forAll(Su0Bf[patchi], facei)
		{
			Su0Bf[patchi][facei] =
				Su0pTphi
				(
					p.boundaryField()[patchi][facei],
					Tu.boundaryField()[patchi][facei],
					phi,
					0.0
				);
		}
	}

	return tSu0;
}


tnbLib::tmp<tnbLib::volScalarField>
tnbLib::laminarFlameSpeedModels::GuldersEGR::Su0pTphi
(
	const volScalarField& p,
	const volScalarField& Tu,
	const volScalarField& phi,
	const volScalarField& egr
) const
{
	tmp<volScalarField> tSu0
	(
		volScalarField::New
		(
			"Su0",
			p.mesh(),
			dimensionedScalar(dimVelocity, 0)
		)
	);

	volScalarField& Su0 = tSu0.ref();

	forAll(Su0, celli)
	{
		Su0[celli] = Su0pTphi(p[celli], Tu[celli], phi[celli], egr[celli]);
	}

	volScalarField::Boundary& Su0Bf = Su0.boundaryFieldRef();

	forAll(Su0Bf, patchi)
	{
		forAll(Su0Bf[patchi], facei)
		{
			Su0Bf[patchi][facei] =
				Su0pTphi
				(
					p.boundaryField()[patchi][facei],
					Tu.boundaryField()[patchi][facei],
					phi.boundaryField()[patchi][facei],
					egr.boundaryField()[patchi][facei]
				);
		}
	}

	return tSu0;
}


tnbLib::tmp<tnbLib::volScalarField>
tnbLib::laminarFlameSpeedModels::GuldersEGR::operator()() const
{
	if
		(
			psiuReactionThermo_.composition().contains("ft")
			&& psiuReactionThermo_.composition().contains("egr")
			)
	{
		return Su0pTphi
		(
			psiuReactionThermo_.p(),
			psiuReactionThermo_.Tu(),
			dimensionedScalar
			(
				psiuReactionThermo_.lookup("stoichiometricAirFuelMassRatio")
			) /
			(
				scalar(1) / psiuReactionThermo_.composition().Y("ft")
				- scalar(1)
				),
			psiuReactionThermo_.composition().Y("egr")
		);
	}
	else
	{
		return Su0pTphi
		(
			psiuReactionThermo_.p(),
			psiuReactionThermo_.Tu(),
			equivalenceRatio_
		);
	}
}


// ************************************************************************* //