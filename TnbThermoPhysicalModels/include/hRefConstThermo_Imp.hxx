#pragma once
#include <IOstreams.hxx>
#include <dictionary.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class EquationOfState>
tnbLib::hRefConstThermo<EquationOfState>::hRefConstThermo(const dictionary& dict)
	:
	EquationOfState(dict),
	Cp_(readScalar(dict.subDict("thermodynamics").lookup("Cp"))),
	Hf_(readScalar(dict.subDict("thermodynamics").lookup("Hf"))),
	Tref_(readScalar(dict.subDict("thermodynamics").lookup("Tref"))),
	Href_(readScalar(dict.subDict("thermodynamics").lookup("Href")))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class EquationOfState>
void tnbLib::hRefConstThermo<EquationOfState>::write(Ostream& os) const
{
	EquationOfState::write(os);

	dictionary dict("thermodynamics");
	dict.add("Cp", Cp_);
	dict.add("Hf", Hf_);
	dict.add("Tref", Tref_);
	dict.add("Href", Href_);
	os << indent << dict.dictName() << dict;
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

template<class EquationOfState>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const hRefConstThermo<EquationOfState>& ct
	)
{
	ct.write(os);
	return os;
}


// ************************************************************************* //