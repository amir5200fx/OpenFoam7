#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::autoPtr<tnbLib::CompositionModel<CloudType>>
tnbLib::CompositionModel<CloudType>::New
(
	const dictionary& dict,
	CloudType& owner
)
{
	const word modelType(dict.lookup("compositionModel"));

	Info << "Selecting composition model " << modelType << endl;

	typename dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(modelType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown composition model type "
			<< modelType << nl << nl
			<< "Valid composition model types are:" << nl
			<< dictionaryConstructorTablePtr_->sortedToc() << nl
			<< exit(FatalError);
	}

	return autoPtr<CompositionModel<CloudType>>(cstrIter()(dict, owner));
}


// ************************************************************************* //