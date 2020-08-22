#include <componentVelocityMotionSolver.hxx>

#include <mapPolyMesh.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(componentVelocityMotionSolver, 0);
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

tnbLib::direction tnbLib::componentVelocityMotionSolver::cmpt
(
	const word& cmptName
) const
{
	if (cmptName == "x")
	{
		return vector::X;
	}
	else if (cmptName == "y")
	{
		return vector::Y;
	}
	else if (cmptName == "z")
	{
		return vector::Z;
	}
	else
	{
		FatalErrorInFunction
			<< "Given component name " << cmptName << " should be x, y or z"
			<< exit(FatalError);

		return 0;
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::componentVelocityMotionSolver::componentVelocityMotionSolver
(
	const polyMesh& mesh,
	const dictionary& dict,
	const word& type
)
	:
	motionSolver(mesh, dict, type),
	cmptName_(coeffDict().lookup("component")),
	cmpt_(cmpt(cmptName_)),
	pointMotionU_
	(
		IOobject
		(
			"pointMotionU" + cmptName_,
			mesh.time().timeName(),
			mesh,
			IOobject::MUST_READ,
			IOobject::AUTO_WRITE
		),
		pointMesh::New(mesh)
	)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::componentVelocityMotionSolver::~componentVelocityMotionSolver()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::componentVelocityMotionSolver::movePoints(const pointField& p)
{
	// No local data to adapt
}


void tnbLib::componentVelocityMotionSolver::updateMesh(const mapPolyMesh& mpm)
{
	// pointMesh already updates pointFields.

	motionSolver::updateMesh(mpm);
}


// ************************************************************************* //