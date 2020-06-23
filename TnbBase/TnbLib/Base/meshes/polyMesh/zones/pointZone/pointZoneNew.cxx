#include <pointZone.hxx>

#include <dictionary.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::pointZone> tnbLib::pointZone::New
(
	const word& name,
	const dictionary& dict,
	const label index,
	const pointZoneMesh& zm
)
{
	if (debug)
	{
		InfoInFunction << "Constructing pointZone " << name << endl;
	}

	const word zoneType(dict.lookup("type"));

	dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(zoneType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalIOErrorInFunction
		(
			dict
		) << "Unknown pointZone type "
			<< zoneType << nl << nl
			<< "Valid pointZone types are:" << nl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalIOError);
	}

	return autoPtr<pointZone>(cstrIter()(name, dict, index, zm));
}


// ************************************************************************* //