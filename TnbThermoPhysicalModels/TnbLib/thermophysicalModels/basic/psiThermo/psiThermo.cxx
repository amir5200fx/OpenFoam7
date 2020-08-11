#include <psiThermo.hxx>

#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(psiThermo, 0);
	defineRunTimeSelectionTable(psiThermo, fvMesh);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::psiThermo::psiThermo(const fvMesh& mesh, const word& phaseName)
	:
	fluidThermo(mesh, phaseName),

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

tnbLib::autoPtr<tnbLib::psiThermo> tnbLib::psiThermo::New
(
	const fvMesh& mesh,
	const word& phaseName
)
{
	return basicThermo::New<psiThermo>(mesh, phaseName);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::psiThermo::~psiThermo()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField> tnbLib::psiThermo::rho() const
{
	return p_ * psi_;
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::psiThermo::rho(const label patchi) const
{
	return p_.boundaryField()[patchi] * psi_.boundaryField()[patchi];
}


void tnbLib::psiThermo::correctRho(const tnbLib::volScalarField& deltaRho)
{}


const tnbLib::volScalarField& tnbLib::psiThermo::psi() const
{
	return psi_;
}


tnbLib::tmp<tnbLib::volScalarField> tnbLib::psiThermo::mu() const
{
	return mu_;
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::psiThermo::mu(const label patchi) const
{
	return mu_.boundaryField()[patchi];
}


// ************************************************************************* //