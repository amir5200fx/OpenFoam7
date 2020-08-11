#pragma once
#include <token.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline tnbLib::specieElement::specieElement()
{}


inline tnbLib::specieElement::specieElement(const word& name, const label nAtoms)
	:
	name_(name),
	nAtoms_(nAtoms)
{}


inline tnbLib::specieElement::specieElement(Istream& is)
	:
	name_(is),
	nAtoms_(readLabel(is))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline const tnbLib::word& tnbLib::specieElement::name() const
{
	return name_;
}


inline tnbLib::word& tnbLib::specieElement::name()
{
	return name_;
}


inline tnbLib::label tnbLib::specieElement::nAtoms() const
{
	return nAtoms_;
}


inline tnbLib::label& tnbLib::specieElement::nAtoms()
{
	return nAtoms_;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

inline bool tnbLib::specieElement::operator==(const specieElement& se) const
{
	return
		(
			nAtoms_ == se.nAtoms_
			&& name_ == se.name_
			);
}


inline bool tnbLib::specieElement::operator!=(const specieElement& se) const
{
	return !operator==(se);
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

inline tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const specieElement& se)
{
	os << se.name() << token::SPACE << se.nAtoms();
	return os;
}


// ************************************************************************* //