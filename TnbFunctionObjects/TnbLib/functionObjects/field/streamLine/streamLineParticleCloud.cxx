#include <streamLineParticleCloud.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTemplateTypeNameAndDebug(Cloud<streamLineParticle>, 0);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::streamLineParticleCloud::streamLineParticleCloud
(
	const polyMesh& mesh,
	const word& cloudName,
	bool readFields
)
	:
	Cloud<streamLineParticle>(mesh, cloudName, false)
{
	if (readFields)
	{
		streamLineParticle::readFields(*this);
	}
}


tnbLib::streamLineParticleCloud::streamLineParticleCloud
(
	const polyMesh& mesh,
	const word& cloudName,
	const IDLList<streamLineParticle>& particles
)
	:
	Cloud<streamLineParticle>(mesh, cloudName, particles)
{}


// ************************************************************************* //