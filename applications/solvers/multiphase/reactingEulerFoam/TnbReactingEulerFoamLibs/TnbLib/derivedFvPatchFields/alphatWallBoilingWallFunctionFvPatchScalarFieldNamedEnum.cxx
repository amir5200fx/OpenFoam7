
#define FoamNamedEnum_EXPORT_DEFINE

#include <alphatWallBoilingWallFunctionFvPatchScalarField.hxx>

using namespace tnbLib;

template<>
const char* tnbLib::NamedEnum
<
	tnbLib::compressible::
	alphatWallBoilingWallFunctionFvPatchScalarField::phaseType,
	2
>::names[] =
{
	"vapor",
	"liquid"
};

const tnbLib::NamedEnum
<
	tnbLib::compressible::
	alphatWallBoilingWallFunctionFvPatchScalarField::phaseType,
	2
>
tnbLib::compressible::
alphatWallBoilingWallFunctionFvPatchScalarField::phaseTypeNames_;