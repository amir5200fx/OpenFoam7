#include <functionEntry.hxx>

#include <IOstreams.hxx>
#include <ISstream.hxx>
#include <dictionary.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineMemberFunctionSelectionTable
	(
		functionEntry,
		execute,
		dictionaryIstream
	);

	defineMemberFunctionSelectionTable
	(
		functionEntry,
		execute,
		primitiveEntryIstream
	);
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

tnbLib::token tnbLib::functionEntry::readLine(const word& key, Istream& is)
{
	string s;
	dynamic_cast<ISstream&>(is).getLine(s);

	return token(string(key + s), is.lineNumber());
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionEntry::functionEntry
(
	const word& key,
	const dictionary& dict,
	Istream& is
)
	:
	primitiveEntry
	(
		word(key + dict.name() + tnbLib::name(is.lineNumber())),
		readLine(key, is)
	)
{}


// * * * * * * * * * * * * Member Function Selectors * * * * * * * * * * * * //

bool tnbLib::functionEntry::execute
(
	const word& functionName,
	dictionary& parentDict,
	Istream& is
)
{
	is.fatalCheck
	(
		"functionEntry::execute"
		"(const word& functionName, dictionary& parentDict, Istream&)"
	);

	if (!executedictionaryIstreamMemberFunctionTablePtr_)
	{
		cerr << "functionEntry::execute"
			<< "(const word&, dictionary&, Istream&)"
			<< " not yet initialized, function = "
			<< functionName.c_str() << std::endl;

		// Return true to keep reading
		return true;
	}

	executedictionaryIstreamMemberFunctionTable::iterator mfIter =
		executedictionaryIstreamMemberFunctionTablePtr_->find(functionName);

	if (mfIter == executedictionaryIstreamMemberFunctionTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown functionEntry '" << functionName
			<< "' in " << is.name() << " near line " << is.lineNumber()
			<< nl << nl
			<< "Valid functionEntries are :" << endl
			<< executedictionaryIstreamMemberFunctionTablePtr_->toc()
			<< exit(FatalError);
	}

	return mfIter()(parentDict, is);
}


bool tnbLib::functionEntry::execute
(
	const word& functionName,
	const dictionary& parentDict,
	primitiveEntry& entry,
	Istream& is
)
{
	is.fatalCheck
	(
		"functionEntry::execute"
		"(const word&, const dictionary&, primitiveEntry&, Istream&)"
	);

	if (!executeprimitiveEntryIstreamMemberFunctionTablePtr_)
	{
		cerr << "functionEntry::execute"
			<< "(const word&, const dictionary&, primitiveEntry&, Istream&)"
			<< " not yet initialized, function = "
			<< functionName.c_str() << std::endl;

		// return true to keep reading anyhow
		return true;
	}

	executeprimitiveEntryIstreamMemberFunctionTable::iterator mfIter =
		executeprimitiveEntryIstreamMemberFunctionTablePtr_->find(functionName);

	if (mfIter == executeprimitiveEntryIstreamMemberFunctionTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown functionEntry '" << functionName
			<< "' in " << is.name() << " near line " << is.lineNumber()
			<< nl << nl
			<< "Valid functionEntries are :" << endl
			<< executeprimitiveEntryIstreamMemberFunctionTablePtr_->toc()
			<< exit(FatalError);
	}

	return mfIter()(parentDict, entry, is);
}


void tnbLib::functionEntry::write(Ostream& os) const
{
	// Contents should be single string token
	const token& t = operator[](0);
	const string& s = t.stringToken();

	for (size_t i = 0; i < s.size(); i++)
	{
		os.write(s[i]);
	}

	os << endl;
}


// ************************************************************************* //