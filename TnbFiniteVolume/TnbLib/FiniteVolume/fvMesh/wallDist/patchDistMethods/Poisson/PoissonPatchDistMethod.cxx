#include <PoissonPatchDistMethod.hxx>

#include <fvcGrad.hxx>
#include <fvmLaplacian.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace patchDistMethods
	{
		defineTypeNameAndDebug(Poisson, 0);
		addToRunTimeSelectionTable(patchDistMethod, Poisson, dictionary);
	}
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::patchDistMethods::Poisson::Poisson
(
	const dictionary& dict,
	const fvMesh& mesh,
	const labelHashSet& patchIDs
)
	:
	patchDistMethod(mesh, patchIDs)
{}


tnbLib::patchDistMethods::Poisson::Poisson
(
	const fvMesh& mesh,
	const labelHashSet& patchIDs
)
	:
	patchDistMethod(mesh, patchIDs)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::patchDistMethods::Poisson::correct(volScalarField& y)
{
	return correct(y, const_cast<volVectorField&>(volVectorField::null()));
}


bool tnbLib::patchDistMethods::Poisson::correct
(
	volScalarField& y,
	volVectorField& n
)
{
	if (!tyPsi_.valid())
	{
		tyPsi_ = tmp<volScalarField>
			(
				volScalarField::New
				(
					"yPsi",
					mesh_,
					dimensionedScalar(sqr(dimLength), 0),
					y.boundaryFieldRef().types()
				)
				);
	}
	volScalarField& yPsi = tyPsi_.ref();

	solve(fvm::laplacian(yPsi) == dimensionedScalar(dimless, -1.0));

	volVectorField gradyPsi(fvc::grad(yPsi));
	volScalarField magGradyPsi(mag(gradyPsi));

	y = sqrt(magSqr(gradyPsi) + 2 * yPsi) - magGradyPsi;

	// Cache yPsi if the mesh is moving otherwise delete
	if (!mesh_.changing())
	{
		tyPsi_.clear();
	}

	// Only calculate n if the field is defined
	if (notNull(n))
	{
		n =
			-gradyPsi
			/ max
			(
				magGradyPsi,
				dimensionedScalar(dimLength, small)
			);
	}

	return true;
}


// ************************************************************************* //