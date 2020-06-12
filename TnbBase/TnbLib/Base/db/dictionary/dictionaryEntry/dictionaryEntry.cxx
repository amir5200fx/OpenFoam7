#include <dictionaryEntry.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::dictionaryEntry::dictionaryEntry
(
	const keyType& key,
	const dictionary& parentDict,
	const dictionary& dict
)
	:
	entry(key),
	dictionary(parentDict, dict)
{}


tnbLib::dictionaryEntry::dictionaryEntry
(
	const dictionary& parentDict,
	const dictionaryEntry& dictEnt
)
	:
	entry(dictEnt),
	dictionary(parentDict, dictEnt)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::label tnbLib::dictionaryEntry::startLineNumber() const
{
	if (size())
	{
		return first()->startLineNumber();
	}
	else
	{
		return -1;
	}
}


tnbLib::label tnbLib::dictionaryEntry::endLineNumber() const
{
	if (size())
	{
		return last()->endLineNumber();
	}
	else
	{
		return -1;
	}
}


tnbLib::ITstream& tnbLib::dictionaryEntry::stream() const
{
	FatalIOErrorInFunction(*this)
		<< "Attempt to return dictionary entry as a primitive"
		<< abort(FatalIOError);

	return lookup("");
}


const tnbLib::dictionary& tnbLib::dictionaryEntry::dict() const
{
	return *this;
}


tnbLib::dictionary& tnbLib::dictionaryEntry::dict()
{
	return *this;
}


// ************************************************************************* //