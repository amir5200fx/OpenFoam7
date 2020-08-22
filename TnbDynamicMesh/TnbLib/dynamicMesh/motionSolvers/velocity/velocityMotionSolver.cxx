#include <velocityMotionSolver.hxx>

#include <mapPolyMesh.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(velocityMotionSolver, 0);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::velocityMotionSolver::velocityMotionSolver
(
	const polyMesh& mesh,
	const dictionary& dict,
	const word& type
)
	:
	motionSolver(mesh, dict, type),
	pointMotionU_
	(
		tnbLib::IOobject
		(
			"pointMotionU",
			mesh.time().timeName(),
			mesh,
			tnbLib::IOobject::MUST_READ,
			tnbLib::IOobject::AUTO_WRITE
		),
		pointMesh::New(mesh)
	)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::velocityMotionSolver::~velocityMotionSolver()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::velocityMotionSolver::movePoints(const pointField& p)
{
	// No local data that needs adapting.
}


void tnbLib::velocityMotionSolver::updateMesh(const mapPolyMesh& mpm)
{
	// pointMesh already updates pointFields.

	motionSolver::updateMesh(mpm);
}


// ************************************************************************* //