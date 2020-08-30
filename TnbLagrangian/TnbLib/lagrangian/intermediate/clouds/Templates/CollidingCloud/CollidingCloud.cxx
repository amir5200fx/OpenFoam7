#include <CollidingCloud.hxx>

#include <CollisionModel.hxx>
#include <NoCollision.hxx>

#include <subCycleTime.hxx>  // added by amir

// * * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * //

template<class CloudType>
void tnbLib::CollidingCloud<CloudType>::setModels()
{
	collisionModel_.reset
	(
		CollisionModel<CollidingCloud<CloudType>>::New
		(
			this->subModelProperties(),
			*this
		).ptr()
	);
}


template<class CloudType>
template<class TrackCloudType>
void tnbLib::CollidingCloud<CloudType>::moveCollide
(
	TrackCloudType& cloud,
	typename parcelType::trackingData& td,
	const scalar deltaT
)
{
	td.part() = parcelType::trackingData::tpVelocityHalfStep;
	CloudType::move(cloud, td, deltaT);

	td.part() = parcelType::trackingData::tpLinearTrack;
	CloudType::move(cloud, td, deltaT);

	// td.part() = parcelType::trackingData::tpRotationalTrack;
	// CloudType::move(cloud, td, deltaT);

	this->updateCellOccupancy();

	this->collision().collide();

	td.part() = parcelType::trackingData::tpVelocityHalfStep;
	CloudType::move(cloud, td, deltaT);
}



template<class CloudType>
void tnbLib::CollidingCloud<CloudType>::cloudReset(CollidingCloud<CloudType>& c)
{
	CloudType::cloudReset(c);

	collisionModel_.reset(c.collisionModel_.ptr());
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::CollidingCloud<CloudType>::CollidingCloud
(
	const word& cloudName,
	const volScalarField& rho,
	const volVectorField& U,
	const volScalarField& mu,
	const dimensionedVector& g,
	bool readFields
)
	:
	CloudType(cloudName, rho, U, mu, g, false),
	constProps_(this->particleProperties()),
	collisionModel_(nullptr)
{
	if (this->solution().active())
	{
		setModels();

		if (readFields)
		{
			parcelType::readFields(*this);
			this->deleteLostParticles();
		}

		if
			(
				this->solution().steadyState()
				&& !isType<NoCollision<CollidingCloud<CloudType>>>(collisionModel_())
				)
		{
			FatalErrorInFunction
				<< "Collision modelling not currently available "
				<< "for steady state calculations" << exit(FatalError);
		}
	}
}


template<class CloudType>
tnbLib::CollidingCloud<CloudType>::CollidingCloud
(
	CollidingCloud<CloudType>& c,
	const word& name
)
	:
	CloudType(c, name),
	collisionModel_(c.collisionModel_->clone())
{}


template<class CloudType>
tnbLib::CollidingCloud<CloudType>::CollidingCloud
(
	const fvMesh& mesh,
	const word& name,
	const CollidingCloud<CloudType>& c
)
	:
	CloudType(mesh, name, c),
	collisionModel_(nullptr)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::CollidingCloud<CloudType>::~CollidingCloud()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
void tnbLib::CollidingCloud<CloudType>::storeState()
{
	cloudCopyPtr_.reset
	(
		static_cast<CollidingCloud<CloudType>*>
		(
			clone(this->name() + "Copy").ptr()
			)
	);
}


template<class CloudType>
void tnbLib::CollidingCloud<CloudType>::restoreState()
{
	cloudReset(cloudCopyPtr_());
	cloudCopyPtr_.clear();
}


template<class CloudType>
void tnbLib::CollidingCloud<CloudType>::evolve()
{
	if (this->solution().canEvolve())
	{
		typename parcelType::trackingData td(*this);

		this->solve(*this, td);
	}
}


template<class CloudType>
template<class TrackCloudType>
void  tnbLib::CollidingCloud<CloudType>::motion
(
	TrackCloudType& cloud,
	typename parcelType::trackingData& td
)
{
	// Sympletic leapfrog integration of particle forces:
	// + apply half deltaV with stored force
	// + move positions with new velocity
	// + calculate forces in new position
	// + apply half deltaV with new force

	label nSubCycles = collision().nSubCycles();

	if (nSubCycles > 1)
	{
		Info << "    " << nSubCycles << " move-collide subCycles" << endl;

		subCycleTime moveCollideSubCycle
		(
			const_cast<Time&>(this->db().time()),
			nSubCycles
		);

		while (!(++moveCollideSubCycle).end())
		{
			moveCollide(cloud, td, this->db().time().deltaTValue());
		}

		moveCollideSubCycle.endSubCycle();
	}
	else
	{
		moveCollide(cloud, td, this->db().time().deltaTValue());
	}
}


template<class CloudType>
void tnbLib::CollidingCloud<CloudType>::info()
{
	CloudType::info();

	scalar rotationalKineticEnergy = rotationalKineticEnergyOfSystem();
	reduce(rotationalKineticEnergy, sumOp<scalar>());

	Info << "    Rotational kinetic energy       = "
		<< rotationalKineticEnergy << nl;
}


// ************************************************************************* //