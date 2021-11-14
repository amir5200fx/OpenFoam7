#include <sixDoFRigidBodyMotionState.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::sixDoFRigidBodyMotionState::sixDoFRigidBodyMotionState()
	:
	centreOfRotation_(Zero),
	Q_(I),
	v_(Zero),
	a_(Zero),
	pi_(Zero),
	tau_(Zero)
{}


tnbLib::sixDoFRigidBodyMotionState::sixDoFRigidBodyMotionState
(
	const dictionary& dict
)
	:
	centreOfRotation_
	(
		dict.lookupOrDefault
		(
			"centreOfRotation",
			dict.lookupOrDefault("centreOfMass", vector::zero)
		)
	),
	Q_(dict.lookupOrDefault("orientation", tensor::I)),
	v_(dict.lookupOrDefault("velocity", vector::zero)),
	a_(dict.lookupOrDefault("acceleration", vector::zero)),
	pi_(dict.lookupOrDefault("angularMomentum", vector::zero)),
	tau_(dict.lookupOrDefault("torque", vector::zero))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::sixDoFRigidBodyMotionState::~sixDoFRigidBodyMotionState()
{}


// ************************************************************************* //