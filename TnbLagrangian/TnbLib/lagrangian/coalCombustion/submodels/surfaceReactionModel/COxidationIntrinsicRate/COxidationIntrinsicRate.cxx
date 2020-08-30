#include <COxidationIntrinsicRate.hxx>

#include <mathematicalConstants.hxx>

#include <SLGThermo.hxx> // added by amir

using namespace tnbLib::constant;

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::COxidationIntrinsicRate<CloudType>::COxidationIntrinsicRate
(
	const dictionary& dict,
	CloudType& owner
)
	:
	SurfaceReactionModel<CloudType>(dict, owner, typeName),
	Sb_(readScalar(this->coeffDict().lookup("Sb"))),
	C1_(readScalar(this->coeffDict().lookup("C1"))),
	rMean_(readScalar(this->coeffDict().lookup("rMean"))),
	theta_(readScalar(this->coeffDict().lookup("theta"))),
	Ai_(readScalar(this->coeffDict().lookup("Ai"))),
	Ei_(readScalar(this->coeffDict().lookup("Ei"))),
	Ag_(readScalar(this->coeffDict().lookup("Ag"))),
	tau_(this->coeffDict().lookupOrDefault("tau", sqrt(2.0))),
	CsLocalId_(-1),
	O2GlobalId_(owner.composition().carrierId("O2")),
	CO2GlobalId_(owner.composition().carrierId("CO2")),
	WC_(0.0),
	WO2_(0.0),
	HcCO2_(0.0)
{
	// Determine Cs ids
	label idSolid = owner.composition().idSolid();
	CsLocalId_ = owner.composition().localId(idSolid, "C");

	// Set local copies of thermo properties
	WO2_ = owner.thermo().carrier().Wi(O2GlobalId_);
	const scalar WCO2 = owner.thermo().carrier().Wi(CO2GlobalId_);
	WC_ = WCO2 - WO2_;

	HcCO2_ = owner.thermo().carrier().Hc(CO2GlobalId_);

	if (Sb_ < 0)
	{
		FatalErrorInFunction
			<< "Stoichiometry of reaction, Sb, must be greater than zero" << nl
			<< exit(FatalError);
	}

	const scalar YCloc = owner.composition().Y0(idSolid)[CsLocalId_];
	const scalar YSolidTot = owner.composition().YMixture0()[idSolid];
	Info << "    C(s): particle mass fraction = " << YCloc * YSolidTot << endl;
}


template<class CloudType>
tnbLib::COxidationIntrinsicRate<CloudType>::COxidationIntrinsicRate
(
	const COxidationIntrinsicRate<CloudType>& srm
)
	:
	SurfaceReactionModel<CloudType>(srm),
	Sb_(srm.Sb_),
	C1_(srm.C1_),
	rMean_(srm.rMean_),
	theta_(srm.theta_),
	Ai_(srm.Ai_),
	Ei_(srm.Ei_),
	Ag_(srm.Ag_),
	tau_(srm.tau_),
	CsLocalId_(srm.CsLocalId_),
	O2GlobalId_(srm.O2GlobalId_),
	CO2GlobalId_(srm.CO2GlobalId_),
	WC_(srm.WC_),
	WO2_(srm.WO2_),
	HcCO2_(srm.HcCO2_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::COxidationIntrinsicRate<CloudType>::
~COxidationIntrinsicRate()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::scalar tnbLib::COxidationIntrinsicRate<CloudType>::calculate
(
	const scalar dt,
	const label celli,
	const scalar d,
	const scalar T,
	const scalar Tc,
	const scalar pc,
	const scalar rhoc,
	const scalar mass,
	const scalarField& YGas,
	const scalarField& YLiquid,
	const scalarField& YSolid,
	const scalarField& YMixture,
	const scalar N,
	scalarField& dMassGas,
	scalarField& dMassLiquid,
	scalarField& dMassSolid,
	scalarField& dMassSRCarrier
) const
{
	// Fraction of remaining combustible material
	const label idSolid = CloudType::parcelType::SLD;
	const scalar Ychar = YMixture[idSolid] * YSolid[CsLocalId_];

	// Surface combustion until combustible fraction is consumed
	if (Ychar < small)
	{
		return 0.0;
	}

	const SLGThermo& thermo = this->owner().thermo();

	// Local mass fraction of O2 in the carrier phase []
	const scalar YO2 = thermo.carrier().Y(O2GlobalId_)[celli];

	// Quick exit if oxidant not present
	if (YO2 < rootVSmall)
	{
		return 0.0;
	}

	// Diffusion rate coefficient [m2/s]
	const scalar D0 = C1_ / d * pow(0.5*(T + Tc), 0.75);

	// Apparent density of pyrolysis char [kg/m^3]
	const scalar rhop = 6.0*mass / (constant::mathematical::pi*pow3(d));

	// Knusden diffusion coefficient [m2/s]
	const scalar Dkn = 97.0*rMean_*sqrt(T / WO2_);

	// Effective diffusion [m2/s]
	const scalar De = theta_ / sqr(tau_) / (1.0 / Dkn + 1 / D0);

	// Cell carrier phase O2 species density [kg/m^3]
	const scalar rhoO2 = rhoc * YO2;

	// Partial pressure O2 [Pa]
	const scalar ppO2 = rhoO2 / WO2_ * RR*Tc;

	// Intrinsic reactivity [1/s]
	const scalar ki = Ai_ * exp(-Ei_ / RR / T);

	// Thiele modulus []
	const scalar phi =
		max(0.5*d*sqrt(Sb_*rhop*Ag_*ki*ppO2 / (De*rhoO2)), rootVSmall);

	// Effectiveness factor []
	const scalar eta = max(3.0*sqr(phi)*(phi / tanh(phi) - 1.0), 0.0);

	// Chemical rate [kmol/m2/s]
	const scalar R = eta * d / 6.0*rhop*Ag_*ki;

	// Particle surface area [m^2]
	const scalar Ap = constant::mathematical::pi*sqr(d);

	// Change in C mass [kg]
	scalar dmC = Ap * rhoc*RR*Tc*YO2 / WO2_ * D0*R / (D0 + R)*dt;

	// Limit mass transfer by availability of C
	dmC = min(mass*Ychar, dmC);

	// Molar consumption [kmol]
	const scalar dOmega = dmC / WC_;

	// Change in O2 mass [kg]
	const scalar dmO2 = dOmega * Sb_*WO2_;

	// Mass of newly created CO2 [kg]
	const scalar dmCO2 = dOmega * (WC_ + Sb_ * WO2_);

	// Update local particle C mass
	dMassSolid[CsLocalId_] += dOmega * WC_;

	// Update carrier O2 and CO2 mass
	dMassSRCarrier[O2GlobalId_] -= dmO2;
	dMassSRCarrier[CO2GlobalId_] += dmCO2;

	const scalar HsC = thermo.solids().properties()[CsLocalId_].Hs(T);

	// carrier sensible enthalpy exchange handled via change in mass

	// Heat of reaction [J]
	return dmC * HsC - dmCO2 * HcCO2_;
}


// ************************************************************************* //