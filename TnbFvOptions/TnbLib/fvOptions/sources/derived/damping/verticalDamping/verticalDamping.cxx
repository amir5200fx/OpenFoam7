#include <verticalDamping.hxx>

#include <fvMatrix.hxx>
#include <uniformDimensionedFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fv
	{
		defineTypeNameAndDebug(verticalDamping, 0);
		addToRunTimeSelectionTable(option, verticalDamping, dictionary);
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::fv::verticalDamping::add
(
	const volVectorField& alphaRhoU,
	fvMatrix<vector>& eqn
)
{
	const uniformDimensionedVectorField& g =
		mesh_.lookupObject<uniformDimensionedVectorField>("g");

	const dimensionedSymmTensor gg(sqr(g) / magSqr(g));

	eqn -= forceCoeff()*(gg & alphaRhoU());
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fv::verticalDamping::verticalDamping
(
	const word& name,
	const word& modelType,
	const dictionary& dict,
	const fvMesh& mesh
)
	:
	damping(name, modelType, dict, mesh)
{
	read(dict);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::fv::verticalDamping::addSup
(
	fvMatrix<vector>& eqn,
	const label fieldi
)
{
	add(eqn.psi(), eqn);
}


void tnbLib::fv::verticalDamping::addSup
(
	const volScalarField& rho,
	fvMatrix<vector>& eqn,
	const label fieldi
)
{
	add(rho*eqn.psi(), eqn);
}


void tnbLib::fv::verticalDamping::addSup
(
	const volScalarField& alpha,
	const volScalarField& rho,
	fvMatrix<vector>& eqn,
	const label fieldi
)
{
	add(alpha*rho*eqn.psi(), eqn);
}


// ************************************************************************* //