#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::autoPtr<tnbLib::PatchInteractionModel<CloudType>>
tnbLib::PatchInteractionModel<CloudType>::New
(
	const dictionary& dict,
	CloudType& owner
)
{
	const word modelType(dict.lookup("patchInteractionModel"));

	Info << "Selecting patch interaction model " << modelType << endl;

	typename dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(modelType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown patch interaction model type "
			<< modelType << nl << nl
			<< "Valid patch interaction model types are:" << nl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<PatchInteractionModel<CloudType>>(cstrIter()(dict, owner));
}


// ************************************************************************* //