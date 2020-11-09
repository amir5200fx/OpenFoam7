#include <Gulders.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace laminarFlameSpeedModels
	{
		defineTypeNameAndDebug(Gulders, 0);

		addToRunTimeSelectionTable
		(
			laminarFlameSpeed,
			Gulders,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::laminarFlameSpeedModels::Gulders::Gulders
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

tnbLib::laminarFlameSpeedModels::Gulders::~Gulders()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

tnbLib::scalar tnbLib::laminarFlameSpeedModels::Gulders::SuRef
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


tnbLib::scalar tnbLib::laminarFlameSpeedModels::Gulders::Su0pTphi
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


tnbLib::tmp<tnbLib::volScalarField> tnbLib::laminarFlameSpeedModels::Gulders::Su0pTphi
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


tnbLib::tmp<tnbLib::volScalarField> tnbLib::laminarFlameSpeedModels::Gulders::Su0pTphi
(
	const volScalarField& p,
	const volScalarField& Tu,
	const volScalarField& phi
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
		Su0[celli] = Su0pTphi(p[celli], Tu[celli], phi[celli], 0.0);
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
					0.0
				);
		}
	}

	return tSu0;
}


tnbLib::tmp<tnbLib::volScalarField>
tnbLib::laminarFlameSpeedModels::Gulders::operator()() const
{
	if (psiuReactionThermo_.composition().contains("ft"))
	{
		const volScalarField& ft = psiuReactionThermo_.composition().Y("ft");

		return Su0pTphi
		(
			psiuReactionThermo_.p(),
			psiuReactionThermo_.Tu(),
			dimensionedScalar
			(
				psiuReactionThermo_.lookup("stoichiometricAirFuelMassRatio")
			)*ft / max(1 - ft, small)
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