#define FoamRegisterDebugSwitch_EXPORT_DEFINE

#include <basicReactingParcel.hxx>

#include <CloudTemplate.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTemplateTypeNameAndDebug(basicReactingParcel, 0);
	defineTemplateTypeNameAndDebug(Cloud<basicReactingParcel>, 0);
}


// ************************************************************************* //