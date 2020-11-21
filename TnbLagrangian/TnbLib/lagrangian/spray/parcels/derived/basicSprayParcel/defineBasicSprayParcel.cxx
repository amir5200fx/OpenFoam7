#define FoamRegisterDebugSwitch_EXPORT_DEFINE

#include <basicSprayParcel.hxx>
#include <CloudTemplate.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTemplateTypeNameAndDebug(basicSprayParcel, 0);
	defineTemplateTypeNameAndDebug(Cloud<basicSprayParcel>, 0);
};


// ************************************************************************* //