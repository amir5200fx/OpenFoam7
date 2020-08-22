#include <PatchFlowRateInjection.hxx>

#include <TimeFunction1.hxx>
#include <distributionModel.hxx>
#include <mathematicalConstants.hxx>
#include <surfaceFields.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::PatchFlowRateInjection<CloudType>::PatchFlowRateInjection
(
	const dictionary& dict,
	CloudType& owner,
	const word& modelName
)
	:
	InjectionModel<CloudType>(dict, owner, modelName, typeName),
	patchInjectionBase(owner.mesh(), this->coeffDict().lookup("patchName")),
	phiName_(this->coeffDict().template lookupOrDefault<word>("phi", "phi")),
	rhoName_(this->coeffDict().template lookupOrDefault<word>("rho", "rho")),
	duration_(readScalar(this->coeffDict().lookup("duration"))),
	concentration_
	(
		TimeFunction1<scalar>
		(
			owner.db().time(),
			"concentration",
			this->coeffDict()
			)
	),
	parcelConcentration_
	(
		readScalar(this->coeffDict().lookup("parcelConcentration"))
	),
	sizeDistribution_
	(
		distributionModel::New
		(
			this->coeffDict().subDict("sizeDistribution"),
			owner.rndGen()
		)
	)
{
	duration_ = owner.db().time().userTimeToTime(duration_);

	patchInjectionBase::updateMesh(owner.mesh());

	// Re-initialise total mass/volume to inject to zero
	// - will be reset during each injection
	this->volumeTotal_ = 0.0;
	this->massTotal_ = 0.0;
}


template<class CloudType>
tnbLib::PatchFlowRateInjection<CloudType>::PatchFlowRateInjection
(
	const PatchFlowRateInjection<CloudType>& im
)
	:
	InjectionModel<CloudType>(im),
	patchInjectionBase(im),
	phiName_(im.phiName_),
	rhoName_(im.rhoName_),
	duration_(im.duration_),
	concentration_(im.concentration_),
	parcelConcentration_(im.parcelConcentration_),
	sizeDistribution_(im.sizeDistribution_().clone().ptr())
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::PatchFlowRateInjection<CloudType>::~PatchFlowRateInjection()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
void tnbLib::PatchFlowRateInjection<CloudType>::updateMesh()
{
	patchInjectionBase::updateMesh(this->owner().mesh());
}


template<class CloudType>
tnbLib::scalar tnbLib::PatchFlowRateInjection<CloudType>::timeEnd() const
{
	return this->SOI_ + duration_;
}


template<class CloudType>
tnbLib::scalar tnbLib::PatchFlowRateInjection<CloudType>::flowRate() const
{
	const polyMesh& mesh = this->owner().mesh();

	const surfaceScalarField& phi =
		mesh.lookupObject<surfaceScalarField>(phiName_);

	const scalarField& phip = phi.boundaryField()[patchId_];

	scalar flowRateIn = 0.0;
	if (phi.dimensions() == dimVelocity * dimArea)
	{
		flowRateIn = max(0.0, -sum(phip));
	}
	else
	{
		const volScalarField& rho =
			mesh.lookupObject<volScalarField>(rhoName_);
		const scalarField& rhop = rho.boundaryField()[patchId_];

		flowRateIn = max(0.0, -sum(phip / rhop));
	}

	reduce(flowRateIn, sumOp<scalar>());

	return flowRateIn;
}


template<class CloudType>
tnbLib::label tnbLib::PatchFlowRateInjection<CloudType>::parcelsToInject
(
	const scalar time0,
	const scalar time1
)
{
	if ((time0 >= 0.0) && (time0 < duration_))
	{
		scalar dt = time1 - time0;

		scalar c = concentration_.value(0.5*(time0 + time1));

		scalar nParcels = parcelConcentration_ * c*flowRate()*dt;

		Random& rnd = this->owner().rndGen();

		label nParcelsToInject = floor(nParcels);

		// Inject an additional parcel with a probability based on the
		// remainder after the floor function
		if
			(
				nParcelsToInject > 0
				&& nParcels - scalar(nParcelsToInject) > rnd.globalScalar01()
				)
		{
			++nParcelsToInject;
		}

		return nParcelsToInject;
	}
	else
	{
		return 0;
	}
}


template<class CloudType>
tnbLib::scalar tnbLib::PatchFlowRateInjection<CloudType>::volumeToInject
(
	const scalar time0,
	const scalar time1
)
{
	scalar volume = 0.0;

	if ((time0 >= 0.0) && (time0 < duration_))
	{
		scalar c = concentration_.value(0.5*(time0 + time1));

		volume = c * (time1 - time0)*flowRate();
	}

	this->volumeTotal_ = volume;
	this->massTotal_ = volume * this->owner().constProps().rho0();

	return volume;
}


template<class CloudType>
void tnbLib::PatchFlowRateInjection<CloudType>::setPositionAndCell
(
	const label,
	const label,
	const scalar,
	vector& position,
	label& cellOwner,
	label& tetFacei,
	label& tetPti
)
{
	patchInjectionBase::setPositionAndCell
	(
		this->owner().mesh(),
		this->owner().rndGen(),
		position,
		cellOwner,
		tetFacei,
		tetPti
	);
}


template<class CloudType>
void tnbLib::PatchFlowRateInjection<CloudType>::setProperties
(
	const label,
	const label,
	const scalar,
	typename CloudType::parcelType& parcel
)
{
	// Set particle velocity to carrier velocity
	parcel.U() = this->owner().U()[parcel.cell()];

	// Set particle diameter
	parcel.d() = sizeDistribution_->sample();
}


template<class CloudType>
bool tnbLib::PatchFlowRateInjection<CloudType>::fullyDescribed() const
{
	return false;
}


template<class CloudType>
bool tnbLib::PatchFlowRateInjection<CloudType>::validInjection(const label)
{
	return true;
}


// ************************************************************************* //