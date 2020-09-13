#include <KinematicParcel.hxx>

#include <forceSuSp.hxx>
#include <integrationScheme.hxx>
#include <meshTools.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

template<class ParcelType>
tnbLib::label tnbLib::KinematicParcel<ParcelType>::maxTrackAttempts = 1;


// * * * * * * * * * * *  Protected Member Functions * * * * * * * * * * * * //

template<class ParcelType>
template<class TrackCloudType>
void tnbLib::KinematicParcel<ParcelType>::setCellValues
(
	TrackCloudType& cloud,
	trackingData& td
)
{
	tetIndices tetIs = this->currentTetIndices();

	td.rhoc() = td.rhoInterp().interpolate(this->coordinates(), tetIs);

	if (td.rhoc() < cloud.constProps().rhoMin())
	{
		if (debug)
		{
			WarningInFunction
				<< "Limiting observed density in cell " << this->cell()
				<< " to " << cloud.constProps().rhoMin() << nl << endl;
		}

		td.rhoc() = cloud.constProps().rhoMin();
	}

	td.Uc() = td.UInterp().interpolate(this->coordinates(), tetIs);

	td.muc() = td.muInterp().interpolate(this->coordinates(), tetIs);
}


template<class ParcelType>
template<class TrackCloudType>
void tnbLib::KinematicParcel<ParcelType>::calcDispersion
(
	TrackCloudType& cloud,
	trackingData& td,
	const scalar dt
)
{
	td.Uc() = cloud.dispersion().update
	(
		dt,
		this->cell(),
		U_,
		td.Uc(),
		UTurb_,
		tTurb_
	);
}


template<class ParcelType>
template<class TrackCloudType>
void tnbLib::KinematicParcel<ParcelType>::cellValueSourceCorrection
(
	TrackCloudType& cloud,
	trackingData& td,
	const scalar dt
)
{
	td.Uc() += cloud.UTrans()[this->cell()] / massCell(td);
}


template<class ParcelType>
template<class TrackCloudType>
void tnbLib::KinematicParcel<ParcelType>::calc
(
	TrackCloudType& cloud,
	trackingData& td,
	const scalar dt
)
{
	// Define local properties at beginning of time step
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	const scalar np0 = nParticle_;
	const scalar mass0 = mass();

	// Reynolds number
	const scalar Re = this->Re(td);


	// Sources
	//~~~~~~~~

	// Explicit momentum source for particle
	vector Su = Zero;

	// Linearised momentum source coefficient
	scalar Spu = 0.0;

	// Momentum transfer from the particle to the carrier phase
	vector dUTrans = Zero;


	// Motion
	// ~~~~~~

	// Calculate new particle velocity
	this->U_ =
		calcVelocity(cloud, td, dt, Re, td.muc(), mass0, Su, dUTrans, Spu);


	// Accumulate carrier phase source terms
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	if (cloud.solution().coupled())
	{
		// Update momentum transfer
		cloud.UTrans()[this->cell()] += np0 * dUTrans;

		// Update momentum transfer coefficient
		cloud.UCoeff()[this->cell()] += np0 * Spu;
	}
}


template<class ParcelType>
template<class TrackCloudType>
const tnbLib::vector tnbLib::KinematicParcel<ParcelType>::calcVelocity
(
	TrackCloudType& cloud,
	trackingData& td,
	const scalar dt,
	const scalar Re,
	const scalar mu,
	const scalar mass,
	const vector& Su,
	vector& dUTrans,
	scalar& Spu
) const
{
	const typename TrackCloudType::parcelType& p =
		static_cast<const typename TrackCloudType::parcelType&>(*this);
	typename TrackCloudType::parcelType::trackingData& ttd =
		static_cast<typename TrackCloudType::parcelType::trackingData&>(td);

	const typename TrackCloudType::forceType& forces = cloud.forces();

	// Momentum source due to particle forces
	const forceSuSp Fcp = forces.calcCoupled(p, ttd, dt, mass, Re, mu);
	const forceSuSp Fncp = forces.calcNonCoupled(p, ttd, dt, mass, Re, mu);
	const scalar massEff = forces.massEff(p, ttd, mass);

	/*
	// Proper splitting ...
	// Calculate the integration coefficients
	const vector acp = (Fcp.Sp()*td.Uc() + Fcp.Su())/massEff;
	const vector ancp = (Fncp.Sp()*td.Uc() + Fncp.Su() + Su)/massEff;
	const scalar bcp = Fcp.Sp()/massEff;
	const scalar bncp = Fncp.Sp()/massEff;

	// Integrate to find the new parcel velocity
	const vector deltaUcp =
		cloud.UIntegrator().partialDelta
		(
			U_, dt, acp + ancp, bcp + bncp, acp, bcp
		);
	const vector deltaUncp =
		cloud.UIntegrator().partialDelta
		(
			U_, dt, acp + ancp, bcp + bncp, ancp, bncp
		);
	const vector deltaT = deltaUcp + deltaUncp;
	*/

	// Shortcut splitting assuming no implicit non-coupled force ...
	// Calculate the integration coefficients
	const vector acp = (Fcp.Sp()*td.Uc() + Fcp.Su()) / massEff;
	const vector ancp = (Fncp.Su() + Su) / massEff;
	const scalar bcp = Fcp.Sp() / massEff;

	// Integrate to find the new parcel velocity
	const vector deltaU = cloud.UIntegrator().delta(U_, dt, acp + ancp, bcp);
	const vector deltaUncp = ancp * dt;
	const vector deltaUcp = deltaU - deltaUncp;

	// Calculate the new velocity and the momentum transfer terms
	vector Unew = U_ + deltaU;

	dUTrans -= massEff * deltaUcp;

	Spu = dt * Fcp.Sp();

	// Apply correction to velocity and dUTrans for reduced-D cases
	const polyMesh& mesh = cloud.pMesh();
	meshTools::constrainDirection(mesh, mesh.solutionD(), Unew);
	meshTools::constrainDirection(mesh, mesh.solutionD(), dUTrans);

	return Unew;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class ParcelType>
tnbLib::KinematicParcel<ParcelType>::KinematicParcel
(
	const KinematicParcel<ParcelType>& p
)
	:
	ParcelType(p),
	active_(p.active_),
	typeId_(p.typeId_),
	nParticle_(p.nParticle_),
	d_(p.d_),
	dTarget_(p.dTarget_),
	U_(p.U_),
	rho_(p.rho_),
	age_(p.age_),
	tTurb_(p.tTurb_),
	UTurb_(p.UTurb_)
{}


template<class ParcelType>
tnbLib::KinematicParcel<ParcelType>::KinematicParcel
(
	const KinematicParcel<ParcelType>& p,
	const polyMesh& mesh
)
	:
	ParcelType(p, mesh),
	active_(p.active_),
	typeId_(p.typeId_),
	nParticle_(p.nParticle_),
	d_(p.d_),
	dTarget_(p.dTarget_),
	U_(p.U_),
	rho_(p.rho_),
	age_(p.age_),
	tTurb_(p.tTurb_),
	UTurb_(p.UTurb_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class ParcelType>
template<class TrackCloudType>
bool tnbLib::KinematicParcel<ParcelType>::move
(
	TrackCloudType& cloud,
	trackingData& td,
	const scalar trackTime
)
{
	typename TrackCloudType::parcelType& p =
		static_cast<typename TrackCloudType::parcelType&>(*this);
	typename TrackCloudType::parcelType::trackingData& ttd =
		static_cast<typename TrackCloudType::parcelType::trackingData&>(td);

	ttd.switchProcessor = false;
	ttd.keepParticle = true;

	const scalarField& cellLengthScale = cloud.cellLengthScale();
	const scalar maxCo = cloud.solution().maxCo();

	while (ttd.keepParticle && !ttd.switchProcessor && p.stepFraction() < 1)
	{
		// Cache the current position, cell and step-fraction
		const point start = p.position();
		const scalar sfrac = p.stepFraction();

		// Total displacement over the time-step
		const vector s = trackTime * U_;

		// Cell length scale
		const scalar l = cellLengthScale[p.cell()];

		// Deviation from the mesh centre for reduced-D cases
		const vector d = p.deviationFromMeshCentre();

		// Fraction of the displacement to track in this loop. This is limited
		// to ensure that the both the time and distance tracked is less than
		// maxCo times the total value.
		scalar f = 1 - p.stepFraction();
		f = min(f, maxCo);
		f = min(f, maxCo*l / max(small*l, mag(s)));
		if (p.active())
		{
			// Track to the next face
			p.trackToFace(f*s - d, f);
		}
		else
		{
			// At present the only thing that sets active_ to false is a stick
			// wall interaction. We want the position of the particle to remain
			// the same relative to the face that it is on. The local
			// coordinates therefore do not change. We still advance in time and
			// perform the relevant interactions with the fixed particle.
			p.stepFraction() += f;
		}

		const scalar dt = (p.stepFraction() - sfrac)*trackTime;

		// Avoid problems with extremely small timesteps
		if (dt > rootVSmall)
		{
			// Update cell based properties
			p.setCellValues(cloud, ttd);

			p.calcDispersion(cloud, ttd, dt);

			if (cloud.solution().cellValueSourceCorrection())
			{
				p.cellValueSourceCorrection(cloud, ttd, dt);
			}

			p.calc(cloud, ttd, dt);
		}

		p.age() += dt;

		if (p.active() && p.onFace())
		{
			cloud.functions().postFace(p, ttd.keepParticle);
		}

		cloud.functions().postMove(p, dt, start, ttd.keepParticle);

		if (p.active() && p.onFace() && ttd.keepParticle)
		{
			p.hitFace(f*s - d, f, cloud, ttd);
		}
	}

	return ttd.keepParticle;
}


template<class ParcelType>
template<class TrackCloudType>
bool tnbLib::KinematicParcel<ParcelType>::hitPatch
(
	TrackCloudType& cloud,
	trackingData& td
)
{
	typename TrackCloudType::parcelType& p =
		static_cast<typename TrackCloudType::parcelType&>(*this);

	const polyPatch& pp = p.mesh().boundaryMesh()[p.patch()];

	// Invoke post-processing model
	cloud.functions().postPatch(p, pp, td.keepParticle);

	// Invoke surface film model
	if (cloud.surfaceFilm().transferParcel(p, pp, td.keepParticle))
	{
		// All interactions done
		return true;
	}
	else if (pp.coupled())
	{
		// Don't apply the patchInteraction models to coupled boundaries
		return false;
	}
	else
	{
		// Invoke patch interaction model
		return cloud.patchInteraction().correct(p, pp, td.keepParticle);
	}
}


template<class ParcelType>
template<class TrackCloudType>
void tnbLib::KinematicParcel<ParcelType>::hitProcessorPatch
(
	TrackCloudType&,
	trackingData& td
)
{
	td.switchProcessor = true;
}


template<class ParcelType>
template<class TrackCloudType>
void tnbLib::KinematicParcel<ParcelType>::hitWallPatch
(
	TrackCloudType&,
	trackingData&
)
{
	// wall interactions are handled by the generic hitPatch method
}


template<class ParcelType>
void tnbLib::KinematicParcel<ParcelType>::transformProperties(const tensor& T)
{
	ParcelType::transformProperties(T);

	U_ = transform(T, U_);
}


template<class ParcelType>
void tnbLib::KinematicParcel<ParcelType>::transformProperties
(
	const vector& separation
)
{
	ParcelType::transformProperties(separation);
}


// * * * * * * * * * * * * * * IOStream operators  * * * * * * * * * * * * * //

#include <KinematicParcelIO.cxx>

// ************************************************************************* //