#define FoamRegisterDebugSwitch_EXPORT_DEFINE

#include <basicReactingMultiphaseParcel.hxx>

#include <CloudTemplate.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTemplateTypeNameAndDebug(basicReactingMultiphaseParcel, 0);
	defineTemplateTypeNameAndDebug(Cloud<basicReactingMultiphaseParcel>, 0);
}


// ************************************************************************* //