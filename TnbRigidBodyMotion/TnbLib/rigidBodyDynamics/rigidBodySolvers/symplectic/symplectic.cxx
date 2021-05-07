#include <symplectic.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace RBD
	{
		namespace rigidBodySolvers
		{
			defineTypeNameAndDebug(symplectic, 0);
			addToRunTimeSelectionTable(rigidBodySolver, symplectic, dictionary);
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::RBD::rigidBodySolvers::symplectic::symplectic
(
	rigidBodyMotion& body,
	const dictionary& dict
)
	:
	rigidBodySolver(body)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::RBD::rigidBodySolvers::symplectic::~symplectic()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::RBD::rigidBodySolvers::symplectic::solve
(
	const scalarField& tau,
	const Field<spatialVector>& fx
)
{
	// First simplectic step:
	//     Half-step for linear and angular velocities
	//     Update position and orientation
	qDot() = qDot0() + 0.5*deltaT0()*qDdot();
	q() = q0() + deltaT()*qDot();

	correctQuaternionJoints();

	// Update the body-state prior to the evaluation of the restraints
	model_.forwardDynamicsCorrection(state());

	// Accumulate the restraint forces
	scalarField rtau(tau);
	Field<spatialVector> rfx(fx);
	model_.applyRestraints(rtau, rfx);

	// Calculate the body acceleration for the given state
	// and restraint forces
	model_.forwardDynamics(state(), rtau, rfx);

	// Second simplectic step:
	//     Complete update of linear and angular velocities
	qDot() += 0.5*deltaT()*qDdot();
}


// ************************************************************************* //