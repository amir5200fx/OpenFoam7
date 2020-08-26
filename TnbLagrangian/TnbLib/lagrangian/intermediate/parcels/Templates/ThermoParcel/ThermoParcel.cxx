#include <ThermoParcel.hxx>

#include <physicoChemicalConstants.hxx>

using namespace tnbLib::constant;

// * * * * * * * * * * *  Protected Member Functions * * * * * * * * * * * * //

template<class ParcelType>
template<class TrackCloudType>
void tnbLib::ThermoParcel<ParcelType>::setCellValues
(
	TrackCloudType& cloud,
	trackingData& td
)
{
	ParcelType::setCellValues(cloud, td);

	tetIndices tetIs = this->currentTetIndices();

	td.Cpc() = td.CpInterp().interpolate(this->coordinates(), tetIs);

	td.Tc() = td.TInterp().interpolate(this->coordinates(), tetIs);

	if (td.Tc() < cloud.constProps().TMin())
	{
		if (debug)
		{
			WarningInFunction
				<< "Limiting observed temperature in cell " << this->cell()
				<< " to " << cloud.constProps().TMin() << nl << endl;
		}

		td.Tc() = cloud.constProps().TMin();
	}
}


template<class ParcelType>
template<class TrackCloudType>
void tnbLib::ThermoParcel<ParcelType>::cellValueSourceCorrection
(
	TrackCloudType& cloud,
	trackingData& td,
	const scalar dt
)
{
	td.Uc() += cloud.UTrans()[this->cell()] / this->massCell(td);

	const scalar CpMean = td.CpInterp().psi()[this->cell()];
	td.Tc() += cloud.hsTrans()[this->cell()] / (CpMean*this->massCell(td));

	if (td.Tc() < cloud.constProps().TMin())
	{
		if (debug)
		{
			WarningInFunction
				<< "Limiting observed temperature in cell " << this->cell()
				<< " to " << cloud.constProps().TMin() << nl << endl;
		}

		td.Tc() = cloud.constProps().TMin();
	}
}


template<class ParcelType>
template<class TrackCloudType>
void tnbLib::ThermoParcel<ParcelType>::calcSurfaceValues
(
	TrackCloudType& cloud,
	trackingData& td,
	const scalar T,
	scalar& Ts,
	scalar& rhos,
	scalar& mus,
	scalar& Pr,
	scalar& kappas
) const
{
	// Surface temperature using two thirds rule
	Ts = (2.0*T + td.Tc()) / 3.0;

	if (Ts < cloud.constProps().TMin())
	{
		if (debug)
		{
			WarningInFunction
				<< "Limiting parcel surface temperature to "
				<< cloud.constProps().TMin() << nl << endl;
		}

		Ts = cloud.constProps().TMin();
	}

	// Assuming thermo props vary linearly with T for small d(T)
	const scalar TRatio = td.Tc() / Ts;

	rhos = td.rhoc()*TRatio;

	tetIndices tetIs = this->currentTetIndices();
	mus = td.muInterp().interpolate(this->coordinates(), tetIs) / TRatio;
	kappas = td.kappaInterp().interpolate(this->coordinates(), tetIs) / TRatio;

	Pr = td.Cpc()*mus / kappas;
	Pr = max(rootVSmall, Pr);
}


template<class ParcelType>
template<class TrackCloudType>
void tnbLib::ThermoParcel<ParcelType>::calc
(
	TrackCloudType& cloud,
	trackingData& td,
	const scalar dt
)
{
	// Define local properties at beginning of time step
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	const scalar np0 = this->nParticle_;
	const scalar mass0 = this->mass();

	// Store T for consistent radiation source
	const scalar T0 = this->T_;


	// Calc surface values
	// ~~~~~~~~~~~~~~~~~~~
	scalar Ts, rhos, mus, Pr, kappas;
	calcSurfaceValues(cloud, td, this->T_, Ts, rhos, mus, Pr, kappas);

	// Reynolds number
	scalar Re = this->Re(rhos, this->U_, td.Uc(), this->d_, mus);


	// Sources
	// ~~~~~~~

	// Explicit momentum source for particle
	vector Su = Zero;

	// Linearised momentum source coefficient
	scalar Spu = 0.0;

	// Momentum transfer from the particle to the carrier phase
	vector dUTrans = Zero;

	// Explicit enthalpy source for particle
	scalar Sh = 0.0;

	// Linearised enthalpy source coefficient
	scalar Sph = 0.0;

	// Sensible enthalpy transfer from the particle to the carrier phase
	scalar dhsTrans = 0.0;


	// Heat transfer
	// ~~~~~~~~~~~~~

	// Sum Ni*Cpi*Wi of emission species
	scalar NCpW = 0.0;

	// Calculate new particle temperature
	this->T_ =
		this->calcHeatTransfer
		(
			cloud,
			td,
			dt,
			Re,
			Pr,
			kappas,
			NCpW,
			Sh,
			dhsTrans,
			Sph
		);


	// Motion
	// ~~~~~~

	// Calculate new particle velocity
	this->U_ =
		this->calcVelocity(cloud, td, dt, Re, mus, mass0, Su, dUTrans, Spu);


	//  Accumulate carrier phase source terms
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	if (cloud.solution().coupled())
	{
		// Update momentum transfer
		cloud.UTrans()[this->cell()] += np0 * dUTrans;

		// Update momentum transfer coefficient
		cloud.UCoeff()[this->cell()] += np0 * Spu;

		// Update sensible enthalpy transfer
		cloud.hsTrans()[this->cell()] += np0 * dhsTrans;

		// Update sensible enthalpy coefficient
		cloud.hsCoeff()[this->cell()] += np0 * Sph;

		// Update radiation fields
		if (cloud.radiation())
		{
			const scalar ap = this->areaP();
			const scalar T4 = pow4(T0);
			cloud.radAreaP()[this->cell()] += dt * np0*ap;
			cloud.radT4()[this->cell()] += dt * np0*T4;
			cloud.radAreaPT4()[this->cell()] += dt * np0*ap*T4;
		}
	}
}


template<class ParcelType>
template<class TrackCloudType>
tnbLib::scalar tnbLib::ThermoParcel<ParcelType>::calcHeatTransfer
(
	TrackCloudType& cloud,
	trackingData& td,
	const scalar dt,
	const scalar Re,
	const scalar Pr,
	const scalar kappa,
	const scalar NCpW,
	const scalar Sh,
	scalar& dhsTrans,
	scalar& Sph
)
{
	if (!cloud.heatTransfer().active())
	{
		return T_;
	}

	const scalar d = this->d();
	const scalar rho = this->rho();
	const scalar As = this->areaS(d);
	const scalar V = this->volume(d);
	const scalar m = rho * V;

	// Calc heat transfer coefficient
	scalar htc = cloud.heatTransfer().htc(d, Re, Pr, kappa, NCpW);

	// Calculate the integration coefficients
	const scalar bcp = htc * As / (m*Cp_);
	const scalar acp = bcp * td.Tc();
	scalar ancp = Sh;
	if (cloud.radiation())
	{
		const tetIndices tetIs = this->currentTetIndices();
		const scalar Gc = td.GInterp().interpolate(this->coordinates(), tetIs);
		const scalar sigma = physicoChemical::sigma.value();
		const scalar epsilon = cloud.constProps().epsilon0();

		ancp += As * epsilon*(Gc / 4.0 - sigma * pow4(T_));
	}
	ancp /= m * Cp_;

	// Integrate to find the new parcel temperature
	const scalar deltaT = cloud.TIntegrator().delta(T_, dt, acp + ancp, bcp);
	const scalar deltaTncp = ancp * dt;
	const scalar deltaTcp = deltaT - deltaTncp;

	// Calculate the new temperature and the enthalpy transfer terms
	scalar Tnew = T_ + deltaT;
	Tnew = min(max(Tnew, cloud.constProps().TMin()), cloud.constProps().TMax());

	dhsTrans -= m * Cp_*deltaTcp;

	Sph = dt * m*Cp_*bcp;

	return Tnew;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class ParcelType>
tnbLib::ThermoParcel<ParcelType>::ThermoParcel
(
	const ThermoParcel<ParcelType>& p
)
	:
	ParcelType(p),
	T_(p.T_),
	Cp_(p.Cp_)
{}


template<class ParcelType>
tnbLib::ThermoParcel<ParcelType>::ThermoParcel
(
	const ThermoParcel<ParcelType>& p,
	const polyMesh& mesh
)
	:
	ParcelType(p, mesh),
	T_(p.T_),
	Cp_(p.Cp_)
{}


// * * * * * * * * * * * * * * IOStream operators  * * * * * * * * * * * * * //

#include <ThermoParcelIO.cxx>

// ************************************************************************* //