#define FoamRegisterDebugSwitch_EXPORT_DEFINE

#include <basicKinematicCollidingParcel.hxx>

#include <CloudTemplate.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTemplateTypeNameAndDebug(basicKinematicCollidingParcel, 0);
	defineTemplateTypeNameAndDebug(Cloud<basicKinematicCollidingParcel>, 0);
}


// ************************************************************************* //