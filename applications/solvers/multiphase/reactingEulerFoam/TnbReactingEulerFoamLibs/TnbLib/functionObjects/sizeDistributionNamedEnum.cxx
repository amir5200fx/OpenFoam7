


#include <sizeDistribution.hxx>

template<>
const char*
tnbLib::NamedEnum
<
	tnbLib::functionObjects::sizeDistribution::selectionModeTypes,
	2
>::names[] = { "cellZone", "all" };

template<>
const char*
tnbLib::NamedEnum
<
	tnbLib::functionObjects::sizeDistribution::functionTypes,
	4
>::names[] =
{
	"numberDensity",
	"volumeDensity",
	"numberConcentration",
	"moments"
};

template<>
const char*
tnbLib::NamedEnum
<
	tnbLib::functionObjects::sizeDistribution::abszissaTypes,
	2
>::names[] = { "diameter", "volume" };

const tnbLib::NamedEnum
<
	tnbLib::functionObjects::sizeDistribution::selectionModeTypes,
	2
> tnbLib::functionObjects::sizeDistribution::selectionModeTypeNames_;

const tnbLib::NamedEnum
<
	tnbLib::functionObjects::sizeDistribution::functionTypes,
	4
> tnbLib::functionObjects::sizeDistribution::functionTypeNames_;

const tnbLib::NamedEnum
<
	tnbLib::functionObjects::sizeDistribution::abszissaTypes,
	2
> tnbLib::functionObjects::sizeDistribution::abszissaTypeNames_;