#include <includeFuncEntry.hxx>

#include <functionObjectList.hxx>
#include <addToMemberFunctionSelectionTable.hxx>

#include <HashSet.hxx> // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionEntries
	{
		defineTypeNameAndDebug(includeFuncEntry, 0);

		addToMemberFunctionSelectionTable
		(
			functionEntry,
			includeFuncEntry,
			execute,
			dictionaryIstream
		);
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::functionEntries::includeFuncEntry::execute
(
	dictionary& parentDict,
	Istream& is
)
{
	const word fNameArgs(is);
	HashSet<word> selectedFields;

	return functionObjectList::readFunctionObject
	(
		fNameArgs,
		parentDict,
		selectedFields
	);
}


// ************************************************************************* //