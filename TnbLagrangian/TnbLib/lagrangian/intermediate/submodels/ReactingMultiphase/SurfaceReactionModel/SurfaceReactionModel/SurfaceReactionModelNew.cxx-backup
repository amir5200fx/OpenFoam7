#include <SurfaceReactionModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::autoPtr<tnbLib::SurfaceReactionModel<CloudType>>
tnbLib::SurfaceReactionModel<CloudType>::New
(
	const dictionary& dict,
	CloudType& owner
)
{
	const word modelType(dict.lookup("surfaceReactionModel"));

	Info << "Selecting surface reaction model " << modelType << endl;

	typename dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(modelType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown surface reaction model type "
			<< modelType << nl << nl
			<< "Valid surface reaction model types are:" << nl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<SurfaceReactionModel<CloudType>>(cstrIter()(dict, owner));
}


// ************************************************************************* //