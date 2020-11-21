#define FoamRegisterDebugSwitch_EXPORT_DEFINE

#include <dsmcParcel.hxx>

#include <DSMCCloudTemplate.hxx>
#include <MaxwellianThermal.hxx>
#include <SpecularReflection.hxx>
#include <MixedDiffuseSpecular.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	typedef DSMCCloud<dsmcParcel> CloudType;

	makeWallInteractionModel(CloudType);

	// Add instances of wall interaction model to the table
	makeWallInteractionModelType(MaxwellianThermal, CloudType);
	makeWallInteractionModelType(SpecularReflection, CloudType);
	makeWallInteractionModelType(MixedDiffuseSpecular, CloudType);
}


// ************************************************************************* //