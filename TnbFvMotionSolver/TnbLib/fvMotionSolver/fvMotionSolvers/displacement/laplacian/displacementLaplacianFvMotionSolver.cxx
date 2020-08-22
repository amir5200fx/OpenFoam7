#include <displacementLaplacianFvMotionSolver.hxx>

#include <motionDiffusivity.hxx>
#include <fvmLaplacian.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <OFstream.hxx>
#include <meshTools.hxx>
#include <mapPolyMesh.hxx>
#include <volPointInterpolation.hxx>

#include <fvBoundaryMesh.hxx>  // added by amir
#include <volMesh.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(displacementLaplacianFvMotionSolver, 0);

	addToRunTimeSelectionTable
	(
		motionSolver,
		displacementLaplacianFvMotionSolver,
		dictionary
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::displacementLaplacianFvMotionSolver::displacementLaplacianFvMotionSolver
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
			pointDisplacement_.dimensions(),
			Zero
		),
		cellMotionBoundaryTypes<vector>(pointDisplacement_.boundaryField())
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
	IOobject io
	(
		"pointLocation",
		fvMesh_.time().timeName(),
		fvMesh_,
		IOobject::MUST_READ,
		IOobject::AUTO_WRITE
	);

	if (debug)
	{
		Info << "displacementLaplacianFvMotionSolver:" << nl
			<< "    diffusivity       : " << diffusivityPtr_().type() << nl
			<< "    frozenPoints zone : " << frozenPointsZone_ << endl;
	}


	if (io.typeHeaderOk<pointVectorField>(true))
	{
		pointLocation_.reset
		(
			new pointVectorField
			(
				io,
				pointMesh::New(fvMesh_)
			)
		);

		if (debug)
		{
			Info << "displacementLaplacianFvMotionSolver :"
				<< " Read pointVectorField "
				<< io.name()
				<< " to be used for boundary conditions on points."
				<< nl
				<< "Boundary conditions:"
				<< pointLocation_().boundaryField().types() << endl;
		}
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::displacementLaplacianFvMotionSolver::
~displacementLaplacianFvMotionSolver()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::motionDiffusivity&
tnbLib::displacementLaplacianFvMotionSolver::diffusivity()
{
	if (!diffusivityPtr_.valid())
	{
		diffusivityPtr_ = motionDiffusivity::New
		(
			fvMesh_,
			coeffDict().lookup("diffusivity")
		);
	}
	return diffusivityPtr_();
}


tnbLib::tmp<tnbLib::pointField>
tnbLib::displacementLaplacianFvMotionSolver::curPoints() const
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
			Info << "displacementLaplacianFvMotionSolver : applying "
				<< " boundary conditions on " << pointLocation_().name()
				<< " to new point location."
				<< endl;
		}

		pointLocation_().primitiveFieldRef() =
			points0()
			+ pointDisplacement_.primitiveField();

		pointLocation_().correctBoundaryConditions();

		// Implement frozen points
		if (frozenPointsZone_ != -1)
		{
			const pointZone& pz = fvMesh_.pointZones()[frozenPointsZone_];

			forAll(pz, i)
			{
				pointLocation_()[pz[i]] = points0()[pz[i]];
			}
		}

		twoDCorrectPoints(pointLocation_().primitiveFieldRef());

		return tmp<pointField>(pointLocation_().primitiveField());
	}
	else
	{
		tmp<pointField> tcurPoints
		(
			points0() + pointDisplacement_.primitiveField()
		);
		pointField& curPoints = tcurPoints.ref();

		// Implement frozen points
		if (frozenPointsZone_ != -1)
		{
			const pointZone& pz = fvMesh_.pointZones()[frozenPointsZone_];

			forAll(pz, i)
			{
				curPoints[pz[i]] = points0()[pz[i]];
			}
		}

		twoDCorrectPoints(curPoints);

		return tcurPoints;
	}
}


void tnbLib::displacementLaplacianFvMotionSolver::solve()
{
	// The points have moved so before interpolation update
	// the motionSolver accordingly
	movePoints(fvMesh_.points());

	diffusivity().correct();
	pointDisplacement_.boundaryFieldRef().updateCoeffs();

	tnbLib::solve
	(
		fvm::laplacian
		(
			diffusivity().operator()(),
			cellDisplacement_,
			"laplacian(diffusivity,cellDisplacement)"
		)
	);
}


void tnbLib::displacementLaplacianFvMotionSolver::updateMesh
(
	const mapPolyMesh& mpm
)
{
	displacementMotionSolver::updateMesh(mpm);

	// Update diffusivity. Note two stage to make sure old one is de-registered
	// before creating/registering new one.
	diffusivityPtr_.clear();
}


// ************************************************************************* //