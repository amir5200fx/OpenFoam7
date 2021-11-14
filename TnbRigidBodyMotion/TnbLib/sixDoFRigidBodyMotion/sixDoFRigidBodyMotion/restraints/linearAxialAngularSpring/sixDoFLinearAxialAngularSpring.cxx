#include <sixDoFLinearAxialAngularSpring.hxx>

#include <sixDoFRigidBodyMotion.hxx>
#include <transform.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace sixDoFRigidBodyMotionRestraints
	{
		defineTypeNameAndDebug(linearAxialAngularSpring, 0);

		addToRunTimeSelectionTable
		(
			sixDoFRigidBodyMotionRestraint,
			linearAxialAngularSpring,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::sixDoFRigidBodyMotionRestraints::linearAxialAngularSpring::
linearAxialAngularSpring
(
	const word& name,
	const dictionary& sDoFRBMRDict
)
	:
	sixDoFRigidBodyMotionRestraint(name, sDoFRBMRDict),
	refQ_(),
	axis_(),
	stiffness_(),
	damping_()
{
	read(sDoFRBMRDict);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::sixDoFRigidBodyMotionRestraints::linearAxialAngularSpring::
~linearAxialAngularSpring()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void
tnbLib::sixDoFRigidBodyMotionRestraints::linearAxialAngularSpring::restrain
(
	const sixDoFRigidBodyMotion& motion,
	vector& restraintPosition,
	vector& restraintForce,
	vector& restraintMoment
) const
{
	vector refDir = rotationTensor(vector(1, 0, 0), axis_) & vector(0, 1, 0);

	vector oldDir = refQ_ & refDir;
	vector newDir = motion.orientation() & refDir;

	if (mag(oldDir & axis_) > 0.95 || mag(newDir & axis_) > 0.95)
	{
		// Directions getting close to the axis, change reference

		refDir = rotationTensor(vector(1, 0, 0), axis_) & vector(0, 0, 1);
		oldDir = refQ_ & refDir;
		newDir = motion.orientation() & refDir;
	}

	// Removing any axis component from oldDir and newDir and normalising
	oldDir -= (axis_ & oldDir)*axis_;
	oldDir /= (mag(oldDir) + vSmall);

	newDir -= (axis_ & newDir)*axis_;
	newDir /= (mag(newDir) + vSmall);

	scalar theta = mag(acos(min(oldDir & newDir, 1.0)));

	// Temporary axis with sign information.
	vector a = (oldDir ^ newDir);

	// Remove any component that is not along axis that may creep in
	a = (a & axis_)*axis_;

	scalar magA = mag(a);

	if (magA > vSmall)
	{
		a /= magA;
	}
	else
	{
		a = Zero;
	}

	// Damping of along axis angular velocity only
	restraintMoment = -stiffness_ * theta*a - damping_ * (motion.omega() & a)*a;

	restraintForce = Zero;

	// Not needed to be altered as restraintForce is zero, but set to
	// centreOfRotation to be sure of no spurious moment
	restraintPosition = motion.centreOfRotation();

	if (motion.report())
	{
		Info << " angle " << theta * sign(a & axis_)
			<< " moment " << restraintMoment
			<< endl;
	}
}


bool tnbLib::sixDoFRigidBodyMotionRestraints::linearAxialAngularSpring::read
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

	axis_ = sDoFRBMRCoeffs_.lookup("axis");

	scalar magAxis(mag(axis_));

	if (magAxis > vSmall)
	{
		axis_ /= magAxis;
	}
	else
	{
		FatalErrorInFunction
			<< "axis has zero length"
			<< abort(FatalError);
	}

	sDoFRBMRCoeffs_.lookup("stiffness") >> stiffness_;
	sDoFRBMRCoeffs_.lookup("damping") >> damping_;

	return true;
}


void tnbLib::sixDoFRigidBodyMotionRestraints::linearAxialAngularSpring::write
(
	Ostream& os
) const
{
	writeEntry(os, "referenceOrientation", refQ_);

	writeEntry(os, "axis", axis_);

	writeEntry(os, "stiffness", stiffness_);

	writeEntry(os, "damping", damping_);
}

// ************************************************************************* //