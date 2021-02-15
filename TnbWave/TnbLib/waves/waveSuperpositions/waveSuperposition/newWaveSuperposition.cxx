#include <waveSuperposition.hxx>

// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

const tnbLib::waveSuperposition& tnbLib::waveSuperposition::New
(
	const objectRegistry& db
)
{
	if (db.foundObject<waveSuperposition>(dictName))
	{
		return db.lookupObject<waveSuperposition>(dictName);
	}

	const IOdictionary dict
	(
		IOobject
		(
			dictName,
			db.time().constant(),
			db,
			IOobject::MUST_READ,
			IOobject::NO_WRITE,
			false
		)
	);

	const word type =
		dict.lookupOrDefault<word>("type", waveSuperposition::typeName);

	objectRegistryConstructorTable::iterator cstrIter =
		objectRegistryConstructorTablePtr_->find(type);

	if (cstrIter == objectRegistryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown " << waveSuperposition::typeName << " " << type
			<< nl << nl << "Valid types are:" << nl
			<< objectRegistryConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	waveSuperposition* ptr = cstrIter()(db).ptr();

	ptr->store();

	return *ptr;
}


// ************************************************************************* //