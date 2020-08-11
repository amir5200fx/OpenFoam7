#include <solidThermo.hxx>

#include <fvMesh.hxx>

#include <Time.hxx>  // added by amir

/* * * * * * * * * * * * * * * private static data * * * * * * * * * * * * * */

namespace tnbLib
{
	defineTypeNameAndDebug(solidThermo, 0);
	defineRunTimeSelectionTable(solidThermo, fvMesh);
	defineRunTimeSelectionTable(solidThermo, dictionary);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::solidThermo::solidThermo
(
	const fvMesh& mesh,
	const word& phaseName
)
	:
	basicThermo(mesh, phaseName),
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
	)
{}


tnbLib::solidThermo::solidThermo
(
	const fvMesh& mesh,
	const dictionary& dict,
	const word& phaseName
)
	:
	basicThermo(mesh, dict, phaseName),
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
	)
{}


// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::solidThermo> tnbLib::solidThermo::New
(
	const fvMesh& mesh,
	const word& phaseName
)
{
	return basicThermo::New<solidThermo>(mesh, phaseName);
}


tnbLib::autoPtr<tnbLib::solidThermo> tnbLib::solidThermo::New
(
	const fvMesh& mesh,
	const dictionary& dict,
	const word& phaseName
)
{
	return basicThermo::New<solidThermo>(mesh, dict, phaseName);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::solidThermo::~solidThermo()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField> tnbLib::solidThermo::rho() const
{
	return rho_;
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::solidThermo::rho(const label patchi) const
{
	return rho_.boundaryField()[patchi];
}


tnbLib::volScalarField& tnbLib::solidThermo::rho()
{
	return rho_;
}


bool tnbLib::solidThermo::read()
{
	return regIOobject::read();
}


// ************************************************************************* //