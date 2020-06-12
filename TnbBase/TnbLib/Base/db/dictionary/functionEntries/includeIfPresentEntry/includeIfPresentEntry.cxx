#include <includeIfPresentEntry.hxx>

#include <dictionary.hxx>
#include <IFstream.hxx>
#include <addToMemberFunctionSelectionTable.hxx>
#include <fileOperation.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

const tnbLib::word tnbLib::functionEntries::includeIfPresentEntry::typeName
(
	tnbLib::functionEntries::includeIfPresentEntry::typeName_()
);

// Don't lookup the debug switch here as the debug switch dictionary
// might include includeIfPresentEntry
int tnbLib::functionEntries::includeIfPresentEntry::debug(0);

namespace tnbLib
{
	namespace functionEntries
	{
		addToMemberFunctionSelectionTable
		(
			functionEntry,
			includeIfPresentEntry,
			execute,
			dictionaryIstream
		);

		addToMemberFunctionSelectionTable
		(
			functionEntry,
			includeIfPresentEntry,
			execute,
			primitiveEntryIstream
		);
	}
}

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::functionEntries::includeIfPresentEntry::execute
(
	dictionary& parentDict,
	Istream& is
)
{
	const fileName fName(includeFileName(is, parentDict));
	// IFstream ifs(fName);
	autoPtr<ISstream> ifsPtr(fileHandler().NewIFstream(fName));
	ISstream& ifs = ifsPtr();

	if (ifs)
	{
		if (tnbLib::functionEntries::includeEntry::log)
		{
			Info << fName << endl;
		}
		parentDict.read(ifs);
	}

	return true;
}


bool tnbLib::functionEntries::includeIfPresentEntry::execute
(
	const dictionary& parentDict,
	primitiveEntry& entry,
	Istream& is
)
{
	const fileName fName(includeFileName(is, parentDict));
	// IFstream ifs(fName);
	autoPtr<ISstream> ifsPtr(fileHandler().NewIFstream(fName));
	ISstream& ifs = ifsPtr();

	if (ifs)
	{
		if (tnbLib::functionEntries::includeEntry::log)
		{
			Info << fName << endl;
		}
		entry.read(parentDict, ifs);
	}

	return true;
}

// ************************************************************************* //