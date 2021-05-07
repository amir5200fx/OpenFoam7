#include <rigidBodyModelState.hxx>

#include <IOstreams.hxx>

// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void tnbLib::RBD::rigidBodyModelState::write(dictionary& dict) const
{
	dict.add("q", q_);
	dict.add("qDot", qDot_);
	dict.add("qDdot", qDdot_);
	dict.add("t", t_);
	dict.add("deltaT", deltaT_);
}


void tnbLib::RBD::rigidBodyModelState::write(Ostream& os) const
{
	writeEntry(os, "q", q_);
	writeEntry(os, "qDot", qDot_);
	writeEntry(os, "qDdot", qDdot_);
	writeEntry(os, "t", t_);
	writeEntry(os, "deltaT", deltaT_);
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

tnbLib::Istream& tnbLib::RBD::operator>>
(
	Istream& is,
	rigidBodyModelState& state
	)
{
	is >> state.q_
		>> state.qDot_
		>> state.qDdot_
		>> state.t_
		>> state.deltaT_;

	// Check state of Istream
	is.check
	(
		"tnbLib::Istream& tnbLib::operator>>"
		"(tnbLib::Istream&, tnbLib::RBD::rigidBodyModelState&)"
	);

	return is;
}


tnbLib::Ostream& tnbLib::RBD::operator<<
(
	Ostream& os,
	const rigidBodyModelState& state
	)
{
	os << state.q_
		<< token::SPACE << state.qDot_
		<< token::SPACE << state.qDdot_
		<< token::SPACE << state.t_
		<< token::SPACE << state.deltaT_;

	// Check state of Ostream
	os.check
	(
		"tnbLib::Ostream& tnbLib::operator<<(tnbLib::Ostream&, "
		"const tnbLib::RBD::rigidBodyModelState&)"
	);

	return os;
}


// ************************************************************************* //