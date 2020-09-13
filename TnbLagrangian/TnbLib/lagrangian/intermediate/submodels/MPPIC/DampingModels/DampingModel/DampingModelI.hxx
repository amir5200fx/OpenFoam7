#pragma once
#include <TimeScaleModel.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::DampingModel<CloudType>::DampingModel(CloudType& owner)
	:
	CloudSubModelBase<CloudType>(owner),
	timeScaleModel_(nullptr)
{}


template<class CloudType>
tnbLib::DampingModel<CloudType>::DampingModel
(
	const dictionary& dict,
	CloudType& owner,
	const word& type
)
	:
	CloudSubModelBase<CloudType>(owner, dict, typeName, type),
	timeScaleModel_
	(
		TimeScaleModel::New
		(
			this->coeffDict().subDict(TimeScaleModel::typeName)
		)
	)
{}


template<class CloudType>
tnbLib::DampingModel<CloudType>::DampingModel(const DampingModel<CloudType>& cm)
	:
	CloudSubModelBase<CloudType>(cm),
	timeScaleModel_(cm.timeScaleModel_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::DampingModel<CloudType>::~DampingModel()
{}


// * * * * * * * * * * * * * * * *  Selector * * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::autoPtr<tnbLib::DampingModel<CloudType>>
tnbLib::DampingModel<CloudType>::New
(
	const dictionary& dict,
	CloudType& owner
)
{
	word modelType(dict.lookup(typeName));

	Info << "Selecting damping model " << modelType << endl;

	typename dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(modelType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown damping model type " << modelType
			<< ", constructor not in hash table" << nl << nl
			<< "    Valid damping model types are:" << nl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return
		autoPtr<DampingModel<CloudType>>
		(
			cstrIter()(dict, owner)
			);
}


// ************************************************************************* //