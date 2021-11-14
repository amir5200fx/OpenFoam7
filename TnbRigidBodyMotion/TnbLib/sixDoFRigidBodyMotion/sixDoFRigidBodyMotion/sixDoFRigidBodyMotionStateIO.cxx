#include <sixDoFRigidBodyMotionState.hxx>

#include <IOstreams.hxx>

// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void tnbLib::sixDoFRigidBodyMotionState::write(dictionary& dict) const
{
	dict.add("centreOfRotation", centreOfRotation_);
	dict.add("orientation", Q_);
	dict.add("velocity", v_);
	dict.add("acceleration", a_);
	dict.add("angularMomentum", pi_);
	dict.add("torque", tau_);
}


void tnbLib::sixDoFRigidBodyMotionState::write(Ostream& os) const
{
	writeEntry(os, "centreOfRotation", centreOfRotation_);
	writeEntry(os, "orientation", Q_);
	writeEntry(os, "velocity", v_);
	writeEntry(os, "acceleration", a_);
	writeEntry(os, "angularMomentum", pi_);
	writeEntry(os, "torque", tau_);
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

tnbLib::Istream& tnbLib::operator>>
(
	Istream& is, sixDoFRigidBodyMotionState& sDoFRBMS
	)
{
	is >> sDoFRBMS.centreOfRotation_
		>> sDoFRBMS.Q_
		>> sDoFRBMS.v_
		>> sDoFRBMS.a_
		>> sDoFRBMS.pi_
		>> sDoFRBMS.tau_;

	// Check state of Istream
	is.check
	(
		"tnbLib::Istream& tnbLib::operator>>"
		"(tnbLib::Istream&, tnbLib::sixDoFRigidBodyMotionState&)"
	);

	return is;
}


tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const sixDoFRigidBodyMotionState& sDoFRBMS
	)
{
	os << token::SPACE << sDoFRBMS.centreOfRotation()
		<< token::SPACE << sDoFRBMS.Q()
		<< token::SPACE << sDoFRBMS.v()
		<< token::SPACE << sDoFRBMS.a()
		<< token::SPACE << sDoFRBMS.pi()
		<< token::SPACE << sDoFRBMS.tau();

	// Check state of Ostream
	os.check
	(
		"tnbLib::Ostream& tnbLib::operator<<(tnbLib::Ostream&, "
		"const tnbLib::sixDoFRigidBodyMotionState&)"
	);

	return os;
}


// ************************************************************************* //