#define FoamRegisterDebugSwitch_EXPORT_DEFINE

#include <indexedParticleCloud.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTemplateTypeNameAndDebug(Cloud<indexedParticle>, 0);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::indexedParticleCloud::indexedParticleCloud
(
	const polyMesh& mesh,
	const word& cloudName,
	bool readFields
)
	:
	Cloud<indexedParticle>(mesh, cloudName, false)
{
	if (readFields)
	{
		indexedParticle::readFields(*this);
	}
}


// ************************************************************************* //