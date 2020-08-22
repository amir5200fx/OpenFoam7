#include <fvMotionSolver.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(fvMotionSolver, 0);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fvMotionSolver::fvMotionSolver(const polyMesh& mesh)
	:
	fvMesh_(refCast<const fvMesh>(mesh))
{}


// ************************************************************************* //