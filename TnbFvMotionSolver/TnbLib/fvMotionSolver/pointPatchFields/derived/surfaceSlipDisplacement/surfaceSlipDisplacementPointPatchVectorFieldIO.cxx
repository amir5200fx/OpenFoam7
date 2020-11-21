#define FoamNamedEnum_EXPORT_DEFINE

#include <surfaceSlipDisplacementPointPatchVectorField.hxx>

namespace tnbLib
{
	template<>
	const char*
		NamedEnum<surfaceSlipDisplacementPointPatchVectorField::projectMode, 3>::
		names[] =
	{
		"nearest",
		"pointNormal",
		"fixedNormal"
	};
}