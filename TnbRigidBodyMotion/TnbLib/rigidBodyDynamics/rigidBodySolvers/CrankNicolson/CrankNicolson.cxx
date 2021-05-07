#include <CrankNicolson.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace RBD
	{
		namespace rigidBodySolvers
		{
			defineTypeNameAndDebug(CrankNicolson, 0);
			addToRunTimeSelectionTable(rigidBodySolver, CrankNicolson, dictionary);
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::RBD::rigidBodySolvers::CrankNicolson::CrankNicolson
(
	rigidBodyMotion& body,
	const dictionary& dict
)
	:
	rigidBodySolver(body),
	aoc_(dict.lookupOrDefault<scalar>("aoc", 0.5)),
	voc_(dict.lookupOrDefault<scalar>("voc", 0.5))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::RBD::rigidBodySolvers::CrankNicolson::~CrankNicolson()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::RBD::rigidBodySolvers::CrankNicolson::solve
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
	qDot() = qDot0() + deltaT()*(aoc_*qDdot() + (1 - aoc_)*qDdot0());

	// Correct position
	q() = q0() + deltaT()*(voc_*qDot() + (1 - voc_)*qDot0());

	correctQuaternionJoints();
}


// ************************************************************************* //