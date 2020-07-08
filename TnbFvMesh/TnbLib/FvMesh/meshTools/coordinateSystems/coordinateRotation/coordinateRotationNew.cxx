#include <coordinateRotation.hxx>
#include <objectRegistry.hxx>

// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::coordinateRotation> tnbLib::coordinateRotation::New
(
	const dictionary& dict, const objectRegistry& obr
)
{
	if (debug)
	{
		Pout << "coordinateRotation::New(const dictionary&) : "
			<< "constructing coordinateRotation"
			<< endl;
	}

	word rotType = dict.lookup("type");

	objectRegistryConstructorTable::iterator cstrIter =
		objectRegistryConstructorTablePtr_->find(rotType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalIOErrorInFunction
		(
			dict
		) << "Unknown coordinateRotation type "
			<< rotType << nl << nl
			<< "Valid coordinateRotation types are :" << nl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalIOError);
	}

	return autoPtr<coordinateRotation>(cstrIter()(dict, obr));
}


tnbLib::autoPtr<tnbLib::coordinateRotation> tnbLib::coordinateRotation::New
(
	const dictionary& dict
)
{
	if (debug)
	{
		Pout << "coordinateRotation::New(const dictionary&) : "
			<< "constructing coordinateRotation"
			<< endl;
	}

	word rotType = dict.lookup("type");

	dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(rotType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalIOErrorInFunction
		(
			dict
		) << "Unknown coordinateRotation type "
			<< rotType << nl << nl
			<< "Valid coordinateRotation types are :" << nl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalIOError);
	}

	return autoPtr<coordinateRotation>(cstrIter()(dict));
}

// ************************************************************************* //