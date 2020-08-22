#include <dynamicMotionSolverFvMesh.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <motionSolver.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(dynamicMotionSolverFvMesh, 0);
	addToRunTimeSelectionTable
	(
		dynamicFvMesh,
		dynamicMotionSolverFvMesh,
		IOobject
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::dynamicMotionSolverFvMesh::dynamicMotionSolverFvMesh(const IOobject& io)
	:
	dynamicFvMesh(io),
	motionPtr_(motionSolver::New(*this, dynamicMeshDict())),
	velocityMotionCorrection_(*this, dynamicMeshDict())
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::dynamicMotionSolverFvMesh::~dynamicMotionSolverFvMesh()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::motionSolver& tnbLib::dynamicMotionSolverFvMesh::motion() const
{
	return motionPtr_();
}


bool tnbLib::dynamicMotionSolverFvMesh::update()
{
	fvMesh::movePoints(motionPtr_->newPoints());
	velocityMotionCorrection_.update();

	return true;
}


bool tnbLib::dynamicMotionSolverFvMesh::writeObject
(
	IOstream::streamFormat fmt,
	IOstream::versionNumber ver,
	IOstream::compressionType cmp,
	const bool write
) const
{
	motionPtr_->write();
	return fvMesh::writeObject(fmt, ver, cmp, write);
}


// ************************************************************************* //