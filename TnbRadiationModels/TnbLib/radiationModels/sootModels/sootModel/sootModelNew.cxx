#include <sootModel.hxx>

#include <error.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::radiationModels::sootModel>
tnbLib::radiationModels::sootModel::New
(
	const dictionary& dict,
	const fvMesh& mesh
)
{
	word modelType("none");

	if (dict.found("sootModel"))
	{
		dict.lookup("sootModel") >> modelType;

		Info << "Selecting sootModel " << modelType << endl;
	}

	dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(modelType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown sootModel type "
			<< modelType << nl << nl
			<< "Valid sootModel types are :" << nl
			<< dictionaryConstructorTablePtr_->sortedToc() << exit(FatalError);
	}

	const label tempOpen = modelType.find('<');

	const word className = modelType(0, tempOpen);

	return autoPtr<sootModel>(cstrIter()(dict, mesh, className));
}


// ************************************************************************* //