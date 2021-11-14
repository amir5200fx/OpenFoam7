#include <sixDoFRigidBodyMotionConstraint.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(sixDoFRigidBodyMotionConstraint, 0);
	defineRunTimeSelectionTable(sixDoFRigidBodyMotionConstraint, dictionary);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::sixDoFRigidBodyMotionConstraint::sixDoFRigidBodyMotionConstraint
(
	const word& name,
	const dictionary& sDoFRBMCDict,
	const sixDoFRigidBodyMotion& motion
)
	:
	name_(name),
	sDoFRBMCCoeffs_(sDoFRBMCDict),
	motion_(motion)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::sixDoFRigidBodyMotionConstraint::~sixDoFRigidBodyMotionConstraint()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool tnbLib::sixDoFRigidBodyMotionConstraint::read
(
	const dictionary& sDoFRBMCDict
)
{
	sDoFRBMCCoeffs_ = sDoFRBMCDict;

	return true;
}


void tnbLib::sixDoFRigidBodyMotionConstraint::write(Ostream& os) const
{}


// ************************************************************************* //