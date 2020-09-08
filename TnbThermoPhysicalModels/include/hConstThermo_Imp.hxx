#pragma once
#include <IOstreams.hxx>
#include <dictionary.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class EquationOfState>
tnbLib::hConstThermo<EquationOfState>::hConstThermo(const dictionary& dict)
	:
	EquationOfState(dict),
	Cp_(readScalar(dict.subDict("thermodynamics").lookup("Cp"))),
	Hf_(readScalar(dict.subDict("thermodynamics").lookup("Hf")))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class EquationOfState>
void tnbLib::hConstThermo<EquationOfState>::write(Ostream& os) const
{
	EquationOfState::write(os);

	dictionary dict("thermodynamics");
	dict.add("Cp", Cp_);
	dict.add("Hf", Hf_);
	os << indent << dict.dictName() << dict;
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

template<class EquationOfState>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const hConstThermo<EquationOfState>& ct
	)
{
	ct.write(os);
	return os;
}


// ************************************************************************* //