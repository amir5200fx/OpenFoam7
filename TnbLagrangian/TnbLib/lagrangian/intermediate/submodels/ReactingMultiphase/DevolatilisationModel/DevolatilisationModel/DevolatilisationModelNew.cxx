#include <DevolatilisationModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::autoPtr<tnbLib::DevolatilisationModel<CloudType>>
tnbLib::DevolatilisationModel<CloudType>::New
(
	const dictionary& dict,
	CloudType& owner
)
{
	const word modelType(dict.lookup("devolatilisationModel"));

	Info << "Selecting devolatilisation model " << modelType << endl;

	typename dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(modelType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown devolatilisation model type "
			<< modelType << nl << nl
			<< "Valid devolatilisation model types are:" << nl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<DevolatilisationModel<CloudType>>(cstrIter()(dict, owner));
}


// ************************************************************************* //