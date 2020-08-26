#include <ThermoLookupTableInjection.hxx>

#include <scalarIOList.hxx>
#include <Random.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::ThermoLookupTableInjection<CloudType>::ThermoLookupTableInjection
(
	const dictionary& dict,
	CloudType& owner,
	const word& modelName
)
	:
	InjectionModel<CloudType>(dict, owner, modelName, typeName),
	inputFileName_(this->coeffDict().lookup("inputFile")),
	duration_(readScalar(this->coeffDict().lookup("duration"))),
	parcelsPerSecond_
	(
		readScalar(this->coeffDict().lookup("parcelsPerSecond"))
	),
	randomise_(readBool(this->coeffDict().lookup("randomise"))),
	injectors_
	(
		tnbLib::IOobject
		(
			inputFileName_,
			owner.db().time().constant(),
			owner.db(),
			tnbLib::IOobject::MUST_READ,
			tnbLib::IOobject::NO_WRITE
		)
	),
	injectorCells_(0),
	injectorTetFaces_(0),
	injectorTetPts_(0)
{
	duration_ = owner.db().time().userTimeToTime(duration_);

	// Set/cache the injector cells
	injectorCells_.setSize(injectors_.size());
	injectorTetFaces_.setSize(injectors_.size());
	injectorTetPts_.setSize(injectors_.size());

	updateMesh();

	// Determine volume of particles to inject
	this->volumeTotal_ = 0.0;
	forAll(injectors_, i)
	{
		this->volumeTotal_ += injectors_[i].mDot() / injectors_[i].rho();
	}
	this->volumeTotal_ *= duration_;
}


template<class CloudType>
tnbLib::ThermoLookupTableInjection<CloudType>::ThermoLookupTableInjection
(
	CloudType& owner,  // Edited by amir
	const ThermoLookupTableInjection<CloudType>& im
)
	:
	InjectionModel<CloudType>(im),
	inputFileName_(im.inputFileName_),
	duration_(im.duration_),
	parcelsPerSecond_(im.parcelsPerSecond_),
	randomise_(im.randomise_),
	injectors_(im.injectors_),
	injectorCells_(im.injectorCells_),
	injectorTetFaces_(im.injectorTetFaces_),
	injectorTetPts_(im.injectorTetPts_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::ThermoLookupTableInjection<CloudType>::~ThermoLookupTableInjection()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
void tnbLib::ThermoLookupTableInjection<CloudType>::updateMesh()
{
	// Set/cache the injector cells
	forAll(injectors_, i)
	{
		this->findCellAtPosition
		(
			injectorCells_[i],
			injectorTetFaces_[i],
			injectorTetPts_[i],
			injectors_[i].x()
		);
	}
}


template<class CloudType>
tnbLib::scalar tnbLib::ThermoLookupTableInjection<CloudType>::timeEnd() const
{
	return this->SOI_ + duration_;
}


template<class CloudType>
tnbLib::label tnbLib::ThermoLookupTableInjection<CloudType>::parcelsToInject
(
	const scalar time0,
	const scalar time1
)
{
	if ((time0 >= 0.0) && (time0 < duration_))
	{
		return floor(injectorCells_.size()*(time1 - time0)*parcelsPerSecond_);
	}
	else
	{
		return 0;
	}
}


template<class CloudType>
tnbLib::scalar tnbLib::ThermoLookupTableInjection<CloudType>::volumeToInject
(
	const scalar time0,
	const scalar time1
)
{
	scalar volume = 0.0;
	if ((time0 >= 0.0) && (time0 < duration_))
	{
		forAll(injectors_, i)
		{
			volume += injectors_[i].mDot() / injectors_[i].rho()*(time1 - time0);
		}
	}

	return volume;
}


template<class CloudType>
void tnbLib::ThermoLookupTableInjection<CloudType>::setPositionAndCell
(
	const label parcelI,
	const label nParcels,
	const scalar time,
	vector& position,
	label& cellOwner,
	label& tetFacei,
	label& tetPti
)
{
	label injectorI = 0;
	if (randomise_)
	{
		Random& rnd = this->owner().rndGen();
		injectorI = rnd.sampleAB<label>(0, injectorCells_.size());
	}
	else
	{
		injectorI = parcelI * injectorCells_.size() / nParcels;
	}

	position = injectors_[injectorI].x();
	cellOwner = injectorCells_[injectorI];
	tetFacei = injectorTetFaces_[injectorI];
	tetPti = injectorTetPts_[injectorI];
}


template<class CloudType>
void tnbLib::ThermoLookupTableInjection<CloudType>::setProperties
(
	const label parcelI,
	const label nParcels,
	const scalar,
	/*typename CloudType::parcelType* pPtr*/  typename CloudType::parcelType& parcel  // Edited by amir
)
{
	label injectorI = parcelI * injectorCells_.size() / nParcels;

	// set particle velocity
	parcel.U() = injectors_[injectorI].U();

	// set particle diameter
	parcel.d() = injectors_[injectorI].d();

	// set particle density
	parcel.rho() = injectors_[injectorI].rho();

	// set particle temperature
	parcel.T() = injectors_[injectorI].T();

	// set particle specific heat capacity
	parcel.cp() = injectors_[injectorI].cp();
}

// Edited by amir
//template<class CloudType>
//bool tnbLib::ThermoLookupTableInjection<CloudType>::fullyDescribed() const
//{
//	return true;
//}


template<class CloudType>
bool tnbLib::ThermoLookupTableInjection<CloudType>::validInjection(const label)
{
	return true;
}


// ************************************************************************* //