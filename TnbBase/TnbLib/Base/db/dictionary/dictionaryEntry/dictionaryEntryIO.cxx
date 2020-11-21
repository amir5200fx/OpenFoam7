#include <dictionaryEntry.hxx>

#include <keyType.hxx>
#include <IOstreams.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::dictionaryEntry::dictionaryEntry
(
	const dictionary& parentDict,
	Istream& is
)
	:
	entry(keyType(is)),
	dictionary(parentDict, is)
{
	is.fatalCheck
	(
		"dictionaryEntry::dictionaryEntry"
		"(const dictionary& parentDict, Istream&)"
	);
}


tnbLib::dictionaryEntry::dictionaryEntry
(
	const keyType& key,
	const dictionary& parentDict,
	Istream& is
)
	:
	entry(key),
	dictionary(key, parentDict, is)
{
	is.fatalCheck
	(
		"dictionaryEntry::dictionaryEntry"
		"(const keyType&, const dictionary& parentDict, Istream&)"
	);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::dictionaryEntry::write(Ostream& os) const
{
	// write keyword with indent but without trailing spaces
	os.indent();
	os.write(keyword());
	dictionary::write(os);
}


// * * * * * * * * * * * * * * Ostream operator  * * * * * * * * * * * * * * //

FoamBase_EXPORT tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const dictionaryEntry& de)
{
	de.write(os);
	return os;
}


template<>
FoamBase_EXPORT tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const InfoProxy<dictionaryEntry>& ip
	)
{
	const dictionaryEntry& e = ip.t_;

	os << "    dictionaryEntry '" << e.keyword() << "'" << endl;

	return os;
}


// ************************************************************************* //