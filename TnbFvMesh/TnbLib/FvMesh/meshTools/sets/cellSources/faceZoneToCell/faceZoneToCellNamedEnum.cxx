#define FoamNamedEnum_EXPORT_DEFINE
#include <faceZoneToCell.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	template<>
	const char* tnbLib::NamedEnum
		<
		tnbLib::faceZoneToCell::faceAction,
		2
		>::names[] =
	{
		"master",
		"slave"
	};
}