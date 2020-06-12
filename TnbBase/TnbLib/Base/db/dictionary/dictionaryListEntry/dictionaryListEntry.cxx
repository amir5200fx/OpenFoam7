#include <dictionaryListEntry.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::dictionaryListEntry::dictionaryListEntry
(
	const dictionary& parentDict,
	const dictionaryListEntry& dictEnt
)
	:
	dictionaryEntry(parentDict, dictEnt)
{}


// ************************************************************************* //