#include <sixDoFRigidBodyMotionOrientationConstraint.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <sixDoFRigidBodyMotion.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace sixDoFRigidBodyMotionConstraints
	{
		defineTypeNameAndDebug(orientation, 0);

		addToRunTimeSelectionTable
		(
			sixDoFRigidBodyMotionConstraint,
			orientation,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::sixDoFRigidBodyMotionConstraints::orientation::orientation
(
	const word& name,
	const dictionary& sDoFRBMCDict,
	const sixDoFRigidBodyMotion& motion
)
	:
	sixDoFRigidBodyMotionConstraint(name, sDoFRBMCDict, motion)
{
	read(sDoFRBMCDict);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::sixDoFRigidBodyMotionConstraints::orientation::~orientation()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void tnbLib::sixDoFRigidBodyMotionConstraints::orientation::
constrainTranslation
(
	pointConstraint& pc
) const
{}


void tnbLib::sixDoFRigidBodyMotionConstraints::orientation::
constrainRotation
(
	pointConstraint& pc
) const
{
	pc.combine(pointConstraint(Tuple2<label, vector>(3, Zero)));
}


bool tnbLib::sixDoFRigidBodyMotionConstraints::orientation::read
(
	const dictionary& sDoFRBMCDict
)
{
	sixDoFRigidBodyMotionConstraint::read(sDoFRBMCDict);

	return true;
}


void tnbLib::sixDoFRigidBodyMotionConstraints::orientation::write
(
	Ostream& os
) const
{
}

// ************************************************************************* //