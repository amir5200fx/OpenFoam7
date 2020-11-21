#define FoamNamedEnum_EXPORT_DEFINE
#define FoamCloud_EXPORT_DEFINE
#define FoamRegisterDebugSwitch_EXPORT_DEFINE

#include <trackedParticle.hxx>

#include <CloudTemplate.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

	//defineParticleTypeNameAndDebug(trackedParticle, 0);
	defineTemplateTypeNameAndDebug(Cloud<trackedParticle>, 0);

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //