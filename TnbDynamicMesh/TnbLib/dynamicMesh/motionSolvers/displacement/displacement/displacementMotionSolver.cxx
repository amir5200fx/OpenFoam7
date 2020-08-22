#include <displacementMotionSolver.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(displacementMotionSolver, 0);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::displacementMotionSolver::displacementMotionSolver
(
	const polyMesh& mesh,
	const dictionary& dict,
	const word& type
)
	:
	points0MotionSolver(mesh, dict, type),
	pointDisplacement_
	(
		IOobject
		(
			"pointDisplacement",
			mesh.time().timeName(),
			mesh,
			IOobject::MUST_READ,
			IOobject::AUTO_WRITE
		),
		pointMesh::New(mesh)
	)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::displacementMotionSolver::~displacementMotionSolver()
{}


// ************************************************************************* //