#define FoamNamedEnum_EXPORT_DEFINE
#include <solidificationMeltingSource.hxx>

namespace tnbLib
{
	template<>
	const char* NamedEnum
		<
		fv::solidificationMeltingSource::thermoMode,
		2
		>::names[] =
	{
		"thermo",
		"lookup"
	};
}