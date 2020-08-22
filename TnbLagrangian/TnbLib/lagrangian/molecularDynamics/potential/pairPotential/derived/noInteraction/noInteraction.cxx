#include <noInteraction.hxx>

#include <token.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace pairPotentials
	{

		// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

		defineTypeNameAndDebug(noInteraction, 0);

		addToRunTimeSelectionTable
		(
			pairPotential,
			noInteraction,
			dictionary
		);


		// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

		noInteraction::noInteraction
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

		scalar noInteraction::unscaledEnergy(const scalar r) const
		{
			return 0.0;
		}


		bool noInteraction::read(const dictionary& pairPotentialProperties)
		{
			pairPotential::read(pairPotentialProperties);

			return true;
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace pairPotentials
} // End namespace tnbLib

// ************************************************************************* //