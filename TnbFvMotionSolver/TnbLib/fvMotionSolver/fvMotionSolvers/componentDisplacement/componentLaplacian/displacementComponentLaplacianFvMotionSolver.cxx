#include <displacementComponentLaplacianFvMotionSolver.hxx>

#include <motionDiffusivity.hxx>
#include <fvmLaplacian.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <mapPolyMesh.hxx>
#include <volPointInterpolation.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(displacementComponentLaplacianFvMotionSolver, 0);

	addToRunTimeSelectionTable
	(
		motionSolver,
		displacementComponentLaplacianFvMotionSolver,
		dictionary
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::displacementComponentLaplacianFvMotionSolver::
displacementComponentLaplacianFvMotionSolver
(
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	componentDisplacementMotionSolver(mesh, dict, type()),
	fvMotionSolver(mesh),
	cellDisplacement_
	(
		IOobject
		(
			"cellDisplacement" + cmptName_,
			mesh.time().timeName(),
			mesh,
			IOobject::READ_IF_PRESENT,
			IOobject::AUTO_WRITE
		),
		fvMesh_,
		dimensionedScalar(pointDisplacement_.dimensions(), 0),
		cellMotionBoundaryTypes<scalar>(pointDisplacement_.boundaryField())
	),
	pointLocation_(nullptr),
	diffusivityPtr_
	(
		motionDiffusivity::New(fvMesh_, coeffDict().lookup("diffusivity"))
	),
	frozenPointsZone_
	(
		coeffDict().found("frozenPointsZone")
		? fvMesh_.pointZones().findZoneID(coeffDict().lookup("frozenPointsZone"))
		: -1
	)
{
	Switch applyPointLocation
	(
		coeffDict().lookupOrDefault
		(
			"applyPointLocation",
			true
		)
	);

	if (applyPointLocation)
	{
		pointLocation_.reset
		(
			new pointVectorField
			(
				IOobject
				(
					"pointLocation",
					fvMesh_.time().timeName(),
					fvMesh_,
					IOobject::MUST_READ,
					IOobject::AUTO_WRITE
				),
				pointMesh::New(fvMesh_)
			)
		);

		// if (debug)
		{
			Info << "displacementComponentLaplacianFvMotionSolver :"
				<< " Read pointVectorField "
				<< pointLocation_().name()
				<< " to be used for boundary conditions on points."
				<< nl
				<< "Boundary conditions:"
				<< pointLocation_().boundaryField().types() << endl;
		}
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::displacementComponentLaplacianFvMotionSolver::
~displacementComponentLaplacianFvMotionSolver()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::pointField>
tnbLib::displacementComponentLaplacianFvMotionSolver::curPoints() const
{
	volPointInterpolation::New(fvMesh_).interpolate
	(
		cellDisplacement_,
		pointDisplacement_
	);

	if (pointLocation_.valid())
	{
		if (debug)
		{
			Info << "displacementComponentLaplacianFvMotionSolver : applying "
				<< " boundary conditions on " << pointLocation_().name()
				<< " to new point location."
				<< endl;
		}

		// Apply pointLocation_ b.c. to mesh points.

		pointLocation_().primitiveFieldRef() = fvMesh_.points();

		pointLocation_().primitiveFieldRef().replace
		(
			cmpt_,
			points0_ + pointDisplacement_.primitiveField()
		);

		pointLocation_().correctBoundaryConditions();

		// Implement frozen points
		if (frozenPointsZone_ != -1)
		{
			const pointZone& pz = fvMesh_.pointZones()[frozenPointsZone_];

			forAll(pz, i)
			{
				label pointi = pz[i];

				pointLocation_()[pointi][cmpt_] = points0_[pointi];
			}
		}

		twoDCorrectPoints(pointLocation_().primitiveFieldRef());

		return tmp<pointField>(pointLocation_().primitiveField());
	}
	else
	{
		tmp<pointField> tcurPoints(new pointField(fvMesh_.points()));
		pointField& curPoints = tcurPoints.ref();

		curPoints.replace
		(
			cmpt_,
			points0_ + pointDisplacement_.primitiveField()
		);

		// Implement frozen points
		if (frozenPointsZone_ != -1)
		{
			const pointZone& pz = fvMesh_.pointZones()[frozenPointsZone_];

			forAll(pz, i)
			{
				label pointi = pz[i];

				curPoints[pointi][cmpt_] = points0_[pointi];
			}
		}

		twoDCorrectPoints(curPoints);

		return tcurPoints;
	}
}


void tnbLib::displacementComponentLaplacianFvMotionSolver::solve()
{
	// The points have moved so before interpolation update
	// the motionSolver accordingly
	movePoints(fvMesh_.points());

	diffusivityPtr_->correct();
	pointDisplacement_.boundaryFieldRef().updateCoeffs();

	tnbLib::solve
	(
		fvm::laplacian
		(
			diffusivityPtr_->operator()(),
			cellDisplacement_,
			"laplacian(diffusivity,cellDisplacement)"
		)
	);
}


void tnbLib::displacementComponentLaplacianFvMotionSolver::updateMesh
(
	const mapPolyMesh& mpm
)
{
	componentDisplacementMotionSolver::updateMesh(mpm);

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