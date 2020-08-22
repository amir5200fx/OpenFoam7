#include <shiftedForce.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace energyScalingFunctions
	{

		// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

		defineTypeNameAndDebug(shiftedForce, 0);

		addToRunTimeSelectionTable
		(
			energyScalingFunction,
			shiftedForce,
			dictionary
		);


		// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

		shiftedForce::shiftedForce
		(
			const word& name,
			const dictionary& energyScalingFunctionProperties,
			const pairPotential& pairPot
		)
			:
			energyScalingFunction(name, energyScalingFunctionProperties, pairPot),
			rCut_(pairPot.rCut()),
			e_at_rCut_(pairPot.unscaledEnergy(rCut_)),
			de_dr_at_rCut_(pairPot.energyDerivative(rCut_, false))
		{}


		// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

		void shiftedForce::scaleEnergy(scalar& e, const scalar r) const
		{
			e -= (e_at_rCut_ + de_dr_at_rCut_ * (r - rCut_));
		}


		bool shiftedForce::read(const dictionary& energyScalingFunctionProperties)
		{
			energyScalingFunction::read(energyScalingFunctionProperties);

			return true;
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace energyScalingFunctions
} // End namespace tnbLib

// ************************************************************************* //