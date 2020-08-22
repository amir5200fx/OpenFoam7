#include <tetherPotential.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::tetherPotential> tnbLib::tetherPotential::New
(
	const word& name,
	const dictionary& propDict
)
{
	const word potentialType(propDict.lookup("tetherPotential"));

	Info << nl << "Selecting tether potential " << potentialType
		<< " for " << name << endl;

	dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(potentialType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown tetherPotential type "
			<< potentialType << nl << nl
			<< "Valid tetherPotentials are:" << nl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<tetherPotential>(cstrIter()(name, propDict));
}


// ************************************************************************* //