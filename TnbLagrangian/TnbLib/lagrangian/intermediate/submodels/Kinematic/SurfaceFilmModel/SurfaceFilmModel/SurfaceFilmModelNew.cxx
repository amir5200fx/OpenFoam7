#include <SurfaceFilmModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::autoPtr<tnbLib::SurfaceFilmModel<CloudType>>
tnbLib::SurfaceFilmModel<CloudType>::New
(
	const dictionary& dict,
	CloudType& owner
)
{
	const word modelType(dict.lookup("surfaceFilmModel"));

	Info << "Selecting surface film model " << modelType << endl;

	typename dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(modelType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown surface film model type "
			<< modelType << nl << nl
			<< "Valid surface film model types are:" << nl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<SurfaceFilmModel<CloudType>>(cstrIter()(dict, owner));
}


// ************************************************************************* //