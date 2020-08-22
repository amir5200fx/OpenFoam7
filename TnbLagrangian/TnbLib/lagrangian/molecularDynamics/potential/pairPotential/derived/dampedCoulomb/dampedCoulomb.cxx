#include <dampedCoulomb.hxx>

#include <mathematicalConstants.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace pairPotentials
	{

		// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

		defineTypeNameAndDebug(dampedCoulomb, 0);

		addToRunTimeSelectionTable
		(
			pairPotential,
			dampedCoulomb,
			dictionary
		);

		scalar dampedCoulomb::oneOverFourPiEps0 =
			1.0 / (4.0*constant::mathematical::pi*8.854187817e-12);


		// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

		dampedCoulomb::dampedCoulomb
		(
			const word& name,
			const dictionary& pairPotentialProperties
		)
			:
			pairPotential(name, pairPotentialProperties),
			dampedCoulombCoeffs_
			(
				pairPotentialProperties.subDict(typeName + "Coeffs")
			),
			alpha_(readScalar(dampedCoulombCoeffs_.lookup("alpha")))
		{
			setLookupTables();
		}


		// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

		scalar dampedCoulomb::unscaledEnergy(const scalar r) const
		{
			return oneOverFourPiEps0 * erfc(alpha_*r) / r;
		}


		bool dampedCoulomb::read(const dictionary& pairPotentialProperties)
		{
			pairPotential::read(pairPotentialProperties);

			dampedCoulombCoeffs_ =
				pairPotentialProperties.subDict(typeName + "Coeffs");

			dampedCoulombCoeffs_.lookup("alpha") >> alpha_;

			return true;
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace pairPotentials
} // End namespace tnbLib

// ************************************************************************* //