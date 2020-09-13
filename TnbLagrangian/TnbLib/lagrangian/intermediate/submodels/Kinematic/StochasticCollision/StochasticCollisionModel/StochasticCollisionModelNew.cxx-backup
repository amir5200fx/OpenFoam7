#include <StochasticCollisionModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::autoPtr<tnbLib::StochasticCollisionModel<CloudType>>
tnbLib::StochasticCollisionModel<CloudType>::New
(
	const dictionary& dict,
	CloudType& owner
)
{
	word modelType(dict.lookup("stochasticCollisionModel"));

	Info << "Selecting stochastic collision model " << modelType << endl;

	typename dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(modelType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown model type type "
			<< modelType << ", constructor not in hash table" << nl << nl
			<< "    Valid model types are:" << nl
			<< dictionaryConstructorTablePtr_->sortedToc() << exit(FatalError);
	}

	return autoPtr<StochasticCollisionModel<CloudType>>
		(
			cstrIter()(dict, owner)
			);
}


// ************************************************************************* //