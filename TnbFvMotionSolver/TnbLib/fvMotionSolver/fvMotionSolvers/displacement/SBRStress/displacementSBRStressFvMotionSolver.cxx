#include <displacementSBRStressFvMotionSolver.hxx>

#include <motionDiffusivity.hxx>
#include <fvmLaplacian.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <fvcDiv.hxx>
#include <fvcGrad.hxx>
#include <surfaceInterpolate.hxx>
#include <fvcLaplacian.hxx>
#include <mapPolyMesh.hxx>
#include <volPointInterpolation.hxx>


// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(displacementSBRStressFvMotionSolver, 0);

	addToRunTimeSelectionTable
	(
		motionSolver,
		displacementSBRStressFvMotionSolver,
		dictionary
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::displacementSBRStressFvMotionSolver::displacementSBRStressFvMotionSolver
(
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	displacementMotionSolver(mesh, dict, typeName),
	fvMotionSolver(mesh),
	cellDisplacement_
	(
		IOobject
		(
			"cellDisplacement",
			mesh.time().timeName(),
			mesh,
			IOobject::READ_IF_PRESENT,
			IOobject::AUTO_WRITE
		),
		fvMesh_,
		dimensionedVector
		(
			"cellDisplacement",
			pointDisplacement().dimensions(),
			Zero
		),
		cellMotionBoundaryTypes<vector>(pointDisplacement().boundaryField())
	),
	diffusivityPtr_
	(
		motionDiffusivity::New(fvMesh_, coeffDict().lookup("diffusivity"))
	)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::displacementSBRStressFvMotionSolver::
~displacementSBRStressFvMotionSolver()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::pointField>
tnbLib::displacementSBRStressFvMotionSolver::curPoints() const
{
	volPointInterpolation::New(fvMesh_).interpolate
	(
		cellDisplacement_,
		pointDisplacement_
	);

	tmp<pointField> tcurPoints
	(
		points0() + pointDisplacement().primitiveField()
	);

	twoDCorrectPoints(tcurPoints.ref());

	return tcurPoints;
}


void tnbLib::displacementSBRStressFvMotionSolver::solve()
{
	// The points have moved so before interpolation update
	// the mtionSolver accordingly
	movePoints(fvMesh_.points());

	diffusivityPtr_->correct();
	pointDisplacement_.boundaryFieldRef().updateCoeffs();

	surfaceScalarField Df(diffusivityPtr_->operator()());

	volTensorField gradCd("gradCd", fvc::grad(cellDisplacement_));

	tnbLib::solve
	(
		fvm::laplacian
		(
			2 * Df,
			cellDisplacement_,
			"laplacian(diffusivity,cellDisplacement)"
		)

		+ fvc::div
		(
			Df
			*(
				fvc::dotInterpolate
				(
					cellDisplacement_.mesh().Sf(),
					gradCd.T() - gradCd
				)

				// Solid-body rotation "lambda" term
				- cellDisplacement_.mesh().Sf()*fvc::interpolate(tr(gradCd))
				)
		)

		/*
	  - fvc::laplacian
		(
			2*Df,
			cellDisplacement_,
			"laplacian(diffusivity,cellDisplacement)"
		)

	  + fvc::div
		(
			Df
		   *(
			   fvc::dotInterpolate
			   (
				   cellDisplacement_.mesh().Sf(),
				   gradCd + gradCd.T()
			   )

			   // Solid-body rotation "lambda" term
			 - cellDisplacement_.mesh().Sf()*fvc::interpolate(tr(gradCd))
		   )
		)
		*/
	);
}


void tnbLib::displacementSBRStressFvMotionSolver::updateMesh
(
	const mapPolyMesh& mpm
)
{
	displacementMotionSolver::updateMesh(mpm);

	// Update diffusivity. Note two stage to make sure old one is de-registered
	// before creating/registering new one.
	diffusivityPtr_.reset(nullptr);
	diffusivityPtr_ = motionDiffusivity::New
	(
		fvMesh_,
		coeffDict().lookup("diffusivity")
	);
}


// ************************************************************************* //