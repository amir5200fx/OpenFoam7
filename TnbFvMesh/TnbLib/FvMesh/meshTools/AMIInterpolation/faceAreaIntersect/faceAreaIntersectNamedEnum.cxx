#define FoamNamedEnum_EXPORT_DEFINE
#include <faceAreaIntersect.hxx>

namespace tnbLib
{
	template<>
	const char* NamedEnum<faceAreaIntersect::triangulationMode, 2>::names[] =
	{
		"fan",
		"mesh"
	};
}