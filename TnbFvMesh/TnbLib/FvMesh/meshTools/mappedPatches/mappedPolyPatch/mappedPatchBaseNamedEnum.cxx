#define FoamNamedEnum_EXPORT_DEFINE
#include <mappedPatchBase.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	template<>
	const char* tnbLib::NamedEnum
		<
		tnbLib::mappedPatchBase::sampleMode,
		6
		>::names[] =
	{
		"nearestCell",
		"nearestPatchFace",
		"nearestPatchFaceAMI",
		"nearestPatchPoint",
		"nearestFace",
		"nearestOnlyCell"
	};

	template<>
	const char* tnbLib::NamedEnum
		<
		tnbLib::mappedPatchBase::offsetMode,
		3
		>::names[] =
	{
		"uniform",
		"nonuniform",
		"normal"
	};
}