#define FoamNamedEnum_EXPORT_DEFINE
#include <cellToFace.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	template<>
	const char* tnbLib::NamedEnum
		<
		tnbLib::cellToFace::cellAction,
		2
		>::names[] =
	{
		"all",
		"both"
	};
}