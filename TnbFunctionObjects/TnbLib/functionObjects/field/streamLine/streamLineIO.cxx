#define FoamNamedEnum_EXPORT_DEFINE

#include <streamLine.hxx>

namespace tnbLib
{
	template<>
	const char*
		NamedEnum<functionObjects::streamLine::trackDirection, 3>::names[] =
	{ "forward", "backward", "both" };
}