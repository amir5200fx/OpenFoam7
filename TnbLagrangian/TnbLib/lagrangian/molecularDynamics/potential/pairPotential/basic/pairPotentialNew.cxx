#include <pairPotential.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::pairPotential> tnbLib::pairPotential::New
(
	const word& name,
	const dictionary& propDict
)
{
	const word potentialType(propDict.lookup("pairPotential"));

	Info << nl << "Selecting intermolecular pair potential "
		<< potentialType << " for "
		<< name << " interaction." << endl;

	dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(potentialType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown pairPotential type "
			<< potentialType << nl << nl
			<< "Valid pairPotentials are:" << nl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<pairPotential>(cstrIter()(name, propDict));
}


// ************************************************************************* //