#include <scatterModel.hxx>

#include <error.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::radiationModels::scatterModel>
tnbLib::radiationModels::scatterModel::New
(
	const dictionary& dict,
	const fvMesh& mesh
)
{
	const word modelType(dict.lookup("scatterModel"));

	Info << "Selecting scatterModel " << modelType << endl;

	dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(modelType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown scatterModel type "
			<< modelType << nl << nl
			<< "Valid scatterModel types are :" << nl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<scatterModel>(cstrIter()(dict, mesh));
}


// ************************************************************************* //