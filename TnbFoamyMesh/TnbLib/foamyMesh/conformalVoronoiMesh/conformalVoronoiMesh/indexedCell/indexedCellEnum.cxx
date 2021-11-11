#define FoamNamedEnum_EXPORT_DEFINE
#include <indexedCellEnum.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

template<>
const char*
tnbLib::NamedEnum<tnbLib::indexedCellEnum::cellTypes, 6>::names[] =
{
	"Unassigned",
	"Internal",
	"Surface",
	"FeatureEdge",
	"FeaturePoint",
	"Far"
};

const tnbLib::NamedEnum<tnbLib::indexedCellEnum::cellTypes, 6>
cellTypesNames_;


// ************************************************************************* //