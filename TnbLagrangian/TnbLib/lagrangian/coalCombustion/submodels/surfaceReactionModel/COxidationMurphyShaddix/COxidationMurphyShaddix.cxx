#include <COxidationMurphyShaddix.hxx>

#include <mathematicalConstants.hxx>

#include <SLGThermo.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::label tnbLib::COxidationMurphyShaddix<CloudType>::maxIters_ = 1000;

template<class CloudType>
tnbLib::scalar tnbLib::COxidationMurphyShaddix<CloudType>::tolerance_ = 1e-06;


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::COxidationMurphyShaddix<CloudType>::COxidationMurphyShaddix
(
	const dictionary& dict,
	CloudType& owner
)
	:
	SurfaceReactionModel<CloudType>(dict, owner, typeName),
	D0_(readScalar(this->coeffDict().lookup("D0"))),
	rho0_(readScalar(this->coeffDict().lookup("rho0"))),
	T0_(readScalar(this->coeffDict().lookup("T0"))),
	Dn_(readScalar(this->coeffDict().lookup("Dn"))),
	A_(readScalar(this->coeffDict().lookup("A"))),
	E_(readScalar(this->coeffDict().lookup("E"))),
	n_(readScalar(this->coeffDict().lookup("n"))),
	WVol_(readScalar(this->coeffDict().lookup("WVol"))),
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

	const scalar YCloc = owner.composition().Y0(idSolid)[CsLocalId_];
	const scalar YSolidTot = owner.composition().YMixture0()[idSolid];
	Info << "    C(s): particle mass fraction = " << YCloc * YSolidTot << endl;
}


template<class CloudType>
tnbLib::COxidationMurphyShaddix<CloudType>::COxidationMurphyShaddix
(
	const COxidationMurphyShaddix<CloudType>& srm
)
	:
	SurfaceReactionModel<CloudType>(srm),
	D0_(srm.D0_),
	rho0_(srm.rho0_),
	T0_(srm.T0_),
	Dn_(srm.Dn_),
	A_(srm.A_),
	E_(srm.E_),
	n_(srm.n_),
	WVol_(srm.WVol_),
	CsLocalId_(srm.CsLocalId_),
	O2GlobalId_(srm.O2GlobalId_),
	CO2GlobalId_(srm.CO2GlobalId_),
	WC_(srm.WC_),
	WO2_(srm.WO2_),
	HcCO2_(srm.HcCO2_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::COxidationMurphyShaddix<CloudType>::~COxidationMurphyShaddix()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::scalar tnbLib::COxidationMurphyShaddix<CloudType>::calculate
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
	const scalar fComb = YMixture[idSolid] * YSolid[CsLocalId_];

	// Surface combustion until combustible fraction is consumed
	if (fComb < small)
	{
		return 0.0;
	}

	const SLGThermo& thermo = this->owner().thermo();

	// Cell carrier phase O2 species density [kg/m^3]
	const scalar rhoO2 = rhoc * thermo.carrier().Y(O2GlobalId_)[celli];

	if (rhoO2 < small)
	{
		return 0.0;
	}

	// Particle surface area [m^2]
	const scalar Ap = constant::mathematical::pi*sqr(d);

	// Calculate diffision constant at continuous phase temperature
	// and density [m^2/s]
	const scalar D = D0_ * (rho0_ / rhoc)*pow(Tc / T0_, Dn_);

	// Far field partial pressure O2 [Pa]
	const scalar ppO2 = rhoO2 / WO2_ * RR*Tc;

	// Total molar concentration of the carrier phase [kmol/m^3]
	const scalar C = pc / (RR*Tc);

	if (debug)
	{
		Pout << "mass  = " << mass << nl
			<< "fComb = " << fComb << nl
			<< "Ap    = " << Ap << nl
			<< "dt    = " << dt << nl
			<< "C     = " << C << nl
			<< endl;
	}

	// Molar reaction rate per unit surface area [kmol/m^2/s]
	scalar qCsOld = 0;
	scalar qCs = 1;

	const scalar qCsLim = mass * fComb / (WC_*Ap*dt);

	if (debug)
	{
		Pout << "qCsLim = " << qCsLim << endl;
	}

	label iter = 0;
	while ((mag(qCs - qCsOld) / qCs > tolerance_) && (iter <= maxIters_))
	{
		qCsOld = qCs;
		const scalar PO2Surface = ppO2 * exp(-(qCs + N)*d / (2 * C*D));
		qCs = A_ * exp(-E_ / (RR*T))*pow(PO2Surface, n_);
		qCs = (100.0*qCs + iter * qCsOld) / (100.0 + iter);
		qCs = min(qCs, qCsLim);

		if (debug)
		{
			Pout << "iter = " << iter
				<< ", qCsOld = " << qCsOld
				<< ", qCs = " << qCs
				<< nl << endl;
		}

		iter++;
	}

	if (iter > maxIters_)
	{
		WarningInFunction
			<< "iter limit reached (" << maxIters_ << ")" << nl << endl;
	}

	// Calculate the number of molar units reacted
	scalar dOmega = qCs * Ap*dt;

	// Add to carrier phase mass transfer
	dMassSRCarrier[O2GlobalId_] += -dOmega * WO2_;
	dMassSRCarrier[CO2GlobalId_] += dOmega * (WC_ + WO2_);

	// Add to particle mass transfer
	dMassSolid[CsLocalId_] += dOmega * WC_;

	const scalar HsC = thermo.solids().properties()[CsLocalId_].Hs(T);

	// carrier sensible enthalpy exchange handled via change in mass

	// Heat of reaction [J]
	return dOmega * (WC_*HsC - (WC_ + WO2_)*HcCO2_);
}


// ************************************************************************* //