#include <absorptionEmissionModel.hxx>

#include <error.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::radiationModels::absorptionEmissionModel>
tnbLib::radiationModels::absorptionEmissionModel::New
(
	const dictionary& dict,
	const fvMesh& mesh
)
{
	const word modelType(dict.lookup("absorptionEmissionModel"));

	Info << "Selecting absorptionEmissionModel " << modelType << endl;

	dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(modelType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown absorptionEmissionModel type "
			<< modelType << nl << nl
			<< "Valid absorptionEmissionModel types are :" << nl
			<< dictionaryConstructorTablePtr_->sortedToc() << exit(FatalError);
	}

	return autoPtr<absorptionEmissionModel>(cstrIter()(dict, mesh));
}


// ************************************************************************* //