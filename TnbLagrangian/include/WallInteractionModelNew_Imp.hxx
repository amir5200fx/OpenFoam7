#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::autoPtr<tnbLib::WallInteractionModel<CloudType>>
tnbLib::WallInteractionModel<CloudType>::New
(
	const dictionary& dict,
	CloudType& owner
)
{
	const word modelType(dict.lookup("WallInteractionModel"));

	Info << "Selecting WallInteractionModel " << modelType << endl;

	typename dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(modelType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown WallInteractionModel type "
			<< modelType << nl << nl
			<< "Valid WallInteractionModel types are:" << nl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<WallInteractionModel<CloudType>>(cstrIter()(dict, owner));
}


// ************************************************************************* //