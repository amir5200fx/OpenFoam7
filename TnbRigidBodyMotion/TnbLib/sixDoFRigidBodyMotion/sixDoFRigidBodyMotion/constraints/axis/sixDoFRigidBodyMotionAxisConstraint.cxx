#include <sixDoFRigidBodyMotionAxisConstraint.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <sixDoFRigidBodyMotion.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace sixDoFRigidBodyMotionConstraints
	{
		defineTypeNameAndDebug(axis, 0);

		addToRunTimeSelectionTable
		(
			sixDoFRigidBodyMotionConstraint,
			axis,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::sixDoFRigidBodyMotionConstraints::axis::axis
(
	const word& name,
	const dictionary& sDoFRBMCDict,
	const sixDoFRigidBodyMotion& motion
)
	:
	sixDoFRigidBodyMotionConstraint(name, sDoFRBMCDict, motion),
	axis_()
{
	read(sDoFRBMCDict);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::sixDoFRigidBodyMotionConstraints::axis::~axis()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void tnbLib::sixDoFRigidBodyMotionConstraints::axis::constrainTranslation
(
	pointConstraint& pc
) const
{}


void tnbLib::sixDoFRigidBodyMotionConstraints::axis::constrainRotation
(
	pointConstraint& pc
) const
{
	pc.combine(pointConstraint(Tuple2<label, vector>(2, axis_)));
}


bool tnbLib::sixDoFRigidBodyMotionConstraints::axis::read
(
	const dictionary& sDoFRBMCDict
)
{
	sixDoFRigidBodyMotionConstraint::read(sDoFRBMCDict);

	sDoFRBMCCoeffs_.lookup("axis") >> axis_;

	scalar magFixedAxis(mag(axis_));

	if (magFixedAxis > vSmall)
	{
		axis_ /= magFixedAxis;
	}
	else
	{
		FatalErrorInFunction
			<< "axis has zero length"
			<< abort(FatalError);
	}

	return true;
}


void tnbLib::sixDoFRigidBodyMotionConstraints::axis::write
(
	Ostream& os
) const
{
	writeEntry(os, "axis", axis_);
}

// ************************************************************************* //