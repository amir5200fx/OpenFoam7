#include <ReactingCloudTemplate.hxx>

#include <CompositionModel.hxx>
#include <PhaseChangeModelTemplate.hxx>

// * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * * //

template<class CloudType>
void tnbLib::ReactingCloud<CloudType>::setModels()
{
	compositionModel_.reset
	(
		CompositionModel<ReactingCloud<CloudType>>::New
		(
			this->subModelProperties(),
			*this
		).ptr()
	);

	phaseChangeModel_.reset
	(
		PhaseChangeModel<ReactingCloud<CloudType>>::New
		(
			this->subModelProperties(),
			*this
		).ptr()
	);
}


template<class CloudType>
void tnbLib::ReactingCloud<CloudType>::checkSuppliedComposition
(
	const scalarField& YSupplied,
	const scalarField& Y,
	const word& YName
)
{
	if (YSupplied.size() != Y.size())
	{
		FatalErrorInFunction
			<< YName << " supplied, but size is not compatible with "
			<< "parcel composition: " << nl << "    "
			<< YName << "(" << YSupplied.size() << ") vs required composition "
			<< YName << "(" << Y.size() << ")" << nl
			<< abort(FatalError);
	}
}


template<class CloudType>
void tnbLib::ReactingCloud<CloudType>::cloudReset(ReactingCloud<CloudType>& c)
{
	CloudType::cloudReset(c);

	compositionModel_.reset(c.compositionModel_.ptr());
	phaseChangeModel_.reset(c.phaseChangeModel_.ptr());
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::ReactingCloud<CloudType>::ReactingCloud
(
	const word& cloudName,
	const volScalarField& rho,
	const volVectorField& U,
	const dimensionedVector& g,
	const SLGThermo& thermo,
	bool readFields
)
	:
	CloudType(cloudName, rho, U, g, thermo, false),
	reactingCloud(),
	cloudCopyPtr_(nullptr),
	constProps_(this->particleProperties()),
	compositionModel_(nullptr),
	phaseChangeModel_(nullptr),
	rhoTrans_(thermo.carrier().species().size())
{
	if (this->solution().active())
	{
		setModels();

		if (readFields)
		{
			parcelType::readFields(*this, this->composition());
			this->deleteLostParticles();
		}
	}

	// Set storage for mass source fields and initialise to zero
	forAll(rhoTrans_, i)
	{
		const word& specieName = thermo.carrier().species()[i];
		rhoTrans_.set
		(
			i,
			new volScalarField::Internal
			(
				IOobject
				(
					this->name() + ":rhoTrans_" + specieName,
					this->db().time().timeName(),
					this->db(),
					IOobject::READ_IF_PRESENT,
					IOobject::AUTO_WRITE
				),
				this->mesh(),
				dimensionedScalar(dimMass, 0)
			)
		);
	}

	if (this->solution().resetSourcesOnStartup())
	{
		resetSourceTerms();
	}
}


template<class CloudType>
tnbLib::ReactingCloud<CloudType>::ReactingCloud
(
	ReactingCloud<CloudType>& c,
	const word& name
)
	:
	CloudType(c, name),
	reactingCloud(),
	cloudCopyPtr_(nullptr),
	constProps_(c.constProps_),
	compositionModel_(c.compositionModel_->clone()),
	phaseChangeModel_(c.phaseChangeModel_->clone()),
	rhoTrans_(c.rhoTrans_.size())
{
	forAll(c.rhoTrans_, i)
	{
		const word& specieName = this->thermo().carrier().species()[i];
		rhoTrans_.set
		(
			i,
			new volScalarField::Internal
			(
				IOobject
				(
					this->name() + ":rhoTrans_" + specieName,
					this->db().time().timeName(),
					this->db(),
					IOobject::NO_READ,
					IOobject::NO_WRITE,
					false
				),
				c.rhoTrans_[i]
			)
		);
	}
}


template<class CloudType>
tnbLib::ReactingCloud<CloudType>::ReactingCloud
(
	const fvMesh& mesh,
	const word& name,
	const ReactingCloud<CloudType>& c
)
	:
	CloudType(mesh, name, c),
	reactingCloud(),
	cloudCopyPtr_(nullptr),
	constProps_(),
	compositionModel_(c.compositionModel_->clone()),
	//    compositionModel_(nullptr),
	phaseChangeModel_(nullptr),
	rhoTrans_(0)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::ReactingCloud<CloudType>::~ReactingCloud()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
void tnbLib::ReactingCloud<CloudType>::setParcelThermoProperties
(
	parcelType& parcel,
	const scalar lagrangianDt
)
{
	CloudType::setParcelThermoProperties(parcel, lagrangianDt);

	parcel.Y() = composition().YMixture0();
}


template<class CloudType>
void tnbLib::ReactingCloud<CloudType>::checkParcelProperties
(
	parcelType& parcel,
	const scalar lagrangianDt,
	const bool fullyDescribed
)
{
	CloudType::checkParcelProperties(parcel, lagrangianDt, fullyDescribed);

	if (fullyDescribed)
	{
		checkSuppliedComposition
		(
			parcel.Y(),
			composition().YMixture0(),
			"YMixture"
		);
	}

	// derived information - store initial mass
	parcel.mass0() = parcel.mass();
}


template<class CloudType>
void tnbLib::ReactingCloud<CloudType>::storeState()
{
	cloudCopyPtr_.reset
	(
		static_cast<ReactingCloud<CloudType>*>
		(
			clone(this->name() + "Copy").ptr()
			)
	);
}


template<class CloudType>
void tnbLib::ReactingCloud<CloudType>::restoreState()
{
	cloudReset(cloudCopyPtr_());
	cloudCopyPtr_.clear();
}


template<class CloudType>
void tnbLib::ReactingCloud<CloudType>::resetSourceTerms()
{
	CloudType::resetSourceTerms();
	forAll(rhoTrans_, i)
	{
		rhoTrans_[i].field() = 0.0;
	}
}


template<class CloudType>
void tnbLib::ReactingCloud<CloudType>::relaxSources
(
	const ReactingCloud<CloudType>& cloudOldTime
)
{
	CloudType::relaxSources(cloudOldTime);

	typedef volScalarField::Internal dsfType;

	forAll(rhoTrans_, fieldi)
	{
		dsfType& rhoT = rhoTrans_[fieldi];
		const dsfType& rhoT0 = cloudOldTime.rhoTrans()[fieldi];
		this->relax(rhoT, rhoT0, "rho");
	}
}


template<class CloudType>
void tnbLib::ReactingCloud<CloudType>::scaleSources()
{
	CloudType::scaleSources();

	typedef volScalarField::Internal dsfType;

	forAll(rhoTrans_, fieldi)
	{
		dsfType& rhoT = rhoTrans_[fieldi];
		this->scale(rhoT, "rho");
	}
}


template<class CloudType>
void tnbLib::ReactingCloud<CloudType>::evolve()
{
	if (this->solution().canEvolve())
	{
		typename parcelType::trackingData td(*this);

		this->solve(*this, td);
	}
}


template<class CloudType>
void tnbLib::ReactingCloud<CloudType>::autoMap(const mapPolyMesh& mapper)
{
	Cloud<parcelType>::autoMap(mapper);

	this->updateMesh();
}


template<class CloudType>
void tnbLib::ReactingCloud<CloudType>::info()
{
	CloudType::info();

	this->phaseChange().info(Info);
}


template<class CloudType>
void tnbLib::ReactingCloud<CloudType>::writeFields() const
{
	if (compositionModel_.valid())
	{
		CloudType::particleType::writeFields(*this, this->composition());
	}
}


// ************************************************************************* //