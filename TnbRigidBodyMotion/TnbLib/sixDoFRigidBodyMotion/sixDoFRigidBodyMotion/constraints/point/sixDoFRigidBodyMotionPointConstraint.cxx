#include <sixDoFRigidBodyMotionPointConstraint.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <sixDoFRigidBodyMotion.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace sixDoFRigidBodyMotionConstraints
	{
		defineTypeNameAndDebug(point, 0);

		addToRunTimeSelectionTable
		(
			sixDoFRigidBodyMotionConstraint,
			point,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::sixDoFRigidBodyMotionConstraints::point::point
(
	const word& name,
	const dictionary& sDoFRBMCDict,
	const sixDoFRigidBodyMotion& motion
)
	:
	sixDoFRigidBodyMotionConstraint(name, sDoFRBMCDict, motion),
	centreOfRotation_()
{
	read(sDoFRBMCDict);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::sixDoFRigidBodyMotionConstraints::point::~point()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void tnbLib::sixDoFRigidBodyMotionConstraints::point::setCentreOfRotation
(
	tnbLib::point& CofR
) const
{
	CofR = centreOfRotation_;
}


void tnbLib::sixDoFRigidBodyMotionConstraints::point::constrainTranslation
(
	pointConstraint& pc
) const
{
	pc.combine(pointConstraint(Tuple2<label, vector>(3, Zero)));
}


void tnbLib::sixDoFRigidBodyMotionConstraints::point::constrainRotation
(
	pointConstraint& pc
) const
{}


bool tnbLib::sixDoFRigidBodyMotionConstraints::point::read
(
	const dictionary& sDoFRBMCDict
)
{
	sixDoFRigidBodyMotionConstraint::read(sDoFRBMCDict);

	centreOfRotation_ = sDoFRBMCCoeffs_.lookupOrDefault
	(
		"centreOfRotation",
		motion_.initialCentreOfMass()
	);

	return true;
}


void tnbLib::sixDoFRigidBodyMotionConstraints::point::write
(
	Ostream& os
) const
{
	writeEntry(os, "centreOfRotation", centreOfRotation_);
}

// ************************************************************************* //