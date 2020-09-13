#pragma once
#include <volFields.hxx>
#include <mathematicalConstants.hxx>

using namespace tnbLib::constant::mathematical;

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::FieldActivatedInjection<CloudType>::FieldActivatedInjection
(
	const dictionary& dict,
	CloudType& owner,
	const word& modelName
)
	:
	InjectionModel<CloudType>(dict, owner, modelName, typeName),
	factor_(readScalar(this->coeffDict().lookup("factor"))),
	referenceField_
	(
		owner.db().objectRegistry::template lookupObject<volScalarField>
		(
			this->coeffDict().lookup("referenceField")
			)
	),
	thresholdField_
	(
		owner.db().objectRegistry::template lookupObject<volScalarField>
		(
			this->coeffDict().lookup("thresholdField")
			)
	),
	positionsFile_(this->coeffDict().lookup("positionsFile")),
	positions_
	(
		IOobject
		(
			positionsFile_,
			owner.db().time().constant(),
			owner.mesh(),
			IOobject::MUST_READ,
			IOobject::NO_WRITE
		)
	),
	injectorCells_(positions_.size()),
	injectorTetFaces_(positions_.size()),
	injectorTetPts_(positions_.size()),
	nParcelsPerInjector_
	(
		readLabel(this->coeffDict().lookup("parcelsPerInjector"))
	),
	nParcelsInjected_(positions_.size(), 0),
	U0_(this->coeffDict().lookup("U0")),
	diameters_(positions_.size()),
	sizeDistribution_
	(
		distributionModel::New
		(
			this->coeffDict().subDict("sizeDistribution"),
			owner.rndGen()
		)
	)
{
	// Construct parcel diameters - one per injector cell
	forAll(diameters_, i)
	{
		diameters_[i] = sizeDistribution_->sample();
	}

	// Determine total volume of particles to inject
	this->volumeTotal_ =
		nParcelsPerInjector_ * sum(pow3(diameters_))*pi / 6.0;

	updateMesh();
}


template<class CloudType>
tnbLib::FieldActivatedInjection<CloudType>::FieldActivatedInjection
(
	const FieldActivatedInjection<CloudType>& im
)
	:
	InjectionModel<CloudType>(im),
	factor_(im.factor_),
	referenceField_(im.referenceField_),
	thresholdField_(im.thresholdField_),
	positionsFile_(im.positionsFile_),
	positions_(im.positions_),
	injectorCells_(im.injectorCells_),
	injectorTetFaces_(im.injectorTetFaces_),
	injectorTetPts_(im.injectorTetPts_),
	nParcelsPerInjector_(im.nParcelsPerInjector_),
	nParcelsInjected_(im.nParcelsInjected_),
	U0_(im.U0_),
	diameters_(im.diameters_),
	sizeDistribution_(im.sizeDistribution_().clone().ptr())
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::FieldActivatedInjection<CloudType>::~FieldActivatedInjection()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
void tnbLib::FieldActivatedInjection<CloudType>::updateMesh()
{
	// Set/cache the injector cells
	forAll(positions_, i)
	{
		this->findCellAtPosition
		(
			injectorCells_[i],
			injectorTetFaces_[i],
			injectorTetPts_[i],
			positions_[i]
		);
	}
}


template<class CloudType>
tnbLib::scalar tnbLib::FieldActivatedInjection<CloudType>::timeEnd() const
{
	return great;
}


template<class CloudType>
tnbLib::label tnbLib::FieldActivatedInjection<CloudType>::parcelsToInject
(
	const scalar time0,
	const scalar time1
)
{
	if (sum(nParcelsInjected_) < nParcelsPerInjector_*positions_.size())
	{
		return positions_.size();
	}
	else
	{
		return 0;
	}
}


template<class CloudType>
tnbLib::scalar tnbLib::FieldActivatedInjection<CloudType>::volumeToInject
(
	const scalar time0,
	const scalar time1
)
{
	if (sum(nParcelsInjected_) < nParcelsPerInjector_*positions_.size())
	{
		return this->volumeTotal_ / nParcelsPerInjector_;
	}
	else
	{
		return 0;
	}
}


template<class CloudType>
void tnbLib::FieldActivatedInjection<CloudType>::setPositionAndCell
(
	const label parcelI,
	const label,
	const scalar,
	vector& position,
	label& cellOwner,
	label& tetFacei,
	label& tetPti
)
{
	position = positions_[parcelI];
	cellOwner = injectorCells_[parcelI];
	tetFacei = injectorTetFaces_[parcelI];
	tetPti = injectorTetPts_[parcelI];
}


template<class CloudType>
void tnbLib::FieldActivatedInjection<CloudType>::setProperties
(
	const label parcelI,
	const label,
	const scalar,
	typename CloudType::parcelType& parcel
)
{
	// set particle velocity
	parcel.U() = U0_;

	// set particle diameter
	parcel.d() = diameters_[parcelI];
}


template<class CloudType>
bool tnbLib::FieldActivatedInjection<CloudType>::fullyDescribed() const
{
	return false;
}


template<class CloudType>
bool tnbLib::FieldActivatedInjection<CloudType>::validInjection
(
	const label parcelI
)
{
	const label celli = injectorCells_[parcelI];

	if
		(
			nParcelsInjected_[parcelI] < nParcelsPerInjector_
			&& factor_*referenceField_[celli] > thresholdField_[celli]
			)
	{
		nParcelsInjected_[parcelI]++;
		return true;
	}

	return false;
}


// ************************************************************************* //