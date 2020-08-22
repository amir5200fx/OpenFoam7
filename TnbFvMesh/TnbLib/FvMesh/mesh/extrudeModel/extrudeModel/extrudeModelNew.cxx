#include <extrudeModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::extrudeModel> tnbLib::extrudeModel::New
(
	const dictionary& dict
)
{
	const word modelType(dict.lookup("extrudeModel"));

	Info << "Selecting extrudeModel " << modelType << endl;

	dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(modelType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown extrudeModel type "
			<< modelType << nl << nl
			<< "Valid extrudeModel types are :" << nl
			<< dictionaryConstructorTablePtr_->sortedToc() << nl
			<< exit(FatalError);
	}

	return autoPtr<extrudeModel>(cstrIter()(dict));
}


// ************************************************************************* //