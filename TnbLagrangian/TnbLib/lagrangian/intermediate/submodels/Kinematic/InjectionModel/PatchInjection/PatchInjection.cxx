#include <PatchInjection.hxx>

#include <TimeFunction1.hxx>
#include <distributionModel.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::PatchInjection<CloudType>::PatchInjection
(
	const dictionary& dict,
	CloudType& owner,
	const word& modelName
)
	:
	InjectionModel<CloudType>(dict, owner, modelName, typeName),
	patchInjectionBase(owner.mesh(), this->coeffDict().lookup("patchName")),
	duration_(readScalar(this->coeffDict().lookup("duration"))),
	parcelsPerSecond_
	(
		readScalar(this->coeffDict().lookup("parcelsPerSecond"))
	),
	U0_(this->coeffDict().lookup("U0")),
	flowRateProfile_
	(
		TimeFunction1<scalar>
		(
			owner.db().time(),
			"flowRateProfile",
			this->coeffDict()
			)
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

	// Set total volume/mass to inject
	this->volumeTotal_ = flowRateProfile_.integrate(0.0, duration_);
}


template<class CloudType>
tnbLib::PatchInjection<CloudType>::PatchInjection
(
	const PatchInjection<CloudType>& im
)
	:
	InjectionModel<CloudType>(im),
	patchInjectionBase(im),
	duration_(im.duration_),
	parcelsPerSecond_(im.parcelsPerSecond_),
	U0_(im.U0_),
	flowRateProfile_(im.flowRateProfile_),
	sizeDistribution_(im.sizeDistribution_().clone().ptr())
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::PatchInjection<CloudType>::~PatchInjection()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
void tnbLib::PatchInjection<CloudType>::updateMesh()
{
	patchInjectionBase::updateMesh(this->owner().mesh());
}


template<class CloudType>
tnbLib::scalar tnbLib::PatchInjection<CloudType>::timeEnd() const
{
	return this->SOI_ + duration_;
}


template<class CloudType>
tnbLib::label tnbLib::PatchInjection<CloudType>::parcelsToInject
(
	const scalar time0,
	const scalar time1
)
{
	if ((time0 >= 0.0) && (time0 < duration_))
	{
		scalar nParcels = (time1 - time0)*parcelsPerSecond_;

		Random& rnd = this->owner().rndGen();

		label nParcelsToInject = floor(nParcels);

		// Inject an additional parcel with a probability based on the
		// remainder after the floor function
		if
			(
				nParcelsToInject > 0
				&& (nParcels - scalar(nParcelsToInject) > rnd.globalScalar01())
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
tnbLib::scalar tnbLib::PatchInjection<CloudType>::volumeToInject
(
	const scalar time0,
	const scalar time1
)
{
	if ((time0 >= 0.0) && (time0 < duration_))
	{
		return flowRateProfile_.integrate(time0, time1);
	}
	else
	{
		return 0.0;
	}
}


template<class CloudType>
void tnbLib::PatchInjection<CloudType>::setPositionAndCell
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
void tnbLib::PatchInjection<CloudType>::setProperties
(
	const label,
	const label,
	const scalar,
	typename CloudType::parcelType& parcel
)
{
	// set particle velocity
	parcel.U() = U0_;

	// set particle diameter
	parcel.d() = sizeDistribution_->sample();
}


template<class CloudType>
bool tnbLib::PatchInjection<CloudType>::fullyDescribed() const
{
	return false;
}


template<class CloudType>
bool tnbLib::PatchInjection<CloudType>::validInjection(const label)
{
	return true;
}


// ************************************************************************* //