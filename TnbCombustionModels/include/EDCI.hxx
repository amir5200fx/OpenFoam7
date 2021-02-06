#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class ReactionThermo>
tnbLib::combustionModels::EDC<ReactionThermo>::EDC
(
	const word& modelType,
	ReactionThermo& thermo,
	const compressibleTurbulenceModel& turb,
	const word& combustionProperties
)
	:
	laminar<ReactionThermo>(modelType, thermo, turb, combustionProperties),
	version_
	(
		EDCversionNames
		[
			this->coeffs().lookupOrDefault
			(
				"version",
				word(EDCversionNames[EDCdefaultVersion])
			)
		]
),
C1_(this->coeffs().lookupOrDefault("C1", 0.05774)),
C2_(this->coeffs().lookupOrDefault("C2", 0.5)),
Cgamma_(this->coeffs().lookupOrDefault("Cgamma", 2.1377)),
Ctau_(this->coeffs().lookupOrDefault("Ctau", 0.4083)),
exp1_(this->coeffs().lookupOrDefault("exp1", EDCexp1[int(version_)])),
exp2_(this->coeffs().lookupOrDefault("exp2", EDCexp2[int(version_)])),
kappa_
(
	IOobject
	(
		this->thermo().phasePropertyName(typeName + ":kappa"),
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
tnbLib::combustionModels::EDC<ReactionThermo>::~EDC()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

template<class ReactionThermo>
void tnbLib::combustionModels::EDC<ReactionThermo>::correct()
{
	tmp<volScalarField> tepsilon(this->turbulence().epsilon());
	const volScalarField& epsilon = tepsilon();

	tmp<volScalarField> tmu(this->turbulence().mu());
	const volScalarField& mu = tmu();

	tmp<volScalarField> tk(this->turbulence().k());
	const volScalarField& k = tk();

	tmp<volScalarField> trho(this->rho());
	const volScalarField& rho = trho();

	scalarField tauStar(epsilon.size(), 0);

	if (version_ == EDCversions::v2016)
	{
		tmp<volScalarField> ttc(this->chemistryPtr_->tc());
		const volScalarField& tc = ttc();

		forAll(tauStar, i)
		{
			const scalar nu = mu[i] / (rho[i] + small);

			const scalar Da =
				max(min(sqrt(nu / (epsilon[i] + small)) / tc[i], 10), 1e-10);

			const scalar ReT = sqr(k[i]) / (nu*epsilon[i] + small);
			const scalar CtauI = min(C1_ / (Da*sqrt(ReT + 1)), 2.1377);

			const scalar CgammaI =
				max(min(C2_*sqrt(Da*(ReT + 1)), 5), 0.4082);

			const scalar gammaL =
				CgammaI * pow025(nu*epsilon[i] / (sqr(k[i]) + small));

			tauStar[i] = CtauI * sqrt(nu / (epsilon[i] + small));

			if (gammaL >= 1)
			{
				kappa_[i] = 1;
			}
			else
			{
				kappa_[i] =
					max
					(
						min
						(
							pow(gammaL, exp1_) / (1 - pow(gammaL, exp2_)),
							1
						),
						0
					);
			}
		}
	}
	else
	{
		forAll(tauStar, i)
		{
			const scalar nu = mu[i] / (rho[i] + small);
			const scalar gammaL =
				Cgamma_ * pow025(nu*epsilon[i] / (sqr(k[i]) + small));

			tauStar[i] = Ctau_ * sqrt(nu / (epsilon[i] + small));
			if (gammaL >= 1)
			{
				kappa_[i] = 1;
			}
			else
			{
				kappa_[i] =
					max
					(
						min
						(
							pow(gammaL, exp1_) / (1 - pow(gammaL, exp2_)),
							1
						),
						0
					);
			}
		}
	}

	this->chemistryPtr_->solve(tauStar);
}


template<class ReactionThermo>
tnbLib::tmp<tnbLib::fvScalarMatrix>
tnbLib::combustionModels::EDC<ReactionThermo>::R(volScalarField& Y) const
{
	return kappa_ * laminar<ReactionThermo>::R(Y);
}


template<class ReactionThermo>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::combustionModels::EDC<ReactionThermo>::Qdot() const
{
	return volScalarField::New
	(
		this->thermo().phasePropertyName(typeName + ":Qdot"),
		kappa_*this->chemistryPtr_->Qdot()
	);
}


template<class ReactionThermo>
bool tnbLib::combustionModels::EDC<ReactionThermo>::read()
{
	if (laminar<ReactionThermo>::read())
	{
		version_ =
			(
				EDCversionNames
				[
					this->coeffs().lookupOrDefault
					(
						"version",
						word(EDCversionNames[EDCdefaultVersion])
					)
				]
		);
		C1_ = this->coeffs().lookupOrDefault("C1", 0.05774);
		C2_ = this->coeffs().lookupOrDefault("C2", 0.5);
		Cgamma_ = this->coeffs().lookupOrDefault("Cgamma", 2.1377);
		Ctau_ = this->coeffs().lookupOrDefault("Ctau", 0.4083);
		exp1_ = this->coeffs().lookupOrDefault("exp1", EDCexp1[int(version_)]);
		exp2_ = this->coeffs().lookupOrDefault("exp2", EDCexp2[int(version_)]);

		return true;
	}
	else
	{
		return false;
	}
}


// ************************************************************************* //