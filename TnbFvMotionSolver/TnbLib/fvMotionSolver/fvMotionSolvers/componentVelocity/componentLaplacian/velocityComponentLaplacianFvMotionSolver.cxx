#include <velocityComponentLaplacianFvMotionSolver.hxx>

#include <motionDiffusivity.hxx>
#include <fvmLaplacian.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <volPointInterpolation.hxx>

#include <fvBoundaryMesh.hxx>  // added by amir
#include <volMesh.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(velocityComponentLaplacianFvMotionSolver, 0);

	addToRunTimeSelectionTable
	(
		motionSolver,
		velocityComponentLaplacianFvMotionSolver,
		dictionary
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::velocityComponentLaplacianFvMotionSolver::
velocityComponentLaplacianFvMotionSolver
(
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	componentVelocityMotionSolver(mesh, dict, typeName),
	fvMotionSolver(mesh),
	cellMotionU_
	(
		IOobject
		(
			"cellMotionU" + cmptName_,
			mesh.time().timeName(),
			mesh,
			IOobject::READ_IF_PRESENT,
			IOobject::AUTO_WRITE
		),
		fvMesh_,
		dimensionedScalar(pointMotionU_.dimensions(), 0),
		cellMotionBoundaryTypes<scalar>(pointMotionU_.boundaryField())
	),
	diffusivityPtr_
	(
		motionDiffusivity::New(fvMesh_, coeffDict().lookup("diffusivity"))
	)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::velocityComponentLaplacianFvMotionSolver::
~velocityComponentLaplacianFvMotionSolver()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::pointField>
tnbLib::velocityComponentLaplacianFvMotionSolver::curPoints() const
{
	volPointInterpolation::New(fvMesh_).interpolate
	(
		cellMotionU_,
		pointMotionU_
	);

	tmp<pointField> tcurPoints(new pointField(fvMesh_.points()));

	tcurPoints.ref().replace
	(
		cmpt_,
		tcurPoints().component(cmpt_)
		+ fvMesh_.time().deltaTValue()*pointMotionU_.primitiveField()
	);

	twoDCorrectPoints(tcurPoints.ref());

	return tcurPoints;
}


void tnbLib::velocityComponentLaplacianFvMotionSolver::solve()
{
	// The points have moved so before interpolation update
	// the fvMotionSolver accordingly
	movePoints(fvMesh_.points());

	diffusivityPtr_->correct();
	pointMotionU_.boundaryFieldRef().updateCoeffs();

	tnbLib::solve
	(
		fvm::laplacian
		(
			diffusivityPtr_->operator()(),
			cellMotionU_,
			"laplacian(diffusivity,cellMotionU)"
		)
	);
}


void tnbLib::velocityComponentLaplacianFvMotionSolver::updateMesh
(
	const mapPolyMesh& mpm
)
{
	componentVelocityMotionSolver::updateMesh(mpm);

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