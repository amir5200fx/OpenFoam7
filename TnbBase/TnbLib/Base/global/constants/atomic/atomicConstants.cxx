#include <atomicConstants.hxx>

#include <mathematicalConstants.hxx>
#include <universalConstants.hxx>
#include <electromagneticConstants.hxx>
#include <dimensionedConstants.hxx>

#include <fundamentalConstants.hxx> // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace constant
	{

		const char* const atomic::group = "atomic";


		// Note: cannot use dimless etc. since not guaranteed to be constructed
		defineDimensionedConstantWithDefault
		(
			atomic::group,
			atomic::alpha,
			dimensionedScalar
			(
				"alpha",
				sqr(electromagnetic::e)
				/ (
					dimensionedScalar("C", dimensionSet(0, 0, 0, 0, 0), 2.0)
					*electromagnetic::epsilon0
					*universal::h
					*universal::c
					)
			),
			constantatomicalpha,
			"alpha"
		);


		defineDimensionedConstantWithDefault
		(
			atomic::group,
			atomic::Rinf,
			dimensionedScalar
			(
				"Rinf",
				sqr(atomic::alpha)
				*atomic::me
				*universal::c
				/ (
					tnbLib::dimensionedScalar
					(
						"C",
						dimensionSet(0, 0, 0, 0, 0),
						2.0
					)
					*universal::h
					)
			),
			constantatomicRinf,
			"Rinf"
		);


		defineDimensionedConstantWithDefault
		(
			atomic::group,
			atomic::a0,
			dimensionedScalar
			(
				"a0",
				atomic::alpha
				/ (
					tnbLib::dimensionedScalar
					(
						"C",
						dimensionSet(0, 0, 0, 0, 0),
						4.0*mathematical::pi
					)
					*atomic::Rinf
					)
			),
			constantatomica0,
			"a0"
		);


		defineDimensionedConstantWithDefault
		(
			atomic::group,
			atomic::re,
			dimensionedScalar
			(
				"re",
				tnbLib::sqr(electromagnetic::e)
				/ (
					tnbLib::dimensionedScalar
					(
						"C",
						dimensionSet(0, 0, 0, 0, 0),
						4.0*mathematical::pi
					)
					*electromagnetic::epsilon0
					*atomic::me
					*tnbLib::sqr(universal::c)
					)
			),
			constantatomicre,
			"re"
		);


		defineDimensionedConstantWithDefault
		(
			atomic::group,
			atomic::Eh,
			dimensionedScalar
			(
				"Eh",
				tnbLib::dimensionedScalar("C", dimensionSet(0, 0, 0, 0, 0), 2.0)
				*atomic::Rinf*universal::h*universal::c
			),
			constantatomicEh,
			"Eh"
		);


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace constant
} // End namespace tnbLib

// ************************************************************************* //