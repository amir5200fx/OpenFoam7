#include <CrankNicolsonSixDoFSolver.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace sixDoFSolvers
	{
		defineTypeNameAndDebug(CrankNicolson, 0);
		addToRunTimeSelectionTable(sixDoFSolver, CrankNicolson, dictionary);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::sixDoFSolvers::CrankNicolson::CrankNicolson
(
	const dictionary& dict,
	sixDoFRigidBodyMotion& body
)
	:
	sixDoFSolver(body),
	aoc_(dict.lookupOrDefault<scalar>("aoc", 0.5)),
	voc_(dict.lookupOrDefault<scalar>("voc", 0.5))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::sixDoFSolvers::CrankNicolson::~CrankNicolson()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::sixDoFSolvers::CrankNicolson::solve
(
	bool firstIter,
	const vector& fGlobal,
	const vector& tauGlobal,
	scalar deltaT,
	scalar deltaT0
)
{
	// Update the linear acceleration and torque
	updateAcceleration(fGlobal, tauGlobal);

	// Correct linear velocity
	v() = tConstraints()
		& (v0() + aDamp()*deltaT*(aoc_*a() + (1 - aoc_)*a0()));

	// Correct angular momentum
	pi() = rConstraints()
		& (pi0() + aDamp()*deltaT*(aoc_*tau() + (1 - aoc_)*tau0()));

	// Correct position
	centreOfRotation() =
		centreOfRotation0() + deltaT * (voc_*v() + (1 - voc_)*v0());

	// Correct orientation
	Tuple2<tensor, vector> Qpi =
		rotate(Q0(), (voc_*pi() + (1 - voc_)*pi0()), deltaT);
	Q() = Qpi.first();
}


// ************************************************************************* //