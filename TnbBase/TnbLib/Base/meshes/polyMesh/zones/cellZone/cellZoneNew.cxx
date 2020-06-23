#include <cellZone.hxx>

#include <dictionary.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::cellZone> tnbLib::cellZone::New
(
	const word& name,
	const dictionary& dict,
	const label index,
	const cellZoneMesh& zm
)
{
	if (debug)
	{
		InfoInFunction << "Constructing cellZone " << name << endl;
	}

	const word zoneType(dict.lookup("type"));

	dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(zoneType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalIOErrorInFunction
		(
			dict
		) << "Unknown cellZone type "
			<< zoneType << nl << nl
			<< "Valid cellZone types are:" << nl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalIOError);
	}

	return autoPtr<cellZone>(cstrIter()(name, dict, index, zm));
}


// ************************************************************************* //