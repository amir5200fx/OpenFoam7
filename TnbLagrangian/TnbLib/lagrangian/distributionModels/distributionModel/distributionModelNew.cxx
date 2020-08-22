#include <distributionModel.hxx>

// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::distributionModel> tnbLib::distributionModel::New
(
	const dictionary& dict,
	Random& rndGen
)
{
	const word modelType(dict.lookup("type"));

	Info << "Selecting distribution model " << modelType << endl;

	dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(modelType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown distribution model type " << modelType << nl << nl
			<< "Valid distribution model types are:" << nl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<distributionModel>(cstrIter()(dict, rndGen));
}


// ************************************************************************* //