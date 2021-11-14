#include <sixDoFSphericalAngularDamper.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <sixDoFRigidBodyMotion.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace sixDoFRigidBodyMotionRestraints
	{
		defineTypeNameAndDebug(sphericalAngularDamper, 0);

		addToRunTimeSelectionTable
		(
			sixDoFRigidBodyMotionRestraint,
			sphericalAngularDamper,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::sixDoFRigidBodyMotionRestraints::sphericalAngularDamper::
sphericalAngularDamper
(
	const word& name,
	const dictionary& sDoFRBMRDict
)
	:
	sixDoFRigidBodyMotionRestraint(name, sDoFRBMRDict),
	coeff_()
{
	read(sDoFRBMRDict);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::sixDoFRigidBodyMotionRestraints::sphericalAngularDamper::
~sphericalAngularDamper()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void tnbLib::sixDoFRigidBodyMotionRestraints::sphericalAngularDamper::restrain
(
	const sixDoFRigidBodyMotion& motion,
	vector& restraintPosition,
	vector& restraintForce,
	vector& restraintMoment
) const
{
	restraintMoment = -coeff_ * motion.omega();
	restraintForce = Zero;

	if (motion.report())
	{
		Info << " moment " << restraintMoment
			<< endl;
	}
}


bool tnbLib::sixDoFRigidBodyMotionRestraints::sphericalAngularDamper::read
(
	const dictionary& sDoFRBMRDict
)
{
	sixDoFRigidBodyMotionRestraint::read(sDoFRBMRDict);

	sDoFRBMRCoeffs_.lookup("coeff") >> coeff_;

	return true;
}


void tnbLib::sixDoFRigidBodyMotionRestraints::sphericalAngularDamper::write
(
	Ostream& os
) const
{
	writeEntry(os, "coeff", coeff_);
}


// ************************************************************************* //