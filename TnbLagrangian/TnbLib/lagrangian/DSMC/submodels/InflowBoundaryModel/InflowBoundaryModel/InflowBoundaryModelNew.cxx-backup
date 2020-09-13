#include <InflowBoundaryModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::autoPtr<tnbLib::InflowBoundaryModel<CloudType>>
tnbLib::InflowBoundaryModel<CloudType>::New
(
	const dictionary& dict,
	CloudType& owner
)
{
	const word modelType(dict.lookup("InflowBoundaryModel"));

	Info << "Selecting InflowBoundaryModel " << modelType << endl;

	typename dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(modelType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown InflowBoundaryModel type "
			<< modelType << nl << nl
			<< "Valid InflowBoundaryModel types are:" << nl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<InflowBoundaryModel<CloudType>>(cstrIter()(dict, owner));
}


// ************************************************************************* //