#include <dictionaryListEntry.hxx>

#include <keyType.hxx>
#include <IOstreams.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

tnbLib::label tnbLib::dictionaryListEntry::realSize(const dictionary& dict)
{
	if (dict.size() < 1 || dict.first()->keyword() != "FoamFile")
	{
		return dict.size();
	}
	else
	{
		return dict.size() - 1;
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::dictionaryListEntry::dictionaryListEntry
(
	const dictionary& parentDict,
	Istream& is
)
	:
	dictionaryEntry
	(
		word("entry" + tnbLib::name(realSize(parentDict))),
		parentDict,
		dictionary::null
	)
{
	token firstToken(is);
	if (firstToken.isLabel())
	{
		label s = firstToken.labelToken();

		is.readBeginList("List");

		for (label i = 0; i < s; i++)
		{
			if (!entry::New(*this, is))
			{
				FatalIOErrorInFunction(is)
					<< "Failed to read dictionary entry in list"
					<< exit(FatalIOError);
			}
		}
		is.readEndList("List");
	}
	else if
		(
			firstToken.isPunctuation()
			&& firstToken.pToken() == token::BEGIN_LIST
			)
	{
		while (true)
		{
			token nextToken(is);
			if
				(
					nextToken.isPunctuation()
					&& nextToken.pToken() == token::END_LIST
					)
			{
				break;
			}
			is.putBack(nextToken);

			if (!entry::New(*this, is))
			{
				FatalIOErrorInFunction(is)
					<< "Failed to read dictionary entry in list"
					<< exit(FatalIOError);
			}
		}
	}
	else
	{
		FatalIOErrorInFunction(is)
			<< "incorrect first token, expected <int> or '(', found "
			<< firstToken.info()
			<< exit(FatalIOError);
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::dictionaryListEntry::write(Ostream& os) const
{
	os << nl << indent << size()
		<< token::SPACE << "// " << keyword() << nl
		<< indent << token::BEGIN_LIST << incrIndent << nl;

	// Write contents
	dictionary::write(os, false);

	// Write end delimiter
	os << decrIndent << indent << token::END_LIST << nl;

	// Check state of IOstream
	os.check("Ostream& operator<<(Ostream&, const dictionaryListEntry&)");
}


// * * * * * * * * * * * * * * Ostream operator  * * * * * * * * * * * * * * //

FoamBase_EXPORT tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const dictionaryListEntry& de)
{
	de.write(os);
	return os;
}


template<>
FoamBase_EXPORT tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const InfoProxy<dictionaryListEntry>& ip
	)
{
	const dictionaryListEntry& e = ip.t_;

	os << "    dictionaryListEntry '" << e.keyword() << "'" << endl;

	return os;
}


// ************************************************************************* //