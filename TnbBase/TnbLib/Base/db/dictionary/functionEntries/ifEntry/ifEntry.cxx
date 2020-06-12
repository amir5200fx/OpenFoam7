#include <ifEntry.hxx>

#include <Switch.hxx>
#include <addToMemberFunctionSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionEntries
	{
		defineTypeNameAndDebug(ifEntry, 0);

		addNamedToMemberFunctionSelectionTable
		(
			functionEntry,
			ifEntry,
			execute,
			dictionaryIstream,
			if
				);
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

bool tnbLib::functionEntries::ifEntry::execute
(
	DynamicList<filePos>& stack,
	dictionary& parentDict,
	Istream& is
)
{
	const label nNested = stack.size();

	stack.append(filePos(is.name(), is.lineNumber()));

	// Read line
	string line;
	dynamic_cast<ISstream&>(is).getLine(line);
	line += ';';
	IStringStream lineStream(line);
	const primitiveEntry e("ifEntry", parentDict, lineStream);
	const Switch doIf(e.stream());

	// Info<< "Using #" << typeName << " " << doIf
	//     << " at line " << stack.last().second()
	//     << " in file " <<  stack.last().first() << endl;

	bool ok = ifeqEntry::execute(doIf, stack, parentDict, is);

	if (stack.size() != nNested)
	{
		FatalIOErrorInFunction(parentDict)
			<< "Did not find matching #endif for condition starting"
			<< " at line " << stack.last().second()
			<< " in file " << stack.last().first() << exit(FatalIOError);
	}

	return ok;
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::functionEntries::ifEntry::execute
(
	dictionary& parentDict,
	Istream& is
)
{
	DynamicList<filePos> stack(10);
	return execute(stack, parentDict, is);
}


// ************************************************************************* //