#include <writeLocalObjects.hxx>

#include <stringListOps.hxx>
#include <dictionary.hxx>

// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void tnbLib::functionObjects::writeLocalObjects::resetLocalObjectName
(
	const word& name
)
{
	localObjectNames_.clear();
	localObjectNames_.append(name);
}


void tnbLib::functionObjects::writeLocalObjects::resetLocalObjectNames
(
	const wordList& names
)
{
	localObjectNames_.clear();
	localObjectNames_.append(names);
}


tnbLib::wordList tnbLib::functionObjects::writeLocalObjects::objectNames()
{
	wordList names
	(
		subsetStrings(wordReListMatcher(writeObjectNames_), localObjectNames_)
	);

	return names;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::writeLocalObjects::writeLocalObjects
(
	const objectRegistry& obr,
	const Switch& log
)
	:
	writeObjectsBase(obr, log),
	localObjectNames_()
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObjects::writeLocalObjects::~writeLocalObjects()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::wordList&
tnbLib::functionObjects::writeLocalObjects::localObjectNames() const
{
	return localObjectNames_;
}


bool tnbLib::functionObjects::writeLocalObjects::read(const dictionary& dict)
{
	if (dict.found("objects"))
	{
		writeObjectsBase::read(dict);
	}
	else
	{
		resetWriteObjectName(wordRe(".*", wordRe::compOption::detect));
	}

	return true;
}


// ************************************************************************* //