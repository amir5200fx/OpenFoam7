#define FoamRegisterDebugSwitch_EXPORT_DEFINE

#include <basicKinematicParcel.hxx>

#include <CloudTemplate.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTemplateTypeNameAndDebug(basicKinematicParcel, 0);
	defineTemplateTypeNameAndDebug(Cloud<basicKinematicParcel>, 0);
}


// ************************************************************************* //