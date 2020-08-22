#include <points0MotionSolver.hxx>

#include <mapPolyMesh.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(points0MotionSolver, 0);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::points0MotionSolver::points0MotionSolver
(
	const polyMesh& mesh,
	const dictionary& dict,
	const word& type
)
	:
	motionSolver(mesh, dict, type),
	points0_(pointIOField(polyMesh::points0IO(mesh)))
{
	if (points0_.size() != mesh.nPoints())
	{
		FatalErrorInFunction
			<< "Number of points in mesh " << mesh.nPoints()
			<< " differs from number of points " << points0_.size()
			<< " read from file "
			<< typeFilePath<pointIOField>
			(
				IOobject
				(
					"points",
					mesh.time().constant(),
					polyMesh::meshSubDir,
					mesh,
					IOobject::MUST_READ,
					IOobject::NO_WRITE,
					false
				)
				)
			<< exit(FatalError);
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::points0MotionSolver::~points0MotionSolver()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::points0MotionSolver::movePoints(const pointField&)
{}


void tnbLib::points0MotionSolver::updateMesh(const mapPolyMesh& mpm)
{
	// pointMesh already updates pointFields

	motionSolver::updateMesh(mpm);

	// Map points0_. Bit special since we somehow have to come up with
	// a sensible points0 position for introduced points.
	// Find out scaling between points0 and current points

	// Get the new points either from the map or the mesh
	const pointField& points =
		(
			mpm.hasMotionPoints()
			? mpm.preMotionPoints()
			: mesh().points()
			);

	// Note: boundBox does reduce
	const vector span0 = boundBox(points0_).span();
	const vector span = boundBox(points).span();

	vector scaleFactors(cmptDivide(span0, span));

	pointField newPoints0(mpm.pointMap().size());

	forAll(newPoints0, pointi)
	{
		label oldPointi = mpm.pointMap()[pointi];

		if (oldPointi >= 0)
		{
			label masterPointi = mpm.reversePointMap()[oldPointi];

			if (masterPointi == pointi)
			{
				newPoints0[pointi] = points0_[oldPointi];
			}
			else
			{
				// New point - assume motion is scaling
				newPoints0[pointi] = points0_[oldPointi] + cmptMultiply
				(
					scaleFactors,
					points[pointi] - points[masterPointi]
				);
			}
		}
		else
		{
			FatalErrorInFunction
				<< "Cannot determine co-ordinates of introduced vertices."
				<< " New vertex " << pointi << " at co-ordinate "
				<< points[pointi] << exit(FatalError);
		}
	}

	twoDCorrectPoints(newPoints0);

	points0_.transfer(newPoints0);

	// points0 changed - set to write and check-in to database
	points0_.rename("points0");
	points0_.writeOpt() = IOobject::AUTO_WRITE;
	points0_.instance() = mesh().time().timeName();
	points0_.checkIn();
}


// ************************************************************************* //