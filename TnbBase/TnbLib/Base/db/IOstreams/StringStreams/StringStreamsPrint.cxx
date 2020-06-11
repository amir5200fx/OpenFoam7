#include <IStringStream.hxx>
#include <OStringStream.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

void tnbLib::IStringStream::print(Ostream& os) const
{
	os << "IStringStream " << name() << " : "
		<< "buffer = \n" << str() << tnbLib::endl;

	ISstream::print(os);
}


void tnbLib::OStringStream::print(Ostream& os) const
{
	os << "OStringStream " << name() << " : "
		<< "buffer = \n" << str() << tnbLib::endl;

	OSstream::print(os);
}


// ************************************************************************* //
