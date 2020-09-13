#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::autoPtr<tnbLib::CollisionModel<CloudType>>
tnbLib::CollisionModel<CloudType>::New
(
	const dictionary& dict,
	CloudType& owner
)
{
	word modelType(dict.lookup("collisionModel"));

	Info << "Selecting collision model " << modelType << endl;

	typename dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(modelType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown collision model type " << modelType
			<< ", constructor not in hash table" << nl << nl
			<< "    Valid collision model types are:" << nl
			<< dictionaryConstructorTablePtr_->sortedToc() << exit(FatalError);
	}

	return autoPtr<CollisionModel<CloudType>>(cstrIter()(dict, owner));
}


// ************************************************************************* //