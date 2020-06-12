#include <removeEntry.hxx>

#include <dictionary.hxx>
#include <stringListOps.hxx>
#include <IStringStream.hxx>
#include <OStringStream.hxx>
#include <addToMemberFunctionSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

const tnbLib::word tnbLib::functionEntries::removeEntry::typeName
(
	tnbLib::functionEntries::removeEntry::typeName_()
);

// Don't lookup the debug switch here as the debug switch dictionary
// might include removeEntry
int tnbLib::functionEntries::removeEntry::debug(0);

namespace tnbLib
{
	namespace functionEntries
	{
		addToMemberFunctionSelectionTable
		(
			functionEntry,
			removeEntry,
			execute,
			dictionaryIstream
		);
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::functionEntries::removeEntry::execute
(
	dictionary& parentDict,
	Istream& is
)
{
	wordList   dictKeys = parentDict.toc();
	wordReList patterns = readList<wordRe>(is);

	labelList indices = findStrings(patterns, dictKeys);

	forAll(indices, indexI)
	{
		parentDict.remove(dictKeys[indices[indexI]]);
	}

	return true;
}

// ************************************************************************* //