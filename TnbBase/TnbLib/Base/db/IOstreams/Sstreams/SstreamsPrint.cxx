#include <ISstream.hxx>
#include <OSstream.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

void tnbLib::ISstream::print(Ostream& os) const
{
	os << "ISstream: " << name().c_str() << ' ';

	IOstream::print(os);
	IOstream::print(os, is_.rdstate());
}


void tnbLib::OSstream::print(Ostream& os) const
{
	os << "OSstream: " << name().c_str() << ' ';

	IOstream::print(os);
	IOstream::print(os, os_.rdstate());
}


// ************************************************************************* //