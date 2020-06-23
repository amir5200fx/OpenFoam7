#include <faceZone.hxx>

#include <dictionary.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::faceZone> tnbLib::faceZone::New
(
	const word& name,
	const dictionary& dict,
	const label index,
	const faceZoneMesh& zm
)
{
	if (debug)
	{
		InfoInFunction << "Constructing faceZone " << name << endl;
	}

	const word zoneType(dict.lookup("type"));

	dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(zoneType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalIOErrorInFunction
		(
			dict
		) << "Unknown faceZone type "
			<< zoneType << nl << nl
			<< "Valid faceZone types are:" << nl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalIOError);
	}

	return autoPtr<faceZone>(cstrIter()(name, dict, index, zm));
}


// ************************************************************************* //