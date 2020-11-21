#define FoamNamedEnum_EXPORT_DEFINE

#include <volFieldValue.hxx>

template<>
const char*
tnbLib::NamedEnum
<
	tnbLib::functionObjects::fieldValues::volFieldValue::operationType,
	13
>::names[] =
{
	"none",
	"sum",
	"weightedSum",
	"sumMag",
	"average",
	"weightedAverage",
	"volAverage",
	"weightedVolAverage",
	"volIntegrate",
	"weightedVolIntegrate",
	"min",
	"max",
	"CoV"
};

const tnbLib::NamedEnum
<
	tnbLib::functionObjects::fieldValues::volFieldValue::operationType,
	13
> tnbLib::functionObjects::fieldValues::volFieldValue::operationTypeNames_;