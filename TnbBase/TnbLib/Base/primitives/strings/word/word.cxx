#include <word.hxx>

#include <tnbDebug.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

const char* const tnbLib::word::typeName = "word";
int tnbLib::word::debug(tnbLib::debug::debugSwitch(word::typeName, 0));
const tnbLib::word tnbLib::word::null;


// * * * * * * * * * * * * * * * IOstream Functions  * * * * * * * * * * * * //

void tnbLib::writeEntry(Ostream& os, const word& value)
{
	os << value;
}


// ************************************************************************* //