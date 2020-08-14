#include <hPolynomialThermo.hxx>

#include <IOstreams.hxx>
#include <dictionary.hxx>
#include <thermodynamicConstants.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class EquationOfState, int PolySize>
tnbLib::hPolynomialThermo<EquationOfState, PolySize>::hPolynomialThermo
(
	const dictionary& dict
)
	:
	EquationOfState(dict),
	Hf_(readScalar(dict.subDict("thermodynamics").lookup("Hf"))),
	Sf_(readScalar(dict.subDict("thermodynamics").lookup("Sf"))),
	CpCoeffs_
	(
		dict.subDict("thermodynamics").lookup
		(
			"CpCoeffs<" + tnbLib::name(PolySize) + '>'
		)
	),
	hCoeffs_(),
	sCoeffs_()
{
	hCoeffs_ = CpCoeffs_.integral();
	sCoeffs_ = CpCoeffs_.integralMinus1();

	// Offset h poly so that it is relative to the enthalpy at Tstd
	hCoeffs_[0] += Hf_ - hCoeffs_.value(constant::thermodynamic::Tstd);

	// Offset s poly so that it is relative to the entropy at Tstd
	sCoeffs_[0] += Sf_ - sCoeffs_.value(constant::thermodynamic::Tstd);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class EquationOfState, int PolySize>
void tnbLib::hPolynomialThermo<EquationOfState, PolySize>::write
(
	Ostream& os
) const
{
	EquationOfState::write(os);

	dictionary dict("thermodynamics");
	dict.add("Hf", Hf_);
	dict.add("Sf", Sf_);
	dict.add
	(
		word("CpCoeffs<" + tnbLib::name(PolySize) + '>'),
		CpCoeffs_
	);
	os << indent << dict.dictName() << dict;
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

template<class EquationOfState, int PolySize>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const hPolynomialThermo<EquationOfState, PolySize>& pt
	)
{
	pt.write(os);
	return os;
}


// ************************************************************************* //