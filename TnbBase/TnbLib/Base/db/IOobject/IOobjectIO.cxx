#include <IOobject.hxx>

#include <token.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<>
FoamBase_EXPORT tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const InfoProxy<IOobject>& ip)
{
	const IOobject& io = ip.t_;

	os << "IOobject: "
		<< io.type() << token::SPACE
		<< io.name() << token::SPACE
		<< "local:" << token::SPACE << io.local() << token::SPACE
		<< "readOpt:" << token::SPACE << io.readOpt() << token::SPACE
		<< "writeOpt:" << token::SPACE << io.writeOpt() << token::SPACE
		<< io.path() << endl;

	return os;
}


// ************************************************************************* //