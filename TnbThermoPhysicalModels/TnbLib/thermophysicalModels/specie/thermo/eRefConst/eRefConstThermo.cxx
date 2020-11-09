#include <eRefConstThermo.hxx>

//#include <IOstreams.hxx>
//#include <dictionary.hxx>  // added by amir
//
//// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //
//
//template<class EquationOfState>
//tnbLib::eRefConstThermo<EquationOfState>::eRefConstThermo(const dictionary& dict)
//	:
//	EquationOfState(dict),
//	Cv_(readScalar(dict.subDict("thermodynamics").lookup("Cv"))),
//	Hf_(readScalar(dict.subDict("thermodynamics").lookup("Hf"))),
//	Tref_(readScalar(dict.subDict("thermodynamics").lookup("Tref"))),
//	Eref_(readScalar(dict.subDict("thermodynamics").lookup("Eref")))
//{}
//
//
//// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //
//
//template<class EquationOfState>
//void tnbLib::eRefConstThermo<EquationOfState>::write(Ostream& os) const
//{
//	EquationOfState::write(os);
//
//	dictionary dict("thermodynamics");
//	dict.add("Cv", Cv_);
//	dict.add("Hf", Hf_);
//	dict.add("Tref", Tref_);
//	dict.add("Eref", Eref_);
//	os << indent << dict.dictName() << dict;
//}
//
//
//// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //
//
//template<class EquationOfState>
//tnbLib::Ostream& tnbLib::operator<<
//(
//	Ostream& os,
//	const eRefConstThermo<EquationOfState>& ct
//	)
//{
//	ct.write(os);
//	return os;
//}
//
//
//// ************************************************************************* //