#include <noScaling.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace energyScalingFunctions
	{

		// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

		defineTypeNameAndDebug(noScaling, 0);

		addToRunTimeSelectionTable
		(
			energyScalingFunction,
			noScaling,
			dictionary
		);


		// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

		noScaling::noScaling
		(
			const word& name,
			const dictionary& energyScalingFunctionProperties,
			const pairPotential& pairPot
		)
			:
			energyScalingFunction(name, energyScalingFunctionProperties, pairPot)
		{}


		// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

		void noScaling::scaleEnergy(scalar& e, const scalar r) const
		{}


		bool noScaling::read(const dictionary& energyScalingFunctionProperties)
		{
			energyScalingFunction::read(energyScalingFunctionProperties);

			return true;
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace energyScalingFunctions
} // End namespace tnbLib

// ************************************************************************* //