#include <Newmark.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace RBD
	{
		namespace rigidBodySolvers
		{
			defineTypeNameAndDebug(Newmark, 0);
			addToRunTimeSelectionTable(rigidBodySolver, Newmark, dictionary);
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::RBD::rigidBodySolvers::Newmark::Newmark
(
	rigidBodyMotion& body,
	const dictionary& dict
)
	:
	rigidBodySolver(body),
	gamma_(dict.lookupOrDefault<scalar>("gamma", 0.5)),
	beta_
	(
		max
		(
			0.25*sqr(gamma_ + 0.5),
			dict.lookupOrDefault<scalar>("beta", 0.25)
		)
	)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::RBD::rigidBodySolvers::Newmark::~Newmark()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::RBD::rigidBodySolvers::Newmark::solve
(
	const scalarField& tau,
	const Field<spatialVector>& fx
)
{
	// Accumulate the restraint forces
	scalarField rtau(tau);
	Field<spatialVector> rfx(fx);
	model_.applyRestraints(rtau, rfx);

	// Calculate the accelerations for the given state and forces
	model_.forwardDynamics(state(), rtau, rfx);

	// Correct velocity
	qDot() = qDot0()
		+ deltaT()*(gamma_*qDdot() + (1 - gamma_)*qDdot0());

	// Correct position
	q() = q0()
		+ deltaT()*qDot0()
		+ sqr(deltaT())*(beta_*qDdot() + (0.5 - beta_)*qDdot0());

	correctQuaternionJoints();
}


// ************************************************************************* //