#include <velocityLaplacianFvMotionSolver.hxx>

#include <motionDiffusivity.hxx>
#include <fvmLaplacian.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <volPointInterpolation.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(velocityLaplacianFvMotionSolver, 0);

	addToRunTimeSelectionTable
	(
		motionSolver,
		velocityLaplacianFvMotionSolver,
		dictionary
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::velocityLaplacianFvMotionSolver::velocityLaplacianFvMotionSolver
(
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	velocityMotionSolver(mesh, dict, typeName),
	fvMotionSolver(mesh),
	cellMotionU_
	(
		IOobject
		(
			"cellMotionU",
			mesh.time().timeName(),
			mesh,
			IOobject::READ_IF_PRESENT,
			IOobject::AUTO_WRITE
		),
		fvMesh_,
		dimensionedVector
		(
			"cellMotionU",
			pointMotionU_.dimensions(),
			Zero
		),
		cellMotionBoundaryTypes<vector>(pointMotionU_.boundaryField())
	),
	diffusivityPtr_
	(
		motionDiffusivity::New(fvMesh_, coeffDict().lookup("diffusivity"))
	)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::velocityLaplacianFvMotionSolver::~velocityLaplacianFvMotionSolver()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::pointField>
tnbLib::velocityLaplacianFvMotionSolver::curPoints() const
{
	volPointInterpolation::New(fvMesh_).interpolate
	(
		cellMotionU_,
		pointMotionU_
	);

	tmp<pointField> tcurPoints
	(
		fvMesh_.points()
		+ fvMesh_.time().deltaTValue()*pointMotionU_.primitiveField()
	);

	twoDCorrectPoints(tcurPoints.ref());

	return tcurPoints;
}


void tnbLib::velocityLaplacianFvMotionSolver::solve()
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


//void tnbLib::velocityLaplacianFvMotionSolver::movePoints(const pointField& p)
//{
//    // Movement of pointMesh and volPointInterpolation already
//    // done by polyMesh,fvMesh
//}


void tnbLib::velocityLaplacianFvMotionSolver::updateMesh
(
	const mapPolyMesh& mpm
)
{
	velocityMotionSolver::updateMesh(mpm);

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