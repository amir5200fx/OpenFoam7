#include <uint.hxx>

#include <IOstreams.hxx>

// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

unsigned int tnbLib::readUint(Istream& is)
{
	unsigned int val;
	is >> val;

	return val;
}


// ************************************************************************* //