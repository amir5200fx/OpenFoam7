#include <lennardJones.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace pairPotentials
	{

		// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

		defineTypeNameAndDebug(lennardJones, 0);

		addToRunTimeSelectionTable
		(
			pairPotential,
			lennardJones,
			dictionary
		);


		// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

		lennardJones::lennardJones
		(
			const word& name,
			const dictionary& pairPotentialProperties
		)
			:
			pairPotential(name, pairPotentialProperties),
			lennardJonesCoeffs_(pairPotentialProperties.subDict(typeName + "Coeffs")),
			sigma_(readScalar(lennardJonesCoeffs_.lookup("sigma"))),
			epsilon_(readScalar(lennardJonesCoeffs_.lookup("epsilon")))
		{
			setLookupTables();
		}


		// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

		scalar lennardJones::unscaledEnergy(const scalar r) const
		{
			// (rIJ/sigma)^-2
			scalar ir2 = (sigma_ / r)*(sigma_ / r);

			// (rIJ/sigma)^-6
			scalar ir6 = ir2 * ir2*ir2;

			return 4.0 * epsilon_*(ir6*(ir6 - 1.0));
		}


		bool lennardJones::read(const dictionary& pairPotentialProperties)
		{
			pairPotential::read(pairPotentialProperties);

			lennardJonesCoeffs_ = pairPotentialProperties.subDict(typeName + "Coeffs");

			lennardJonesCoeffs_.lookup("sigma") >> sigma_;
			lennardJonesCoeffs_.lookup("epsilon") >> epsilon_;

			return true;
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace pairPotentials
} // End namespace tnbLib

// ************************************************************************* //