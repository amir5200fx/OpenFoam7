#include <LESfilter.hxx>

#include <error.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(LESfilter, 0);
	defineRunTimeSelectionTable(LESfilter, dictionary);
}


// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::LESfilter> tnbLib::LESfilter::New
(
	const fvMesh& mesh,
	const dictionary& dict,
	const word& filterDictName
)
{
	const word filterType(dict.lookup(filterDictName));

	dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(filterType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown LESfilter type "
			<< filterType << nl << nl
			<< "Valid LESfilter types are :" << endl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<LESfilter>(cstrIter()(mesh, dict));
}


// ************************************************************************* //