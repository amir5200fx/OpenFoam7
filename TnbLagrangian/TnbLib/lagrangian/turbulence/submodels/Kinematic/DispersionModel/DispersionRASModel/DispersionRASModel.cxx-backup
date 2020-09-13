#include <DispersionRASModel.hxx>

#include <demandDrivenData.hxx>
#include <turbulenceModel.hxx>

// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

template<class CloudType>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::DispersionRASModel<CloudType>::kModel() const
{
	const objectRegistry& obr = this->owner().mesh();
	const word turbName =
		IOobject::groupName
		(
			turbulenceModel::propertiesName,
			this->owner().U().group()
		);

	if (obr.foundObject<turbulenceModel>(turbName))
	{
		const turbulenceModel& model =
			obr.lookupObject<turbulenceModel>(turbName);
		return model.k();
	}
	else
	{
		FatalErrorInFunction
			<< "Turbulence model not found in mesh database" << nl
			<< "Database objects include: " << obr.sortedToc()
			<< abort(FatalError);

		return tmp<volScalarField>(nullptr);
	}
}


template<class CloudType>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::DispersionRASModel<CloudType>::epsilonModel() const
{
	const objectRegistry& obr = this->owner().mesh();
	const word turbName =
		IOobject::groupName
		(
			turbulenceModel::propertiesName,
			this->owner().U().group()
		);

	if (obr.foundObject<turbulenceModel>(turbName))
	{
		const turbulenceModel& model =
			obr.lookupObject<turbulenceModel>(turbName);
		return model.epsilon();
	}
	else
	{
		FatalErrorInFunction
			<< "Turbulence model not found in mesh database" << nl
			<< "Database objects include: " << obr.sortedToc()
			<< abort(FatalError);

		return tmp<volScalarField>(nullptr);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::DispersionRASModel<CloudType>::DispersionRASModel
(
	const dictionary&,
	CloudType& owner
)
	:
	DispersionModel<CloudType>(owner),
	kPtr_(nullptr),
	ownK_(false),
	epsilonPtr_(nullptr),
	ownEpsilon_(false)
{}


template<class CloudType>
tnbLib::DispersionRASModel<CloudType>::DispersionRASModel
(
	const DispersionRASModel<CloudType>& dm
)
	:
	DispersionModel<CloudType>(dm),
	kPtr_(dm.kPtr_),
	ownK_(dm.ownK_),
	epsilonPtr_(dm.epsilonPtr_),
	ownEpsilon_(dm.ownEpsilon_)
{
	dm.ownK_ = false;
	dm.ownEpsilon_ = false;
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::DispersionRASModel<CloudType>::~DispersionRASModel()
{
	cacheFields(false);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
void tnbLib::DispersionRASModel<CloudType>::cacheFields(const bool store)
{
	if (store)
	{
		tmp<volScalarField> tk = this->kModel();
		if (tk.isTmp())
		{
			kPtr_ = tk.ptr();
			ownK_ = true;
		}
		else
		{
			kPtr_ = &tk();
			ownK_ = false;
		}

		tmp<volScalarField> tepsilon = this->epsilonModel();
		if (tepsilon.isTmp())
		{
			epsilonPtr_ = tepsilon.ptr();
			ownEpsilon_ = true;
		}
		else
		{
			epsilonPtr_ = &tepsilon();
			ownEpsilon_ = false;
		}
	}
	else
	{
		if (ownK_ && kPtr_)
		{
			deleteDemandDrivenData(kPtr_);
			ownK_ = false;
		}
		if (ownEpsilon_ && epsilonPtr_)
		{
			deleteDemandDrivenData(epsilonPtr_);
			ownEpsilon_ = false;
		}
	}
}


template<class CloudType>
void tnbLib::DispersionRASModel<CloudType>::write(Ostream& os) const
{
	DispersionModel<CloudType>::write(os);
	writeEntry(os, "ownK", ownK_);
	writeEntry(os, "ownEpsilon", ownEpsilon_);
}


// ************************************************************************* //