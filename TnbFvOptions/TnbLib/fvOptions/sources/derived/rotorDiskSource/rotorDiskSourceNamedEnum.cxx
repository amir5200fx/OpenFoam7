#define FoamNamedEnum_EXPORT_DEFINE
#include <rotorDiskSource.hxx>

namespace tnbLib
{

	template<> const char* NamedEnum<fv::rotorDiskSource::geometryModeType, 2>::
		names[] =
	{
		"auto",
		"specified"
	};

	const NamedEnum<fv::rotorDiskSource::geometryModeType, 2>
		fv::rotorDiskSource::geometryModeTypeNames_;

	template<> const char* NamedEnum<fv::rotorDiskSource::inletFlowType, 3>::
		names[] =
	{
		"fixed",
		"surfaceNormal",
		"local"
	};

	const NamedEnum<fv::rotorDiskSource::inletFlowType, 3>
		fv::rotorDiskSource::inletFlowTypeNames_;
}