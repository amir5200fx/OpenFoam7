#include <sixDoFRigidBodyMotionLineConstraint.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <sixDoFRigidBodyMotion.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace sixDoFRigidBodyMotionConstraints
	{
		defineTypeNameAndDebug(line, 0);

		addToRunTimeSelectionTable
		(
			sixDoFRigidBodyMotionConstraint,
			line,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::sixDoFRigidBodyMotionConstraints::line::line
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

tnbLib::sixDoFRigidBodyMotionConstraints::line::~line()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void tnbLib::sixDoFRigidBodyMotionConstraints::line::setCentreOfRotation
(
	point& CofR
) const
{
	CofR = centreOfRotation_;
}


void tnbLib::sixDoFRigidBodyMotionConstraints::line::constrainTranslation
(
	pointConstraint& pc
) const
{
	pc.combine(pointConstraint(Tuple2<label, vector>(2, direction_)));
}


void tnbLib::sixDoFRigidBodyMotionConstraints::line::constrainRotation
(
	pointConstraint& pc
) const
{}


bool tnbLib::sixDoFRigidBodyMotionConstraints::line::read
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

	sDoFRBMCCoeffs_.lookup("direction") >> direction_;

	scalar magDir(mag(direction_));

	if (magDir > vSmall)
	{
		direction_ /= magDir;
	}
	else
	{
		FatalErrorInFunction
			<< "line direction has zero length"
			<< abort(FatalError);
	}

	return true;
}


void tnbLib::sixDoFRigidBodyMotionConstraints::line::write
(
	Ostream& os
) const
{
	writeEntry(os, "centreOfRotation", centreOfRotation_);
	writeEntry(os, "direction", direction_);
}

// ************************************************************************* //