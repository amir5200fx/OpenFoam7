#include <InjectionModelTemplate.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::autoPtr<tnbLib::InjectionModel<CloudType>>
tnbLib::InjectionModel<CloudType>::New
(
	const dictionary& dict,
	CloudType& owner
)
{
	const word modelType(dict.lookup("injectionModel"));

	Info << "Selecting injection model " << modelType << endl;

	typename dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(modelType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown injection model type "
			<< modelType << nl << nl
			<< "Valid injection model types are:" << nl
			<< dictionaryConstructorTablePtr_->sortedToc() << exit(FatalError);
	}

	return autoPtr<InjectionModel<CloudType>>(cstrIter()(dict, owner));
}


template<class CloudType>
tnbLib::autoPtr<tnbLib::InjectionModel<CloudType>>
tnbLib::InjectionModel<CloudType>::New
(
	const dictionary& dict,
	const word& modelName,
	const word& modelType,
	CloudType& owner
)
{
	Info << "Selecting injection model " << modelType << endl;

	typename dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(modelType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown injection model type "
			<< modelType << nl << nl
			<< "Valid injection model types are:" << nl
			<< dictionaryConstructorTablePtr_->sortedToc() << exit(FatalError);
	}

	return
		autoPtr<InjectionModel<CloudType>>
		(
			cstrIter()
			(
				dict,
				owner,
				modelName
				)
			);
}


// ************************************************************************* //