#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class ReactionThermo>
tnbLib::combustionModels::PaSR<ReactionThermo>::PaSR
(
	const word& modelType,
	ReactionThermo& thermo,
	const compressibleTurbulenceModel& turb,
	const word& combustionProperties
)
	:
	laminar<ReactionThermo>(modelType, thermo, turb, combustionProperties),
	Cmix_(readScalar(this->coeffs().lookup("Cmix"))),
	kappa_
	(
		IOobject
		(
			thermo.phasePropertyName(typeName + ":kappa"),
			this->mesh().time().timeName(),
			this->mesh(),
			IOobject::NO_READ,
			IOobject::AUTO_WRITE
		),
		this->mesh(),
		dimensionedScalar(dimless, 0)
	)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class ReactionThermo>
tnbLib::combustionModels::PaSR<ReactionThermo>::~PaSR()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

template<class ReactionThermo>
void tnbLib::combustionModels::PaSR<ReactionThermo>::correct()
{
	laminar<ReactionThermo>::correct();

	tmp<volScalarField> tepsilon(this->turbulence().epsilon());
	const scalarField& epsilon = tepsilon();

	tmp<volScalarField> tmuEff(this->turbulence().muEff());
	const scalarField& muEff = tmuEff();

	tmp<volScalarField> ttc(this->tc());
	const scalarField& tc = ttc();

	tmp<volScalarField> trho(this->rho());
	const scalarField& rho = trho();

	forAll(epsilon, i)
	{
		const scalar tk =
			Cmix_ * sqrt(max(muEff[i] / rho[i] / (epsilon[i] + small), 0));

		if (tk > small)
		{
			kappa_[i] = tc[i] / (tc[i] + tk);
		}
		else
		{
			kappa_[i] = 1.0;
		}
	}
}


template<class ReactionThermo>
tnbLib::tmp<tnbLib::fvScalarMatrix>
tnbLib::combustionModels::PaSR<ReactionThermo>::R(volScalarField& Y) const
{
	return kappa_ * laminar<ReactionThermo>::R(Y);
}


template<class ReactionThermo>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::combustionModels::PaSR<ReactionThermo>::Qdot() const
{
	return volScalarField::New
	(
		this->thermo().phasePropertyName(typeName + ":Qdot"),
		kappa_*laminar<ReactionThermo>::Qdot()
	);
}


template<class ReactionThermo>
bool tnbLib::combustionModels::PaSR<ReactionThermo>::read()
{
	if (laminar<ReactionThermo>::read())
	{
		this->coeffs().lookup("Cmix") >> Cmix_;
		return true;
	}
	else
	{
		return false;
	}
}


// ************************************************************************* //