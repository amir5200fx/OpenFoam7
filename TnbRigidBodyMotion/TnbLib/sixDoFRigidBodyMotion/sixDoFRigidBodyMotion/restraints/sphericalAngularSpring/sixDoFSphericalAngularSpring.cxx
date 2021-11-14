#include <sixDoFSphericalAngularSpring.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <sixDoFRigidBodyMotion.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace sixDoFRigidBodyMotionRestraints
	{
		defineTypeNameAndDebug(sphericalAngularSpring, 0);

		addToRunTimeSelectionTable
		(
			sixDoFRigidBodyMotionRestraint,
			sphericalAngularSpring,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::sixDoFRigidBodyMotionRestraints::sphericalAngularSpring::
sphericalAngularSpring
(
	const word& name,
	const dictionary& sDoFRBMRDict
)
	:
	sixDoFRigidBodyMotionRestraint(name, sDoFRBMRDict),
	refQ_(),
	stiffness_(),
	damping_()
{
	read(sDoFRBMRDict);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::sixDoFRigidBodyMotionRestraints::sphericalAngularSpring::
~sphericalAngularSpring()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void tnbLib::sixDoFRigidBodyMotionRestraints::sphericalAngularSpring::restrain
(
	const sixDoFRigidBodyMotion& motion,
	vector& restraintPosition,
	vector& restraintForce,
	vector& restraintMoment
) const
{
	restraintMoment = Zero;

	for (direction cmpt = 0; cmpt < vector::nComponents; cmpt++)
	{
		vector axis = Zero;
		axis[cmpt] = 1;

		vector refDir = Zero;
		refDir[(cmpt + 1) % 3] = 1;

		vector newDir = motion.orientation() & refDir;

		axis = (refQ_ & axis);
		refDir = (refQ_ & refDir);
		newDir -= (axis & newDir)*axis;

		restraintMoment += -stiffness_ * (refDir ^ newDir);
	}

	restraintMoment += -damping_ * motion.omega();

	restraintForce = Zero;

	// Not needed to be altered as restraintForce is zero, but set to
	// centreOfRotation to be sure of no spurious moment
	restraintPosition = motion.centreOfRotation();

	if (motion.report())
	{
		Info << " moment " << restraintMoment
			<< endl;
	}
}


bool tnbLib::sixDoFRigidBodyMotionRestraints::sphericalAngularSpring::read
(
	const dictionary& sDoFRBMRDict
)
{
	sixDoFRigidBodyMotionRestraint::read(sDoFRBMRDict);

	refQ_ = sDoFRBMRCoeffs_.lookupOrDefault<tensor>("referenceOrientation", I);

	if (mag(mag(refQ_) - sqrt(3.0)) > 1e-9)
	{
		FatalErrorInFunction
			<< "referenceOrientation " << refQ_ << " is not a rotation tensor. "
			<< "mag(referenceOrientation) - sqrt(3) = "
			<< mag(refQ_) - sqrt(3.0) << nl
			<< exit(FatalError);
	}

	sDoFRBMRCoeffs_.lookup("stiffness") >> stiffness_;
	sDoFRBMRCoeffs_.lookup("damping") >> damping_;

	return true;
}


void tnbLib::sixDoFRigidBodyMotionRestraints::sphericalAngularSpring::write
(
	Ostream& os
) const
{
	writeEntry(os, "referenceOrientation", refQ_);

	writeEntry(os, "stiffness", stiffness_);

	writeEntry(os, "damping", damping_);
}


// ************************************************************************* //