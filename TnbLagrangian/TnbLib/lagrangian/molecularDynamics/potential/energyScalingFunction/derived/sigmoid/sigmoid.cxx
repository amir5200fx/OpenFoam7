#include <sigmoid.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace energyScalingFunctions
	{

		// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

		defineTypeNameAndDebug(sigmoid, 0);

		addToRunTimeSelectionTable
		(
			energyScalingFunction,
			sigmoid,
			dictionary
		);


		// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

		scalar sigmoid::sigmoidScale
		(
			const scalar r,
			const scalar shift,
			const scalar scale
		) const
		{
			return 1.0 / (1.0 + exp(scale * (r - shift)));
		}


		// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

		sigmoid::sigmoid
		(
			const word& name,
			const dictionary& energyScalingFunctionProperties,
			const pairPotential& pairPot
		)
			:
			energyScalingFunction(name, energyScalingFunctionProperties, pairPot),
			sigmoidCoeffs_
			(
				energyScalingFunctionProperties.subDict(typeName + "Coeffs")
			),
			shift_(readScalar(sigmoidCoeffs_.lookup("shift"))),
			scale_(readScalar(sigmoidCoeffs_.lookup("scale")))
		{}


		// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

		void sigmoid::scaleEnergy(scalar& e, const scalar r) const
		{
			e *= sigmoidScale(r, shift_, scale_);
		}


		bool sigmoid::read(const dictionary& energyScalingFunctionProperties)
		{
			energyScalingFunction::read(energyScalingFunctionProperties);

			sigmoidCoeffs_ =
				energyScalingFunctionProperties.subDict(typeName + "Coeffs");

			sigmoidCoeffs_.lookup("shift") >> shift_;
			sigmoidCoeffs_.lookup("scale") >> shift_;

			return true;
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace energyScalingFunctions
} // End namespace tnbLib

// ************************************************************************* //