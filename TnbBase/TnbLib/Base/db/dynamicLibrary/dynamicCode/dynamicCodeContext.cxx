#include <dynamicCodeContext.hxx>

#include <stringOps.hxx>
#include <OSHA1stream.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::dynamicCodeContext::addLineDirective
(
	string& code,
	const label lineNum,
	const fileName& name
)
{
	code = "#line " + tnbLib::name(lineNum + 1) + " \"" + name + "\"\n" + code;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::dynamicCodeContext::dynamicCodeContext
(
	const dictionary& dict,
	const wordList& codeKeys
)
	:
	dict_(dict),
	code_(),
	options_(),
	libs_()
{
	// Expand all dictionary entries. Note that this removes any leading or
	// trailing whitespace, which is necessary for compilation options, and
	// doesn't hurt for everything else
	List<const entry*> codePtrs(codeKeys.size(), nullptr);
	forAll(codeKeys, i)
	{
		const word& key = codeKeys[i];
		codePtrs[i] = dict.lookupEntryPtr(key, false, false);
		if (codePtrs[i])
		{
			code_.insert
			(
				key,
				stringOps::expand
				(
					stringOps::trim(codePtrs[i]->stream()),
					dict
				)
			);
		}
		else
		{
			code_.insert(key, "");
		}
	}

	// Options
	const entry* optionsPtr = dict.lookupEntryPtr("codeOptions", false, false);
	if (optionsPtr)
	{
		options_ =
			stringOps::expand(stringOps::trim(optionsPtr->stream()), dict);
	}

	// Libs
	const entry* libsPtr = dict.lookupEntryPtr("codeLibs", false, false);
	if (libsPtr)
	{
		libs_ =
			stringOps::expand(stringOps::trim(libsPtr->stream()), dict);
	}

	// Calculate SHA1 digest from all entries
	OSHA1stream os;
	forAllConstIter(HashTable<string>, code_, iter)
	{
		os << iter();
	}
	os << options_ << libs_;
	sha1_ = os.digest();

	// Add line directive after calculating SHA1 since this includes
	// "processor..." in the path which differs between cores
	forAll(codeKeys, i)
	{
		if (codePtrs[i])
		{
			const word& key = codeKeys[i];
			addLineDirective
			(
				code_[key],
				codePtrs[i]->startLineNumber(),
				dict.name()
			);
		}
	}
}


// ************************************************************************* //