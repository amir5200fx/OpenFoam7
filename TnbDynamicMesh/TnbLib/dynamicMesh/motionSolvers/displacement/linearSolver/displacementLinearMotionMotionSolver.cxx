#include <displacementLinearMotionMotionSolver.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(displacementLinearMotionMotionSolver, 0);

	addToRunTimeSelectionTable
	(
		motionSolver,
		displacementLinearMotionMotionSolver,
		dictionary
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::displacementLinearMotionMotionSolver::
displacementLinearMotionMotionSolver
(
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	points0MotionSolver(mesh, dict, typeName),
	axis_(normalised(vector(coeffDict().lookup("axis")))),
	xFixed_(readScalar(coeffDict().lookup("xFixed"))),
	xMoving_(readScalar(coeffDict().lookup("xMoving"))),
	displacement_(Function1<scalar>::New("displacement", coeffDict()))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::displacementLinearMotionMotionSolver::
~displacementLinearMotionMotionSolver()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::pointField>
tnbLib::displacementLinearMotionMotionSolver::curPoints() const
{
	tmp<pointField> tcurPoints(new pointField(points0()));
	pointField& curPoints = tcurPoints.ref();

	const scalar t = mesh().time().value();

	const scalar displacement = displacement_->value(t);

	forAll(curPoints, i)
	{
		const scalar lambda =
			(xFixed_ - (axis_ & curPoints[i])) / (xFixed_ - xMoving_);

		if (lambda > 1)
		{
			curPoints[i] += axis_ * displacement;
		}
		else if (lambda > 0)
		{
			curPoints[i] += axis_ * lambda*displacement;
		}
	}

	return tcurPoints;
}


// ************************************************************************* //