#include <fieldValue.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::functionObjects::fieldValue>
tnbLib::functionObjects::fieldValue::New
(
	const word& name,
	const objectRegistry& obr,
	const dictionary& dict,
	const bool output
)
{
	const word modelType(dict.lookup("type"));

	if (output)
	{
		Info << "Selecting " << typeName << " " << modelType << endl;
	}

	dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(modelType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown " << typeName << " type "
			<< modelType << nl << nl
			<< "Valid " << typeName << " types are:" << nl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<fieldValue>(cstrIter()(name, obr, dict));
}


// ************************************************************************* //