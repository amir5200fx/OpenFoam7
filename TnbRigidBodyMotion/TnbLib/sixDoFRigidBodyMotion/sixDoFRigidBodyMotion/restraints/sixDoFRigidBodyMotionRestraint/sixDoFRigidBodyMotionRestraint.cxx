#include <sixDoFRigidBodyMotionRestraint.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(sixDoFRigidBodyMotionRestraint, 0);
	defineRunTimeSelectionTable(sixDoFRigidBodyMotionRestraint, dictionary);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::sixDoFRigidBodyMotionRestraint::sixDoFRigidBodyMotionRestraint
(
	const word& name,
	const dictionary& sDoFRBMRDict
)
	:
	name_(name),
	sDoFRBMRCoeffs_(sDoFRBMRDict)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::sixDoFRigidBodyMotionRestraint::~sixDoFRigidBodyMotionRestraint()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool tnbLib::sixDoFRigidBodyMotionRestraint::read
(
	const dictionary& sDoFRBMRDict
)
{
	sDoFRBMRCoeffs_ = sDoFRBMRDict;

	return true;
}


// ************************************************************************* //