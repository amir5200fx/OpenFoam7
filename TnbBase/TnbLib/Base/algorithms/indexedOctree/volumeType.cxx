#include <volumeType.hxx>

#include <Istream.hxx> // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	template<>
	const char* tnbLib::NamedEnum
		<
		tnbLib::volumeType,
		4
		>::names[] =
	{
		"unknown",
		"mixed",
		"inside",
		"outside"
	};
}

const tnbLib::NamedEnum<tnbLib::volumeType, 4> tnbLib::volumeType::names;


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

FoamBase_EXPORT tnbLib::Istream& tnbLib::operator>>(Istream& is, volumeType& vt)
{
	// Read beginning of volumeType
	is.readBegin("volumeType");

	int type;
	is >> type;

	vt.t_ = static_cast<volumeType::type>(type);

	// Read end of volumeType
	is.readEnd("volumeType");

	// Check state of Istream
	is.check("operator>>(Istream&, volumeType&)");

	return is;
}


FoamBase_EXPORT tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const volumeType& vt)
{
	os << static_cast<int>(vt.t_);

	return os;
}


// ************************************************************************* //