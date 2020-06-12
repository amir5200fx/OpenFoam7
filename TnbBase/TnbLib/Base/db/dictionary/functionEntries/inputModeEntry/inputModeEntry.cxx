#include <inputModeEntry.hxx>

#include <dictionary.hxx>
#include <addToMemberFunctionSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

const tnbLib::word tnbLib::functionEntries::inputModeEntry::typeName
(
	tnbLib::functionEntries::inputModeEntry::typeName_()
);

// Don't lookup the debug switch here as the debug switch dictionary
// might include inputModeEntries
int tnbLib::functionEntries::inputModeEntry::debug(0);

tnbLib::functionEntries::inputModeEntry::inputMode
tnbLib::functionEntries::inputModeEntry::mode_(MERGE);

namespace tnbLib
{
	namespace functionEntries
	{
		addToMemberFunctionSelectionTable
		(
			functionEntry,
			inputModeEntry,
			execute,
			dictionaryIstream
		);
	}
}

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

// we could combine this into execute() directly, but leave it here for now
void tnbLib::functionEntries::inputModeEntry::setMode(Istream& is)
{
	clear();

	word mode(is);
	if (mode == "merge" || mode == "default")
	{
		mode_ = MERGE;
	}
	else if (mode == "overwrite")
	{
		mode_ = OVERWRITE;
	}
	else if (mode == "protect")
	{
		mode_ = PROTECT;
	}
	else if (mode == "warn")
	{
		mode_ = WARN;
	}
	else if (mode == "error")
	{
		mode_ = ERROR;
	}
	else
	{
		WarningInFunction
			<< "unsupported input mode '" << mode
			<< "' ... defaulting to 'merge'"
			<< endl;
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::functionEntries::inputModeEntry::execute
(
	dictionary& parentDict,
	Istream& is
)
{
	setMode(is);
	return true;
}


void tnbLib::functionEntries::inputModeEntry::clear()
{
	mode_ = MERGE;
}


bool tnbLib::functionEntries::inputModeEntry::merge()
{
	return mode_ == MERGE;
}


bool tnbLib::functionEntries::inputModeEntry::overwrite()
{
	return mode_ == OVERWRITE;
}


bool tnbLib::functionEntries::inputModeEntry::protect()
{
	return mode_ == PROTECT;
}

bool tnbLib::functionEntries::inputModeEntry::error()
{
	return mode_ == ERROR;
}


// ************************************************************************* //