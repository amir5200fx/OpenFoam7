#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::autoPtr<tnbLib::PhaseChangeModel<CloudType>>
tnbLib::PhaseChangeModel<CloudType>::New
(
	const dictionary& dict,
	CloudType& owner
)
{
	const word modelType(dict.lookup("phaseChangeModel"));

	Info << "Selecting phase change model " << modelType << endl;

	typename dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(modelType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown phase change model type "
			<< modelType << nl << nl
			<< "Valid phase change model types are:" << nl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<PhaseChangeModel<CloudType>>(cstrIter()(dict, owner));
}


// ************************************************************************* //