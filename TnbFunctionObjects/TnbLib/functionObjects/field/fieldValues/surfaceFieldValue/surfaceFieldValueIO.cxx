#define FoamNamedEnum_EXPORT_DEFINE

#include <surfaceFieldValue.hxx>

template<>
const char* tnbLib::NamedEnum
<
	tnbLib::functionObjects::fieldValues::surfaceFieldValue::regionTypes,
	3
>::names[] =
{
	"faceZone",
	"patch",
	"sampledSurface"
};

template<>
const char* tnbLib::NamedEnum
<
	tnbLib::functionObjects::fieldValues::surfaceFieldValue::operationType,
	17
>::names[] =
{
	"none",
	"sum",
	"weightedSum",
	"sumMag",
	"sumDirection",
	"sumDirectionBalance",
	"average",
	"weightedAverage",
	"areaAverage",
	"weightedAreaAverage",
	"areaIntegrate",
	"weightedAreaIntegrate",
	"min",
	"max",
	"CoV",
	"areaNormalAverage",
	"areaNormalIntegrate"
};

const tnbLib::NamedEnum
<
	tnbLib::functionObjects::fieldValues::surfaceFieldValue::regionTypes,
	3
> tnbLib::functionObjects::fieldValues::surfaceFieldValue::regionTypeNames_;

const tnbLib::NamedEnum
<
	tnbLib::functionObjects::fieldValues::surfaceFieldValue::operationType,
	17
> tnbLib::functionObjects::fieldValues::surfaceFieldValue::operationTypeNames_;