#include <coordinateSystem.hxx>

#include <dictionary.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::coordinateSystem> tnbLib::coordinateSystem::New
(
	const objectRegistry& obr,
	const dictionary& dict
)
{
	const dictionary& coordDict = dict.subDict(typeName_());
	word coordType = coordDict.lookup("type");

	dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(coordType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalIOErrorInFunction
		(
			dict
		) << "Unknown coordinateSystem type "
			<< coordType << nl << nl
			<< "Valid coordinateSystem types are :" << nl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalIOError);
	}

	return autoPtr<coordinateSystem>(cstrIter()(obr, coordDict));
}


tnbLib::autoPtr<tnbLib::coordinateSystem> tnbLib::coordinateSystem::New
(
	const dictionary& dict
)
{
	const dictionary& coordDict = dict.subDict(typeName_());

	return autoPtr<coordinateSystem>(new coordinateSystem(coordDict));
}


tnbLib::autoPtr<tnbLib::coordinateSystem> tnbLib::coordinateSystem::New
(
	Istream& is
)
{
	const word name(is);
	const dictionary dict(is);

	return autoPtr<coordinateSystem>(new coordinateSystem(name, dict));
}


// ************************************************************************* //