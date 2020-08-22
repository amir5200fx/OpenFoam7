#include <motionSolverList.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(motionSolverList, 0);
	addToRunTimeSelectionTable
	(
		motionSolver,
		motionSolverList,
		dictionary
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::motionSolverList::motionSolverList
(
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	motionSolver(mesh, dict, typeName),
	motionSolvers_
	(
		dict.lookup("solvers"),
		motionSolver::iNew(mesh)
	)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::motionSolverList::~motionSolverList()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::pointField> tnbLib::motionSolverList::curPoints() const
{
	if (motionSolvers_.size())
	{
		// Accumulated displacement
		pointField disp(motionSolvers_[0].curPoints() - mesh().points());

		for (label i = 1; i < motionSolvers_.size(); i++)
		{
			disp += motionSolvers_[i].curPoints() - mesh().points();
		}

		return mesh().points() + disp;
	}
	else
	{
		return mesh().points();
	}
}


void tnbLib::motionSolverList::solve()
{
	forAll(motionSolvers_, i)
	{
		motionSolvers_[i].solve();
	}
}


void tnbLib::motionSolverList::movePoints(const pointField& points)
{
	forAll(motionSolvers_, i)
	{
		motionSolvers_[i].movePoints(points);
	}
}


void tnbLib::motionSolverList::updateMesh(const mapPolyMesh& mpm)
{
	forAll(motionSolvers_, i)
	{
		motionSolvers_[i].updateMesh(mpm);
	}
}


// ************************************************************************* //