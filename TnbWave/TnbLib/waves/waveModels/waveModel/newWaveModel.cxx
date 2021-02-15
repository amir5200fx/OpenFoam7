#include <waveModel.hxx>

// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::waveModel> tnbLib::waveModel::New
(
	const objectRegistry& db,
	const dictionary& dict
)
{
	return waveModel::New(dict.lookup("type"), db, dict);
}


tnbLib::autoPtr<tnbLib::waveModel> tnbLib::waveModel::New
(
	const word& type,
	const objectRegistry& db,
	const dictionary& dict
)
{
	if (debug)
	{
		Info << "Selecting " << waveModel::typeName << " " << type << endl;
	}

	objectRegistryConstructorTable::iterator cstrIter =
		objectRegistryConstructorTablePtr_->find(type);

	if (cstrIter == objectRegistryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown " << waveModel::typeName << " " << type << nl << nl
			<< "Valid model types are:" << nl
			<< objectRegistryConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return cstrIter()(db, dict);
}


// ************************************************************************* //