#pragma once
#include <IOstreams.hxx>

#include <sstream>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Form, class Cmpt, tnbLib::direction Ncmpts>
tnbLib::VectorSpace<Form, Cmpt, Ncmpts>::VectorSpace
(
	Istream& is
)
{
	// Read beginning of VectorSpace<Cmpt>
	is.readBegin("VectorSpace<Form, Cmpt, Ncmpts>");

	for (direction i = 0; i < Ncmpts; i++)
	{
		is >> v_[i];
	}

	// Read end of VectorSpace<Cmpt>
	is.readEnd("VectorSpace<Form, Cmpt, Ncmpts>");

	// Check state of Istream
	is.check("VectorSpace<Form, Cmpt, Ncmpts>::VectorSpace(Istream&)");
}


template<class Form, class Cmpt, tnbLib::direction Ncmpts>
tnbLib::word tnbLib::name
(
	const VectorSpace<Form, Cmpt, Ncmpts>& vs
)
{
	std::ostringstream buf;

	buf << '(' << vs.v_[0];

	for (direction i = 1; i < Ncmpts; i++)
	{
		buf << ',' << vs.v_[i];
	}

	buf << ')';

	return buf.str();
}


// * * * * * * * * * * * * * * * IOstream Functions  * * * * * * * * * * * * //

template<class Form, class Cmpt, tnbLib::direction Ncmpts>
void tnbLib::writeEntry(Ostream& os, const VectorSpace<Form, Cmpt, Ncmpts>& value)
{
	os << value;
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

template<class Form, class Cmpt, tnbLib::direction Ncmpts>
tnbLib::Istream& tnbLib::operator>>
(
	Istream& is,
	VectorSpace<Form, Cmpt, Ncmpts>& vs
	)
{
	// Read beginning of VectorSpace<Cmpt, Ncmpts>
	is.readBegin("VectorSpace<Form, Cmpt, Ncmpts>");

	for (direction i = 0; i < Ncmpts; i++)
	{
		is >> vs.v_[i];
	}

	// Read end of VectorSpace<Cmpt, Ncmpts>
	is.readEnd("VectorSpace<Form, Cmpt, Ncmpts>");

	// Check state of Istream
	is.check("operator>>(Istream&, VectorSpace<Form, Cmpt, Ncmpts>&)");

	return is;
}


template<class Form, class Cmpt, tnbLib::direction Ncmpts>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const VectorSpace<Form, Cmpt, Ncmpts>& vs
	)
{
	os << token::BEGIN_LIST << vs.v_[0];

	for (direction i = 1; i < Ncmpts; i++)
	{
		os << token::SPACE << vs.v_[i];
	}

	os << token::END_LIST;

	// Check state of Ostream
	os.check("operator<<(Ostream&, const VectorSpace<Form, Cmpt, Ncmpts>&)");

	return os;
}


// ************************************************************************* //