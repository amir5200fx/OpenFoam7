#include <sixDoFLinearSpring.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <sixDoFRigidBodyMotion.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace sixDoFRigidBodyMotionRestraints
	{
		defineTypeNameAndDebug(linearSpring, 0);

		addToRunTimeSelectionTable
		(
			sixDoFRigidBodyMotionRestraint,
			linearSpring,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::sixDoFRigidBodyMotionRestraints::linearSpring::linearSpring
(
	const word& name,
	const dictionary& sDoFRBMRDict
)
	:
	sixDoFRigidBodyMotionRestraint(name, sDoFRBMRDict),
	anchor_(),
	refAttachmentPt_(),
	stiffness_(),
	damping_(),
	restLength_()
{
	read(sDoFRBMRDict);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::sixDoFRigidBodyMotionRestraints::linearSpring::~linearSpring()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void tnbLib::sixDoFRigidBodyMotionRestraints::linearSpring::restrain
(
	const sixDoFRigidBodyMotion& motion,
	vector& restraintPosition,
	vector& restraintForce,
	vector& restraintMoment
) const
{
	restraintPosition = motion.transform(refAttachmentPt_);

	vector r = restraintPosition - anchor_;

	scalar magR = mag(r);
	r /= (magR + vSmall);

	vector v = motion.velocity(restraintPosition);

	restraintForce = -stiffness_ * (magR - restLength_)*r - damping_ * (r & v)*r;

	restraintMoment = Zero;

	if (motion.report())
	{
		Info << " attachmentPt - anchor " << r * magR
			<< " spring length " << magR
			<< " force " << restraintForce
			<< endl;
	}
}


bool tnbLib::sixDoFRigidBodyMotionRestraints::linearSpring::read
(
	const dictionary& sDoFRBMRDict
)
{
	sixDoFRigidBodyMotionRestraint::read(sDoFRBMRDict);

	sDoFRBMRCoeffs_.lookup("anchor") >> anchor_;
	sDoFRBMRCoeffs_.lookup("refAttachmentPt") >> refAttachmentPt_;
	sDoFRBMRCoeffs_.lookup("stiffness") >> stiffness_;
	sDoFRBMRCoeffs_.lookup("damping") >> damping_;
	sDoFRBMRCoeffs_.lookup("restLength") >> restLength_;

	return true;
}


void tnbLib::sixDoFRigidBodyMotionRestraints::linearSpring::write
(
	Ostream& os
) const
{
	writeEntry(os, "anchor", anchor_);

	writeEntry(os, "refAttachmentPt", refAttachmentPt_);

	writeEntry(os, "stiffness", stiffness_);

	writeEntry(os, "damping", damping_);

	writeEntry(os, "restLength", restLength_);
}

// ************************************************************************* //