#include <calcEntry.hxx>

#include <addToMemberFunctionSelectionTable.hxx>
#include <dictionary.hxx>
#include <dynamicCode.hxx>
#include <codeStream.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionEntries
	{
		defineTypeNameAndDebug(calcEntry, 0);

		addToMemberFunctionSelectionTable
		(
			functionEntry,
			calcEntry,
			execute,
			dictionaryIstream
		);

		addToMemberFunctionSelectionTable
		(
			functionEntry,
			calcEntry,
			execute,
			primitiveEntryIstream
		);

	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::functionEntries::calcEntry::execute
(
	const dictionary& parentDict,
	primitiveEntry& thisEntry,
	Istream& is
)
{
	Info << "Using #calcEntry at line " << is.lineNumber()
		<< " in file " << parentDict.name() << endl;

	dynamicCode::checkSecurity
	(
		"functionEntries::calcEntry::execute(..)",
		parentDict
	);

	// Read string
	string s(is);
	// Make sure we stop this entry
	// is.putBack(token(token::END_STATEMENT, is.lineNumber()));

	// Construct codeDict for codeStream
	// must reference parent for stringOps::expand to work nicely.
	dictionary codeSubDict;
	codeSubDict.add("code", "os << (" + s + ");");
	dictionary codeDict(parentDict, codeSubDict);

	codeStream::streamingFunctionType function = codeStream::getFunction
	(
		parentDict,
		codeDict
	);

	// use function to write stream
	OStringStream os(is.format());
	(*function)(os, parentDict);

	// get the entry from this stream
	IStringStream resultStream(os.str());
	thisEntry.read(parentDict, resultStream);

	return true;
}


bool tnbLib::functionEntries::calcEntry::execute
(
	dictionary& parentDict,
	Istream& is
)
{
	Info << "Using #calcEntry at line " << is.lineNumber()
		<< " in file " << parentDict.name() << endl;

	dynamicCode::checkSecurity
	(
		"functionEntries::calcEntry::execute(..)",
		parentDict
	);

	// Read string
	string s(is);
	// Make sure we stop this entry
	// is.putBack(token(token::END_STATEMENT, is.lineNumber()));

	// Construct codeDict for codeStream
	// must reference parent for stringOps::expand to work nicely.
	dictionary codeSubDict;
	codeSubDict.add("code", "os << (" + s + ");");
	dictionary codeDict(parentDict, codeSubDict);

	codeStream::streamingFunctionType function = codeStream::getFunction
	(
		parentDict,
		codeDict
	);

	// use function to write stream
	OStringStream os(is.format());
	(*function)(os, parentDict);

	// get the entry from this stream
	IStringStream resultStream(os.str());
	parentDict.read(resultStream);

	return true;
}


// ************************************************************************* //