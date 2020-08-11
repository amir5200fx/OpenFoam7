#include <thermophysicalFunction.hxx>

#include <HashTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(thermophysicalFunction, 0);
	defineRunTimeSelectionTable(thermophysicalFunction, dictionary);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::thermophysicalFunction> tnbLib::thermophysicalFunction::New
(
	const dictionary& dict
)
{
	if (debug)
	{
		InfoInFunction
			<< "Constructing thermophysicalFunction"
			<< endl;
	}

	const word thermophysicalFunctionType(dict.lookup("functionType"));

	dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(thermophysicalFunctionType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown thermophysicalFunction type "
			<< thermophysicalFunctionType
			<< nl << nl
			<< "Valid thermophysicalFunction types are :" << endl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< abort(FatalError);
	}

	return autoPtr<thermophysicalFunction>(cstrIter()(dict));
}


// ************************************************************************* //