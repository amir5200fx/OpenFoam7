#include <PairSpringSliderDashpot.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class CloudType>
void tnbLib::PairSpringSliderDashpot<CloudType>::findMinMaxProperties
(
	scalar& RMin,
	scalar& rhoMax,
	scalar& UMagMax
) const
{
	RMin = vGreat;
	rhoMax = -vGreat;
	UMagMax = -vGreat;

	forAllConstIter(typename CloudType, this->owner(), iter)
	{
		const typename CloudType::parcelType& p = iter();

		// Finding minimum diameter to avoid excessive arithmetic

		scalar dEff = p.d();

		if (useEquivalentSize_)
		{
			dEff *= cbrt(p.nParticle()*volumeFactor_);
		}

		RMin = min(dEff, RMin);

		rhoMax = max(p.rho(), rhoMax);

		UMagMax = max
		(
			mag(p.U()) + mag(p.omega())*dEff / 2,
			UMagMax
		);
	}

	// Transform the minimum diameter into minimum radius
	//     rMin = dMin/2
	// then rMin into minimum R,
	//     1/RMin = 1/rMin + 1/rMin,
	//     RMin = rMin/2 = dMin/4

	RMin /= 4.0;

	// Multiply by two to create the worst-case relative velocity

	UMagMax = 2 * UMagMax;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::PairSpringSliderDashpot<CloudType>::PairSpringSliderDashpot
(
	const dictionary& dict,
	CloudType& cloud
)
	:
	PairModel<CloudType>(dict, cloud, typeName),
	Estar_(),
	Gstar_(),
	alpha_(readScalar(this->coeffDict().lookup("alpha"))),
	b_(readScalar(this->coeffDict().lookup("b"))),
	mu_(readScalar(this->coeffDict().lookup("mu"))),
	cohesionEnergyDensity_
	(
		readScalar(this->coeffDict().lookup("cohesionEnergyDensity"))
	),
	cohesion_(false),
	collisionResolutionSteps_
	(
		readScalar(this->coeffDict().lookup("collisionResolutionSteps"))
	),
	volumeFactor_(1.0),
	useEquivalentSize_(Switch(this->coeffDict().lookup("useEquivalentSize")))
{
	if (useEquivalentSize_)
	{
		volumeFactor_ = readScalar(this->coeffDict().lookup("volumeFactor"));
	}

	scalar nu = this->owner().constProps().poissonsRatio();

	scalar E = this->owner().constProps().youngsModulus();

	Estar_ = E / (2.0*(1.0 - sqr(nu)));

	scalar G = E / (2.0*(1.0 + nu));

	Gstar_ = G / (2.0*(2.0 - nu));

	cohesion_ = (mag(cohesionEnergyDensity_) > vSmall);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::PairSpringSliderDashpot<CloudType>::~PairSpringSliderDashpot()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
bool tnbLib::PairSpringSliderDashpot<CloudType>::controlsTimestep() const
{
	return true;
}


template<class CloudType>
tnbLib::label tnbLib::PairSpringSliderDashpot<CloudType>::nSubCycles() const
{
	if (!(this->owner().size()))
	{
		return 1;
	}

	scalar RMin;
	scalar rhoMax;
	scalar UMagMax;

	findMinMaxProperties(RMin, rhoMax, UMagMax);

	// Note:  pi^(7/5)*(5/4)^(2/5) = 5.429675
	scalar minCollisionDeltaT =
		5.429675
		*RMin
		*pow(rhoMax / (Estar_*sqrt(UMagMax) + vSmall), 0.4)
		/ collisionResolutionSteps_;

	return ceil(this->owner().time().deltaTValue() / minCollisionDeltaT);
}


template<class CloudType>
void tnbLib::PairSpringSliderDashpot<CloudType>::evaluatePair
(
	typename CloudType::parcelType& pA,
	typename CloudType::parcelType& pB
) const
{
	vector r_AB = (pA.position() - pB.position());

	scalar dAEff = pA.d();

	if (useEquivalentSize_)
	{
		dAEff *= cbrt(pA.nParticle()*volumeFactor_);
	}

	scalar dBEff = pB.d();

	if (useEquivalentSize_)
	{
		dBEff *= cbrt(pB.nParticle()*volumeFactor_);
	}

	scalar r_AB_mag = mag(r_AB);

	scalar normalOverlapMag = 0.5*(dAEff + dBEff) - r_AB_mag;

	if (normalOverlapMag > 0)
	{
		// Particles in collision

		vector rHat_AB = r_AB / (r_AB_mag + vSmall);

		vector U_AB = pA.U() - pB.U();

		// Effective radius
		scalar R = 0.5*dAEff*dBEff / (dAEff + dBEff);

		// Effective mass
		scalar M = pA.mass()*pB.mass() / (pA.mass() + pB.mass());

		scalar kN = (4.0 / 3.0)*sqrt(R)*Estar_;

		scalar etaN = alpha_ * sqrt(M*kN)*pow025(normalOverlapMag);

		// Normal force
		vector fN_AB =
			rHat_AB
			* (kN*pow(normalOverlapMag, b_) - etaN * (U_AB & rHat_AB));

		// Cohesion force, energy density multiplied by the area of
		// particle-particle overlap
		if (cohesion_)
		{
			fN_AB +=
				-cohesionEnergyDensity_
				* overlapArea(dAEff / 2.0, dBEff / 2.0, r_AB_mag)
				*rHat_AB;
		}

		pA.f() += fN_AB;
		pB.f() += -fN_AB;

		vector USlip_AB =
			U_AB - (U_AB & rHat_AB)*rHat_AB
			- ((dAEff / 2 * pA.omega() + dBEff / 2 * pB.omega()) ^ rHat_AB);

		scalar deltaT = this->owner().mesh().time().deltaTValue();

		vector& tangentialOverlap_AB =
			pA.collisionRecords().matchPairRecord
			(
				pB.origProc(),
				pB.origId()
			).collisionData();

		vector& tangentialOverlap_BA =
			pB.collisionRecords().matchPairRecord
			(
				pA.origProc(),
				pA.origId()
			).collisionData();

		vector deltaTangentialOverlap_AB = USlip_AB * deltaT;

		tangentialOverlap_AB += deltaTangentialOverlap_AB;
		tangentialOverlap_BA += -deltaTangentialOverlap_AB;

		scalar tangentialOverlapMag = mag(tangentialOverlap_AB);

		if (tangentialOverlapMag > vSmall)
		{
			scalar kT = 8.0*sqrt(R*normalOverlapMag)*Gstar_;

			scalar etaT = etaN;

			// Tangential force
			vector fT_AB;

			if (kT*tangentialOverlapMag > mu_*mag(fN_AB))
			{
				// Tangential force greater than sliding friction,
				// particle slips

				fT_AB = -mu_ * mag(fN_AB)*USlip_AB / mag(USlip_AB);

				tangentialOverlap_AB = Zero;
				tangentialOverlap_BA = Zero;
			}
			else
			{
				fT_AB = -kT * tangentialOverlap_AB - etaT * USlip_AB;
			}

			pA.f() += fT_AB;
			pB.f() += -fT_AB;

			pA.torque() += (dAEff / 2 * -rHat_AB) ^ fT_AB;
			pB.torque() += (dBEff / 2 * rHat_AB) ^ -fT_AB;
		}
	}
}


// ************************************************************************* //