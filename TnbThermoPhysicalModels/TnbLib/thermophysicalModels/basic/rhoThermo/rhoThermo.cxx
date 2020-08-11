#include <rhoThermo.hxx>

#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(rhoThermo, 0);
	defineRunTimeSelectionTable(rhoThermo, fvMesh);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::rhoThermo::rhoThermo(const fvMesh& mesh, const word& phaseName)
	:
	fluidThermo(mesh, phaseName),
	rho_
	(
		IOobject
		(
			phasePropertyName("thermo:rho"),
			mesh.time().timeName(),
			mesh,
			IOobject::NO_READ,
			IOobject::NO_WRITE
		),
		mesh,
		dimDensity
	),

	psi_
	(
		IOobject
		(
			phasePropertyName("thermo:psi"),
			mesh.time().timeName(),
			mesh,
			IOobject::NO_READ,
			IOobject::NO_WRITE
		),
		mesh,
		dimensionSet(0, -2, 2, 0, 0)
	),

	mu_
	(
		IOobject
		(
			phasePropertyName("thermo:mu"),
			mesh.time().timeName(),
			mesh,
			IOobject::NO_READ,
			IOobject::NO_WRITE
		),
		mesh,
		dimensionSet(1, -1, -1, 0, 0)
	)
{}


tnbLib::rhoThermo::rhoThermo
(
	const fvMesh& mesh,
	const dictionary& dict,
	const word& phaseName
)
	:
	fluidThermo(mesh, dict, phaseName),
	rho_
	(
		IOobject
		(
			phasePropertyName("thermo:rho"),
			mesh.time().timeName(),
			mesh,
			IOobject::NO_READ,
			IOobject::NO_WRITE
		),
		mesh,
		dimDensity
	),

	psi_
	(
		IOobject
		(
			phasePropertyName("thermo:psi"),
			mesh.time().timeName(),
			mesh,
			IOobject::NO_READ,
			IOobject::NO_WRITE
		),
		mesh,
		dimensionSet(0, -2, 2, 0, 0)
	),

	mu_
	(
		IOobject
		(
			phasePropertyName("thermo:mu"),
			mesh.time().timeName(),
			mesh,
			IOobject::NO_READ,
			IOobject::NO_WRITE
		),
		mesh,
		dimensionSet(1, -1, -1, 0, 0)
	)
{}


// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::rhoThermo> tnbLib::rhoThermo::New
(
	const fvMesh& mesh,
	const word& phaseName
)
{
	return basicThermo::New<rhoThermo>(mesh, phaseName);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::rhoThermo::~rhoThermo()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField> tnbLib::rhoThermo::rho() const
{
	return rho_;
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::rhoThermo::rho(const label patchi) const
{
	return rho_.boundaryField()[patchi];
}


tnbLib::volScalarField& tnbLib::rhoThermo::rho()
{
	return rho_;
}


void tnbLib::rhoThermo::correctRho(const tnbLib::volScalarField& deltaRho)
{
	rho_ += deltaRho;
}


const tnbLib::volScalarField& tnbLib::rhoThermo::psi() const
{
	return psi_;
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::rhoThermo::mu() const
{
	return mu_;
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::rhoThermo::mu(const label patchi) const
{
	return mu_.boundaryField()[patchi];
}


// ************************************************************************* //