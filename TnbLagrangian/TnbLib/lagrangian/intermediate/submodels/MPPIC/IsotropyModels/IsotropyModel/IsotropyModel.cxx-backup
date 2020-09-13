#include <IsotropyModel.hxx>

#include <TimeScaleModel.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::IsotropyModel<CloudType>::IsotropyModel(CloudType& owner)
	:
	CloudSubModelBase<CloudType>(owner),
	timeScaleModel_(nullptr)
{}


template<class CloudType>
tnbLib::IsotropyModel<CloudType>::IsotropyModel
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
tnbLib::IsotropyModel<CloudType>::IsotropyModel
(
	const IsotropyModel<CloudType>& cm
)
	:
	CloudSubModelBase<CloudType>(cm),
	timeScaleModel_(cm.timeScaleModel_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::IsotropyModel<CloudType>::~IsotropyModel()
{}


// * * * * * * * * * * * * * * * *  Selector * * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::autoPtr<tnbLib::IsotropyModel<CloudType>>
tnbLib::IsotropyModel<CloudType>::New
(
	const dictionary& dict,
	CloudType& owner
)
{
	word modelType(dict.lookup(typeName));

	Info << "Selecting isotropy model " << modelType << endl;

	typename dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(modelType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown isotropy model type " << modelType
			<< ", constructor not in hash table" << nl << nl
			<< "    Valid isotropy model types are:" << nl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return
		autoPtr<IsotropyModel<CloudType>>
		(
			cstrIter()(dict, owner)
			);
}


// ************************************************************************* //