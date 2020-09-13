#pragma once
#include <PackingModel.hxx>
#include <ParticleStressModel.hxx>
#include <DampingModel.hxx>
#include <IsotropyModel.hxx>
#include <TimeScaleModel.hxx>

// * * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * //

template<class CloudType>
void tnbLib::MPPICCloud<CloudType>::setModels()
{
	packingModel_.reset
	(
		PackingModel<MPPICCloud<CloudType>>::New
		(
			this->subModelProperties(),
			*this
		).ptr()
	);
	dampingModel_.reset
	(
		DampingModel<MPPICCloud<CloudType>>::New
		(
			this->subModelProperties(),
			*this
		).ptr()
	);
	isotropyModel_.reset
	(
		IsotropyModel<MPPICCloud<CloudType>>::New
		(
			this->subModelProperties(),
			*this
		).ptr()
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::MPPICCloud<CloudType>::MPPICCloud
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
	packingModel_(nullptr),
	dampingModel_(nullptr),
	isotropyModel_(nullptr)
{
	if (this->solution().steadyState())
	{
		FatalErrorInFunction
			<< "MPPIC modelling not available for steady state calculations"
			<< exit(FatalError);
	}

	if (this->solution().active())
	{
		setModels();

		if (readFields)
		{
			parcelType::readFields(*this);
			this->deleteLostParticles();
		}
	}
}


template<class CloudType>
tnbLib::MPPICCloud<CloudType>::MPPICCloud
(
	MPPICCloud<CloudType>& c,
	const word& name
)
	:
	CloudType(c, name),
	packingModel_(c.packingModel_->clone()),
	dampingModel_(c.dampingModel_->clone()),
	isotropyModel_(c.isotropyModel_->clone())
{}


template<class CloudType>
tnbLib::MPPICCloud<CloudType>::MPPICCloud
(
	const fvMesh& mesh,
	const word& name,
	const MPPICCloud<CloudType>& c
)
	:
	CloudType(mesh, name, c),
	packingModel_(nullptr),
	dampingModel_(nullptr),
	isotropyModel_(nullptr)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::MPPICCloud<CloudType>::~MPPICCloud()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
void tnbLib::MPPICCloud<CloudType>::storeState()
{
	cloudCopyPtr_.reset
	(
		static_cast<MPPICCloud<CloudType>*>
		(
			clone(this->name() + "Copy").ptr()
			)
	);
}


template<class CloudType>
void tnbLib::MPPICCloud<CloudType>::restoreState()
{
	this->cloudReset(cloudCopyPtr_());
	cloudCopyPtr_.clear();
}


template<class CloudType>
void tnbLib::MPPICCloud<CloudType>::evolve()
{
	if (this->solution().canEvolve())
	{
		typename parcelType::trackingData td(*this);

		this->solve(*this, td);
	}
}


template<class CloudType>
template<class TrackCloudType>
void tnbLib::MPPICCloud<CloudType>::motion
(
	TrackCloudType& cloud,
	typename parcelType::trackingData& td
)
{
	// Kinematic
	// ~~~~~~~~~

	// force calculation and tracking
	td.part() = parcelType::trackingData::tpLinearTrack;
	CloudType::move(cloud, td, this->db().time().deltaTValue());


	// Preliminary
	// ~~~~~~~~~~~

	// switch forces off so they are not applied in corrector steps
	this->forces().setCalcNonCoupled(false);
	this->forces().setCalcCoupled(false);


	// Damping
	// ~~~~~~~

	if (dampingModel_->active())
	{
		if (this->mesh().moving())
		{
			FatalErrorInFunction
				<< "MPPIC damping modelling does not support moving meshes."
				<< exit(FatalError);
		}

		// update averages
		td.updateAverages(cloud);

		// memory allocation and eulerian calculations
		dampingModel_->cacheFields(true);

		// calculate the damping velocity corrections without moving the parcels
		td.part() = parcelType::trackingData::tpDampingNoTrack;
		CloudType::move(cloud, td, this->db().time().deltaTValue());

		// correct the parcel positions and velocities
		td.part() = parcelType::trackingData::tpCorrectTrack;
		CloudType::move(cloud, td, this->db().time().deltaTValue());

		// finalise and free memory
		dampingModel_->cacheFields(false);
	}


	// Packing
	// ~~~~~~~

	if (packingModel_->active())
	{
		if (this->mesh().moving())
		{
			FatalErrorInFunction
				<< "MPPIC packing modelling does not support moving meshes."
				<< exit(FatalError);
		}

		// same procedure as for damping
		td.updateAverages(cloud);
		packingModel_->cacheFields(true);
		td.part() = parcelType::trackingData::tpPackingNoTrack;
		CloudType::move(cloud, td, this->db().time().deltaTValue());
		td.part() = parcelType::trackingData::tpCorrectTrack;
		CloudType::move(cloud, td, this->db().time().deltaTValue());
		packingModel_->cacheFields(false);
	}


	// Isotropy
	// ~~~~~~~~

	if (isotropyModel_->active())
	{
		// update averages
		td.updateAverages(cloud);

		// apply isotropy model
		isotropyModel_->calculate();
	}


	// Final
	// ~~~~~

	// update cell occupancy
	this->updateCellOccupancy();

	// switch forces back on
	this->forces().setCalcNonCoupled(true);
	this->forces().setCalcCoupled(this->solution().coupled());
}


template<class CloudType>
void tnbLib::MPPICCloud<CloudType>::info()
{
	CloudType::info();

	tmp<volScalarField> alpha = this->theta();

	const scalar alphaMin = gMin(alpha().primitiveField());
	const scalar alphaMax = gMax(alpha().primitiveField());

	Info << "    Min cell volume fraction        = " << alphaMin << endl;
	Info << "    Max cell volume fraction        = " << alphaMax << endl;

	if (alphaMax < small)
	{
		return;
	}

	scalar nMin = great;

	forAll(this->mesh().cells(), celli)
	{
		const label n = this->cellOccupancy()[celli].size();

		if (n > 0)
		{
			const scalar nPack = n * alphaMax / alpha()[celli];

			if (nPack < nMin)
			{
				nMin = nPack;
			}
		}
	}

	reduce(nMin, minOp<scalar>());

	Info << "    Min dense number of parcels     = " << nMin << endl;
}


// ************************************************************************* //