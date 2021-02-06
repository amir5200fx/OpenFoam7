#define FoamNamedEnum_EXPORT_DEFINE
#include <EDC.hxx>

// * * * * * * * * * * * * * Static Member Data  * * * * * * * * * * * * * * //

template<>
const char* tnbLib::NamedEnum
<
	tnbLib::combustionModels::EDCversions,
	4
>::names[] =
{
	"v1981",
	"v1996",
	"v2005",
	"v2016"
};

const tnbLib::NamedEnum<tnbLib::combustionModels::EDCversions, 4>
tnbLib::combustionModels::EDCversionNames;

const tnbLib::combustionModels::EDCversions
tnbLib::combustionModels::EDCdefaultVersion
(
	tnbLib::combustionModels::EDCversions::v2005
);