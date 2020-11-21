#define FoamNamedEnum_EXPORT_DEFINE
#include <pointToCell.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	template<>
	const char* tnbLib::NamedEnum
		<
		tnbLib::pointToCell::pointAction,
		2
		>::names[] =
	{
		"any",
		"edge"
	};
}
