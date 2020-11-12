#define FoamRegisterDebugSwitch_EXPORT_DEFINE

#include <basicThermoParcel.hxx>

#include <CloudTemplate.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTemplateTypeNameAndDebug(basicThermoParcel, 0);
	defineTemplateTypeNameAndDebug(Cloud<basicThermoParcel>, 0);
}

// ************************************************************************* //