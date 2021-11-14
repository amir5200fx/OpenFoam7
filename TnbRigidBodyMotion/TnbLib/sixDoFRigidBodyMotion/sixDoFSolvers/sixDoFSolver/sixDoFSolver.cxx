#include <sixDoFSolver.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(sixDoFSolver, 0);
	defineRunTimeSelectionTable(sixDoFSolver, dictionary);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::sixDoFSolver::sixDoFSolver(sixDoFRigidBodyMotion& body)
	:
	body_(body)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::sixDoFSolver::~sixDoFSolver()
{}


// ************************************************************************* //