#include <int.hxx>

#include <IOstreams.hxx>

// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

int tnbLib::readInt(Istream& is)
{
	int val;
	is >> val;

	return val;
}


// ************************************************************************* //