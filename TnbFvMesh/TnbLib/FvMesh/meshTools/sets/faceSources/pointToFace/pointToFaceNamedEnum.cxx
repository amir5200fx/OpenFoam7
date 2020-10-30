#include <pointToFace.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	template<>
	const char* tnbLib::NamedEnum
		<
		tnbLib::pointToFace::pointAction,
		3
		>::names[] =
	{
		"any",
		"all",
		"edge"
	};
}