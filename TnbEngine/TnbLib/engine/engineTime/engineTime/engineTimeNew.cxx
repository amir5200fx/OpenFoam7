#include <engineTime.hxx>

#include <IFstream.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::engineTime> tnbLib::engineTime::New
(
	const word& name,
	const fileName& rootPath,
	const fileName& caseName,
	const fileName& systemName,
	const fileName& constantName,
	const fileName& dictName
)
{
	IFstream engineDictFile("." / constantName / dictName);

	dictionary engineDict(engineDictFile);

	const word engineType
	(
		engineDict.lookupOrDefault<word>("engineType", "crankConRod")
	);

	Info << "Selecting engine type " << engineType << endl;

	dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(engineType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown engine type "
			<< engineType << nl << nl
			<< "Valid engine types are :" << nl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<engineTime>
		(
			cstrIter()
			(
				name,
				rootPath,
				caseName,
				systemName,
				constantName,
				dictName
				)
			);
}


// ************************************************************************* //