#include <physicoChemicalConstants.hxx>

#include <mathematicalConstants.hxx>
#include <universalConstants.hxx>
#include <electromagneticConstants.hxx>
#include <physicoChemicalConstants.hxx>

#include <dimensionedConstants.hxx>

#include <fundamentalConstants.hxx> // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace constant
	{

		const char* const physicoChemical::group = "physicoChemical";

		defineDimensionedConstantWithDefault
		(
			physicoChemical::group,
			physicoChemical::R,
			dimensionedScalar
			(
				"R",
				physicoChemical::NA*physicoChemical::k
			),
			constantphysicoChemicalR,
			"R"
		);


		defineDimensionedConstantWithDefault
		(
			physicoChemical::group,
			physicoChemical::F,
			dimensionedScalar
			(
				"F",
				physicoChemical::NA*electromagnetic::e
			),
			constantphysicoChemicalF,
			"F"
		);


		// Note: cannot use dimless etc. since not guaranteed to be constructed
		defineDimensionedConstantWithDefault
		(
			physicoChemical::group,
			physicoChemical::sigma,
			dimensionedScalar
			(
				"sigma",
				tnbLib::dimensionedScalar
				(
					"C",
					dimensionSet(0, 0, 0, 0, 0),    // tnbLib::dimless,
					tnbLib::sqr(mathematical::pi) / 60.0
				)
				*tnbLib::pow4(physicoChemical::k)
				/ (pow3(universal::hr)*sqr(universal::c))
			),
			constantphysicoChemicalsigma,
			"sigma"
		);


		defineDimensionedConstantWithDefault
		(
			physicoChemical::group,
			physicoChemical::b,
			dimensionedScalar
			(
				"b",
				(universal::h*universal::c / physicoChemical::k)
				/ tnbLib::dimensionedScalar
				(
					"C",
					dimensionSet(0, 0, 0, 0, 0),    // tnbLib::dimless
					4.965114231
				)
			),
			constantphysicoChemicalb,
			"b"
		);


		defineDimensionedConstantWithDefault
		(
			physicoChemical::group,
			physicoChemical::c1,
			dimensionedScalar
			(
				"c1",
				tnbLib::dimensionedScalar
				(
					"C",
					dimensionSet(0, 0, 0, 0, 0),    // tnbLib::dimless,
					mathematical::twoPi
				)
				*universal::h*tnbLib::sqr(universal::c)
			),
			constantphysicoChemicalc1,
			"c1"
		);


		defineDimensionedConstantWithDefault
		(
			physicoChemical::group,
			physicoChemical::c2,
			dimensionedScalar
			(
				"c2",
				universal::h*universal::c / physicoChemical::k
			),
			constantphysicoChemicalc2,
			"c2"
		);


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace constant
} // End namespace tnbLib

// ************************************************************************* //