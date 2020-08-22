#include <coulomb.hxx>

#include <mathematicalConstants.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace pairPotentials
	{

		// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

		defineTypeNameAndDebug(coulomb, 0);

		addToRunTimeSelectionTable
		(
			pairPotential,
			coulomb,
			dictionary
		);

		scalar coulomb::oneOverFourPiEps0 =
			1.0 / (4.0*constant::mathematical::pi*8.854187817e-12);


		// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

		coulomb::coulomb
		(
			const word& name,
			const dictionary& pairPotentialProperties
		)
			:
			pairPotential(name, pairPotentialProperties)
		{
			setLookupTables();
		}


		// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

		scalar coulomb::unscaledEnergy(const scalar r) const
		{
			return oneOverFourPiEps0 / r;
		}


		bool coulomb::read(const dictionary& pairPotentialProperties)
		{
			pairPotential::read(pairPotentialProperties);

			return true;
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace pairPotentials
} // End namespace tnbLib

// ************************************************************************* //