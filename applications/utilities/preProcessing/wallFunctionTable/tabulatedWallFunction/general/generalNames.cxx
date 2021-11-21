#define FoamNamedEnum_EXPORT_DEFINE
#include <general.hxx>

namespace tnbLib
{

	template<>
	const char* tnbLib::NamedEnum
		<
		tnbLib::tabulatedWallFunctions::general::interpolationType,
		1
		>::names[] =
	{
		"linear"
	};
}

const
tnbLib::NamedEnum<tnbLib::tabulatedWallFunctions::general::interpolationType, 1>
tnbLib::tabulatedWallFunctions::general::interpolationTypeNames_;