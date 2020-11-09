#include <hPowerThermo.hxx>

//#include <IOstreams.hxx>
//#include <dictionary.hxx>  // added by amir
//
//// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //
//
//template<class EquationOfState>
//tnbLib::hPowerThermo<EquationOfState>::hPowerThermo
//(
//	const dictionary& dict
//)
//	:
//	EquationOfState(dict),
//	c0_(readScalar(dict.subDict("thermodynamics").lookup("C0"))),
//	n0_(readScalar(dict.subDict("thermodynamics").lookup("n0"))),
//	Tref_(readScalar(dict.subDict("thermodynamics").lookup("Tref"))),
//	Hf_(readScalar(dict.subDict("thermodynamics").lookup("Hf")))
//{}
//
//
//// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //
//
//template<class EquationOfState>
//tnbLib::Ostream& tnbLib::operator<<
//(
//	Ostream& os,
//	const hPowerThermo<EquationOfState>& et
//	)
//{
//	et.write(os);
//	return os;
//}
//
//
//// ************************************************************************* //