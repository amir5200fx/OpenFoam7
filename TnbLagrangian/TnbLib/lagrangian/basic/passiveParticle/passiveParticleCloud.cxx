#include <passiveParticleCloud.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTemplateTypeNameAndDebug(Cloud<passiveParticle>, 0);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::passiveParticleCloud::passiveParticleCloud
(
	const polyMesh& mesh,
	const word& cloudName,
	bool readFields
)
	:
	Cloud<passiveParticle>(mesh, cloudName, false)
{
	if (readFields)
	{
		passiveParticle::readFields(*this);
	}
}


tnbLib::passiveParticleCloud::passiveParticleCloud
(
	const polyMesh& mesh,
	const word& cloudName,
	const IDLList<passiveParticle>& particles
)
	:
	Cloud<passiveParticle>(mesh, cloudName, particles)
{}


// ************************************************************************* //