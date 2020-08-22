#include <polyMeshModifier.hxx>

#include <dictionary.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::polyMeshModifier> tnbLib::polyMeshModifier::New
(
	const word& name,
	const dictionary& dict,
	const label index,
	const polyTopoChanger& mme
)
{
	if (debug)
	{
		InfoInFunction << "Constructing polyMeshModifier" << endl;
	}

	const word modifierType(dict.lookup("type"));

	dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(modifierType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalIOErrorInFunction
		(
			dict
		) << "Unknown polyMeshModifier type "
			<< modifierType << nl << nl
			<< "Valid polyMeshModifier types are :" << endl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalIOError);
	}

	return autoPtr<polyMeshModifier>(cstrIter()(name, dict, index, mme));
}


// ************************************************************************* //