#include <solidParticleCloud.hxx>

#include <fvMesh.hxx>
#include <volFields.hxx>
#include <interpolationCellPoint.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::solidParticleCloud::solidParticleCloud
(
	const fvMesh& mesh,
	const word& cloudName,
	bool readFields
)
	:
	Cloud<solidParticle>(mesh, cloudName, false),
	mesh_(mesh),
	particleProperties_
	(
		IOobject
		(
			"particleProperties",
			mesh_.time().constant(),
			mesh_,
			IOobject::MUST_READ_IF_MODIFIED,
			IOobject::NO_WRITE
		)
	),
	rhop_(dimensionedScalar(particleProperties_.lookup("rhop")).value()),
	e_(dimensionedScalar(particleProperties_.lookup("e")).value()),
	mu_(dimensionedScalar(particleProperties_.lookup("mu")).value())
{
	if (readFields)
	{
		solidParticle::readFields(*this);
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::solidParticleCloud::move(const dimensionedVector& g)
{
	const volScalarField& rho = mesh_.lookupObject<const volScalarField>("rho");
	const volVectorField& U = mesh_.lookupObject<const volVectorField>("U");
	const volScalarField& nu = mesh_.lookupObject<const volScalarField>("nu");

	interpolationCellPoint<scalar> rhoInterp(rho);
	interpolationCellPoint<vector> UInterp(U);
	interpolationCellPoint<scalar> nuInterp(nu);

	solidParticle::trackingData
		td(*this, rhoInterp, UInterp, nuInterp, g.value());

	Cloud<solidParticle>::move(*this, td, mesh_.time().deltaTValue());
}


// ************************************************************************* //