#include <rigidBodyRestraint.hxx>

// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::RBD::restraint>
tnbLib::RBD::restraint::New
(
	const word& name,
	const dictionary& dict,
	const rigidBodyModel& model
)
{
	const word restraintType(dict.lookup("type"));

	dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(restraintType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown restraint type "
			<< restraintType << nl << nl
			<< "Valid restraint types are : " << endl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<restraint>(cstrIter()(name, dict, model));
}


// ************************************************************************* //