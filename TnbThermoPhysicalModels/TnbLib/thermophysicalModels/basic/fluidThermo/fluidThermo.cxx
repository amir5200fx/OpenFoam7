#include <fluidThermo.hxx>

/* * * * * * * * * * * * * * * private static data * * * * * * * * * * * * * */

namespace tnbLib
{
	defineTypeNameAndDebug(fluidThermo, 0);
	defineRunTimeSelectionTable(fluidThermo, fvMesh);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fluidThermo::fluidThermo(const fvMesh& mesh, const word& phaseName)
	:
	basicThermo(mesh, phaseName)
{}



tnbLib::fluidThermo::fluidThermo
(
	const fvMesh& mesh,
	const dictionary& dict,
	const word& phaseName
)
	:
	basicThermo(mesh, dict, phaseName)
{}


// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::fluidThermo> tnbLib::fluidThermo::New
(
	const fvMesh& mesh,
	const word& phaseName
)
{
	return basicThermo::New<fluidThermo>(mesh, phaseName);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::fluidThermo::~fluidThermo()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::volScalarField> tnbLib::fluidThermo::nu() const
{
	return mu() / rho();
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::fluidThermo::nu(const label patchi) const
{
	return mu(patchi) / rho(patchi);
}


// ************************************************************************* //