#include <sixDoFRigidBodyMotionPlaneConstraint.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <sixDoFRigidBodyMotion.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace sixDoFRigidBodyMotionConstraints
	{
		defineTypeNameAndDebug(plane, 0);

		addToRunTimeSelectionTable
		(
			sixDoFRigidBodyMotionConstraint,
			plane,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::sixDoFRigidBodyMotionConstraints::plane::plane
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

tnbLib::sixDoFRigidBodyMotionConstraints::plane::~plane()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void tnbLib::sixDoFRigidBodyMotionConstraints::plane::setCentreOfRotation
(
	point& CofR
) const
{
	CofR = centreOfRotation_;
}


void tnbLib::sixDoFRigidBodyMotionConstraints::plane::constrainTranslation
(
	pointConstraint& pc
) const
{
	pc.applyConstraint(normal_);
}


void tnbLib::sixDoFRigidBodyMotionConstraints::plane::constrainRotation
(
	pointConstraint& pc
) const
{}


bool tnbLib::sixDoFRigidBodyMotionConstraints::plane::read
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

	sDoFRBMCCoeffs_.lookup("normal") >> normal_;

	return true;
}


void tnbLib::sixDoFRigidBodyMotionConstraints::plane::write
(
	Ostream& os
) const
{
	writeEntry(os, "centreOfRotation", centreOfRotation_);
	writeEntry(os, "normal", normal_);
}

// ************************************************************************* //