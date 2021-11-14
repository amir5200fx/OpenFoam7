#include <sixDoFLinearDamper.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <sixDoFRigidBodyMotion.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace sixDoFRigidBodyMotionRestraints
	{
		defineTypeNameAndDebug(linearDamper, 0);

		addToRunTimeSelectionTable
		(
			sixDoFRigidBodyMotionRestraint,
			linearDamper,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::sixDoFRigidBodyMotionRestraints::linearDamper::linearDamper
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

tnbLib::sixDoFRigidBodyMotionRestraints::linearDamper::~linearDamper()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void tnbLib::sixDoFRigidBodyMotionRestraints::linearDamper::restrain
(
	const sixDoFRigidBodyMotion& motion,
	vector& restraintPosition,
	vector& restraintForce,
	vector& restraintMoment
) const
{
	restraintForce = -coeff_ * motion.v();
	restraintMoment = Zero;

	if (motion.report())
	{
		Info << " force " << restraintForce
			<< endl;
	}
}


bool tnbLib::sixDoFRigidBodyMotionRestraints::linearDamper::read
(
	const dictionary& sDoFRBMRDict
)
{
	sixDoFRigidBodyMotionRestraint::read(sDoFRBMRDict);

	sDoFRBMRCoeffs_.lookup("coeff") >> coeff_;

	return true;
}


void tnbLib::sixDoFRigidBodyMotionRestraints::linearDamper::write
(
	Ostream& os
) const
{
	writeEntry(os, "coeff", coeff_);
}


// ************************************************************************* //