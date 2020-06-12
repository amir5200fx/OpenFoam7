#include <negEntry.hxx>

#include <addToMemberFunctionSelectionTable.hxx>
#include <dictionary.hxx> // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionEntries
	{
		defineTypeNameAndDebug(negEntry, 0);

		addToMemberFunctionSelectionTable
		(
			functionEntry,
			negEntry,
			execute,
			dictionaryIstream
		);

		addToMemberFunctionSelectionTable
		(
			functionEntry,
			negEntry,
			execute,
			primitiveEntryIstream
		);
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::string tnbLib::functionEntries::negEntry::negateVariable
(
	const dictionary& parentDict,
	Istream& is
)
{
	// Read variable name as a word including the '$'
	const word varWord(is);

	if (varWord[0] != '$')
	{
		FatalIOErrorInFunction
		(
			parentDict
		) << "Expected variable name beginning with a '$' but found '"
			<< varWord << "'" << exit(FatalIOError);

		return string::null;
	}

	// Strip the leading '$' from the variable name
	const string varName = varWord(1, varWord.size() - 1);

	// Lookup the variable name in the parent dictionary....
	const entry* ePtr = parentDict.lookupScopedEntryPtr(varName, true, false);

	if (ePtr && ePtr->isStream())
	{
		const token variable(ePtr->stream());

		// Convert to a string
		OStringStream os(is.format());
		os << variable;
		const string str(os.str());

		// Negate
		if (str[0] == '-')
		{
			return str(1, str.size() - 1);
		}
		else
		{
			return '-' + str;
		}
	}
	else
	{
		FatalIOErrorInFunction
		(
			parentDict
		) << "Illegal dictionary variable name " << varName << endl
			<< "Valid dictionary entries are " << parentDict.toc()
			<< exit(FatalIOError);

		return string::null;
	}
}


bool tnbLib::functionEntries::negEntry::execute
(
	const dictionary& parentDict,
	primitiveEntry& thisEntry,
	Istream& is
)
{
	// Reinsert negated variable into entry
	IStringStream resultStream(negateVariable(parentDict, is));
	thisEntry.read(parentDict, resultStream);

	return true;
}


bool tnbLib::functionEntries::negEntry::execute
(
	dictionary& parentDict,
	Istream& is
)
{
	// Reinsert negated variable into dictionary
	IStringStream resultStream(negateVariable(parentDict, is));
	parentDict.read(resultStream);

	return true;
}


// ************************************************************************* //