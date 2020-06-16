#include <universalConstants.hxx>


#include <mathematicalConstants.hxx>
#include <dimensionedConstants.hxx>

#include <fundamentalConstants.hxx> // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace constant
	{

		const char* const universal::group = "universal";


		// Note: cannot use dimless etc. since not guaranteed to be constructed
		defineDimensionedConstantWithDefault
		(
			"universal",
			universal::hr,
			dimensionedScalar
			(
				"hr",
				universal::h
				/ (
					dimensionedScalar
					(
						"C",
						dimensionSet(0, 0, 0, 0, 0),//dimless
						mathematical::twoPi
					)
					)
			),
			constantuniversalhr,
			"hr"
		);


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace constant
} // End namespace tnbLib

// ************************************************************************* //