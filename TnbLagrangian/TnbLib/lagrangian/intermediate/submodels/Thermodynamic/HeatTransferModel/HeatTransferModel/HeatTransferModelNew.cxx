#include <HeatTransferModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::autoPtr<tnbLib::HeatTransferModel<CloudType>>
tnbLib::HeatTransferModel<CloudType>::New
(
	const dictionary& dict,
	CloudType& owner
)
{
	const word modelType(dict.lookup("heatTransferModel"));

	Info << "Selecting heat transfer model " << modelType << endl;

	typename dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(modelType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown heat transfer model type "
			<< modelType << nl << nl
			<< "Valid heat transfer model types are:" << nl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<HeatTransferModel<CloudType>>(cstrIter()(dict, owner));
}


// ************************************************************************* //