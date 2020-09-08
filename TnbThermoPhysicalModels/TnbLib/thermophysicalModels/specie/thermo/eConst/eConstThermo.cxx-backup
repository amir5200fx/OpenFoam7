#include <eConstThermo.hxx>

#include <IOstreams.hxx>
#include <dictionary.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class EquationOfState>
tnbLib::eConstThermo<EquationOfState>::eConstThermo(const dictionary& dict)
	:
	EquationOfState(dict),
	Cv_(readScalar(dict.subDict("thermodynamics").lookup("Cv"))),
	Hf_(readScalar(dict.subDict("thermodynamics").lookup("Hf")))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class EquationOfState>
void tnbLib::eConstThermo<EquationOfState>::write(Ostream& os) const
{
	EquationOfState::write(os);

	dictionary dict("thermodynamics");
	dict.add("Cv", Cv_);
	dict.add("Hf", Hf_);
	os << indent << dict.dictName() << dict;
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

template<class EquationOfState>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const eConstThermo<EquationOfState>& ct
	)
{
	ct.write(os);
	return os;
}


// ************************************************************************* //