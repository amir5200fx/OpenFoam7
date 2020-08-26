#include <regionModelFunctionObject.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::regionModels::regionModelFunctionObject>
tnbLib::regionModels::regionModelFunctionObject::New
(
	const dictionary& dict,
	regionModel& region,
	const word& modelName
)
{
	const word modelType = dict.subDict(modelName).lookup("type");

	Info << "        " << modelType << endl;

	dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(modelType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown region model function type "
			<< modelType << nl << nl
			<< "Valid region model function types are:" << nl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return
		autoPtr<regionModelFunctionObject>
		(
			cstrIter()
			(
				dict.subDict(modelName),
				region
				)
			);
}


// ************************************************************************* //