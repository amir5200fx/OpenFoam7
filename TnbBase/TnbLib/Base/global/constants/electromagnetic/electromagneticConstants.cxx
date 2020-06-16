#include <electromagneticConstants.hxx>

#include <mathematicalConstants.hxx>
#include <universalConstants.hxx>
#include <atomicConstants.hxx>

#include <dimensionedConstants.hxx>

#include <fundamentalConstants.hxx> // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace constant
	{

		const char* const electromagnetic::group = "electromagnetic";


		defineDimensionedConstantWithDefault
		(
			electromagnetic::group,
			electromagnetic::mu0,
			dimensionedScalar
			(
				"mu0",
				dimensionSet(1, 1, -2, 0, 0, -2, 0),
				4.0*mathematical::pi*1e-07
			),
			constantelectromagneticmu0,
			"mu0"
		);


		// Note: cannot use dimless etc. since not guaranteed to be constructed
		defineDimensionedConstantWithDefault
		(
			electromagnetic::group,
			electromagnetic::epsilon0,

			dimensionedScalar
			(
				"epsilon0",
				dimensionedScalar
				(
					"C",
					dimensionSet(0, 0, 0, 0, 0),
					1.0
				)
				/ (electromagnetic::mu0*sqr(universal::c))
			),
			constantelectromagneticepsilon0,
			"epsilon0"
		);


		defineDimensionedConstantWithDefault
		(
			electromagnetic::group,
			electromagnetic::Z0,
			dimensionedScalar
			(
				"Z0",
				electromagnetic::mu0*universal::c
			),
			constantelectromagneticZ0,
			"Z0"
		);


		defineDimensionedConstantWithDefault
		(
			electromagnetic::group,
			electromagnetic::kappa,

			dimensionedScalar
			(
				"kappa",
				dimensionedScalar
				(
					"C",
					dimensionSet(0, 0, 0, 0, 0),
					1.0 / (4.0*mathematical::pi)
				)
				/ electromagnetic::epsilon0
			),

			constantelectromagnetickappa,
			"kappa"
		);


		defineDimensionedConstantWithDefault
		(
			electromagnetic::group,
			electromagnetic::G0,
			dimensionedScalar
			(
				"G0",
				dimensionedScalar("C", dimensionSet(0, 0, 0, 0, 0), 2)
				*sqr(electromagnetic::e)
				/ universal::h
			),
			constantelectromagneticG0,
			"G0"
		);


		defineDimensionedConstantWithDefault
		(
			electromagnetic::group,
			electromagnetic::KJ,
			dimensionedScalar
			(
				"KJ",
				dimensionedScalar("C", dimensionSet(0, 0, 0, 0, 0), 2)
				*electromagnetic::e
				/ universal::h
			),
			constantelectromagneticKJ,
			"KJ"
		);


		defineDimensionedConstantWithDefault
		(
			electromagnetic::group,
			electromagnetic::phi0,
			dimensionedScalar
			(
				"phi0",
				universal::h
				/ (
					dimensionedScalar("C", dimensionSet(0, 0, 0, 0, 0), 2)
					*electromagnetic::e
					)
			),
			constantelectromagneticphi0,
			"phi0"
		);


		defineDimensionedConstantWithDefault
		(
			electromagnetic::group,
			electromagnetic::RK,
			dimensionedScalar
			(
				"RK",
				universal::h / tnbLib::sqr(electromagnetic::e)
			),
			constantelectromagneticRK,
			"RK"
		);


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace constant
} // End namespace tnbLib

// ************************************************************************* //