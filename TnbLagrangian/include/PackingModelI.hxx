#pragma once
#include <AveragingMethod.hxx>
#include <ParticleStressModel.hxx>
#include <CorrectionLimitingMethod.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::PackingModel<CloudType>::PackingModel(CloudType& owner)
	:
	CloudSubModelBase<CloudType>(owner),
	particleStressModel_(nullptr)
{}


template<class CloudType>
tnbLib::PackingModel<CloudType>::PackingModel
(
	const dictionary& dict,
	CloudType& owner,
	const word& type
)
	:
	CloudSubModelBase<CloudType>(owner, dict, typeName, type),
	particleStressModel_
	(
		ParticleStressModel::New
		(
			this->coeffDict().subDict(ParticleStressModel::typeName)
		)
	)
{}


template<class CloudType>
tnbLib::PackingModel<CloudType>::PackingModel(const PackingModel<CloudType>& cm)
	:
	CloudSubModelBase<CloudType>(cm),
	particleStressModel_(cm.particleStressModel_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::PackingModel<CloudType>::~PackingModel()
{}


// * * * * * * * * * * * * * * * * Selector  * * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::autoPtr<tnbLib::PackingModel<CloudType>>
tnbLib::PackingModel<CloudType>::New
(
	const dictionary& dict,
	CloudType& owner
)
{
	word modelType(dict.lookup(typeName));

	Info << "Selecting packing model " << modelType << endl;

	typename dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(modelType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown packing model type " << modelType
			<< ", constructor not in hash table" << nl << nl
			<< "    Valid packing model types are:" << nl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<PackingModel<CloudType>>(cstrIter()(dict, owner));
}


// ************************************************************************* //