#include <dictionary.hxx>

#include <inputModeEntry.hxx>
#include <regExp.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::dictionary::dictionary
(
	const fileName& name,
	const dictionary& parentDict,
	Istream& is
)
	:
	dictionaryName(parentDict.name() + '.' + name),
	parent_(parentDict)
{
	read(is);
}


tnbLib::dictionary::dictionary(Istream& is)
	:
	dictionaryName(is.name()),
	parent_(dictionary::null)
{
	// Reset input mode as this is a "top-level" dictionary
	functionEntries::inputModeEntry::clear();

	read(is);
}


tnbLib::dictionary::dictionary(Istream& is, const bool keepHeader)
	:
	dictionaryName(is.name()),
	parent_(dictionary::null)
{
	// Reset input mode as this is a "top-level" dictionary
	functionEntries::inputModeEntry::clear();

	read(is, keepHeader);
}


// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::dictionary> tnbLib::dictionary::New(Istream& is)
{
	return autoPtr<dictionary>(new dictionary(is));
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool tnbLib::dictionary::read(Istream& is, const bool keepHeader)
{
	// Check for empty dictionary
	if (is.eof())
	{
		return true;
	}

	if (!is.good())
	{
		FatalIOErrorInFunction(is)
			<< "Istream not OK for reading dictionary "
			<< exit(FatalIOError);

		return false;
	}

	token currToken(is);
	if (currToken != token::BEGIN_BLOCK)
	{
		is.putBack(currToken);
	}

	while (!is.eof() && entry::New(*this, is))
	{
	}

	// normally remove the FoamFile header entry if it exists
	if (!keepHeader)
	{
		remove("FoamFile");
	}

	if (is.bad())
	{
		InfoInFunction
			<< "Istream not OK after reading dictionary " << name()
			<< endl;

		return false;
	}

	return true;
}


bool tnbLib::dictionary::read(Istream& is)
{
	return this->read(is, false);
}


bool tnbLib::dictionary::substituteKeyword(const word& keyword)
{
	word varName = keyword(1, keyword.size() - 1);

	// lookup the variable name in the given dictionary
	const entry* ePtr = lookupEntryPtr(varName, true, true);

	// if defined insert its entries into this dictionary
	if (ePtr != nullptr)
	{
		const dictionary& addDict = ePtr->dict();

		forAllConstIter(IDLList<entry>, addDict, iter)
		{
			add(iter());
		}

		return true;
	}

	return false;
}


// * * * * * * * * * * * * * * * IOstream Functions  * * * * * * * * * * * * //

void tnbLib::writeEntry(Ostream& os, const dictionary& value)
{
	os << value;
}


// * * * * * * * * * * * * * * Istream Operator  * * * * * * * * * * * * * * //

tnbLib::Istream& tnbLib::operator>>(Istream& is, dictionary& dict)
{
	// Reset input mode assuming this is a "top-level" dictionary
	functionEntries::inputModeEntry::clear();

	dict.clear();
	dict.name() = is.name();
	dict.read(is);

	return is;
}


// * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * * //

void tnbLib::dictionary::write(Ostream& os, bool subDict) const
{
	if (subDict)
	{
		os << nl << indent << token::BEGIN_BLOCK << incrIndent << nl;
	}

	forAllConstIter(IDLList<entry>, *this, iter)
	{
		const entry& e = *iter;

		// Write entry
		os << e;

		// Add extra new line between entries for "top-level" dictionaries
		if (!subDict && parent() == dictionary::null && e != *last())
		{
			os << nl;
		}

		// Check stream before going to next entry.
		if (!os.good())
		{
			WarningInFunction
				<< "Can't write entry " << iter().keyword()
				<< " for dictionary " << name()
				<< endl;
		}
	}

	if (subDict)
	{
		os << decrIndent << indent << token::END_BLOCK << endl;
	}
}


tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const dictionary& dict)
{
	dict.write(os, true);
	return os;
}


// ************************************************************************* //