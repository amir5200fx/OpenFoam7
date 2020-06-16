#include <fundamentalConstants.hxx>

#include <universalConstants.hxx>
#include <electromagneticConstants.hxx>
#include <atomicConstants.hxx>
#include <physicoChemicalConstants.hxx>

#include <dimensionedConstants.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// Universal constants

namespace tnbLib
{
	namespace constant
	{

		defineDimensionedConstant
		(
			universal::group,
			universal::c,
			constantuniversalc,
			"c"
		);


		defineDimensionedConstant
		(
			universal::group,
			universal::G,
			constantuniversalG,
			"G"
		);


		defineDimensionedConstant
		(
			universal::group,
			universal::h,
			constantuniversalh,
			"h"
		);


		// Electromagnetic

		defineDimensionedConstant
		(
			electromagnetic::group,
			electromagnetic::e,
			constantelectromagnetice,
			"e"
		);


		// Atomic

		defineDimensionedConstant
		(
			atomic::group,
			atomic::me,
			constantatomicme,
			"me"
		);


		defineDimensionedConstant
		(
			atomic::group,
			atomic::mp,
			constantatomicmp,
			"mp"
		);


		// Physico-chemical

		defineDimensionedConstant
		(
			physicoChemical::group,
			physicoChemical::mu,
			constantphysicoChemicalmu,
			"mu"
		);


		// Note: cannot use dimless etc since not guaranteed to be constructed
		defineDimensionedConstantWithDefault
		(
			physicoChemical::group,
			physicoChemical::NA,
			tnbLib::dimensionedScalar
			(
				"NA",
				dimensionSet(0, 0, 0, 0, -1), // tnbLib::dimless/tnbLib::dimMoles,
				6.0221417930e+23
			),
			constantphysicoChemicalNA,
			"NA"
		);


		defineDimensionedConstant
		(
			physicoChemical::group,
			physicoChemical::k,
			constantphysicoChemicalk,
			"k"
		);


		// Standard

		defineDimensionedConstant
		(
			"standard",
			standard::Pstd,
			constantstandardPstd,
			"Pstd"
		);


		defineDimensionedConstant
		(
			"standard",
			standard::Tstd,
			constantstandardTstd,
			"Tstd"
		);


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace constant
} // End namespace tnbLib

// ************************************************************************* //
