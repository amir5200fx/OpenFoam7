#include <exponentialRepulsion.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace pairPotentials
	{

		// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

		defineTypeNameAndDebug(exponentialRepulsion, 0);

		addToRunTimeSelectionTable
		(
			pairPotential,
			exponentialRepulsion,
			dictionary
		);


		// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

		exponentialRepulsion::exponentialRepulsion
		(
			const word& name,
			const dictionary& exponentialRepulsion
		)
			:
			pairPotential(name, exponentialRepulsion),
			exponentialRepulsionCoeffs_
			(
				exponentialRepulsion.subDict(typeName + "Coeffs")
			),
			rm_(readScalar(exponentialRepulsionCoeffs_.lookup("rm"))),
			epsilon_(readScalar(exponentialRepulsionCoeffs_.lookup("epsilon")))
		{
			setLookupTables();
		}


		// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

		scalar exponentialRepulsion::unscaledEnergy(const scalar r) const
		{
			return epsilon_ * exp(-r / rm_);
		}


		bool exponentialRepulsion::read(const dictionary& exponentialRepulsion)
		{
			pairPotential::read(exponentialRepulsion);

			exponentialRepulsionCoeffs_ =
				exponentialRepulsion.subDict(typeName + "Coeffs");

			exponentialRepulsionCoeffs_.lookup("rm") >> rm_;
			exponentialRepulsionCoeffs_.lookup("epsilon") >> epsilon_;

			return true;
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace pairPotentials
} // End namespace tnbLib

// ************************************************************************* //