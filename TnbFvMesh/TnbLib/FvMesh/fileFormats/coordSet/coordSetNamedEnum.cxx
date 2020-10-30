#include <coordSet.hxx>

// * * * * * * * * * * * * * Static Member Data  * * * * * * * * * * * * * * //

namespace tnbLib
{
	template<>
	const char* tnbLib::NamedEnum
		<
		tnbLib::coordSet::coordFormat,
		5
		>::names[] =
	{
		"xyz",
		"x",
		"y",
		"z",
		"distance"
	};
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //