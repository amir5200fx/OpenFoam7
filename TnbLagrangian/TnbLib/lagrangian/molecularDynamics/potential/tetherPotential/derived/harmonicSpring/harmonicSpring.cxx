#include <harmonicSpring.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace tetherPotentials
	{

		// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

		defineTypeNameAndDebug(harmonicSpring, 0);

		addToRunTimeSelectionTable
		(
			tetherPotential,
			harmonicSpring,
			dictionary
		);


		// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

		harmonicSpring::harmonicSpring
		(
			const word& name,
			const dictionary& tetherPotentialProperties
		)
			:
			tetherPotential(name, tetherPotentialProperties),
			harmonicSpringCoeffs_
			(
				tetherPotentialProperties.subDict(typeName + "Coeffs")
			),
			springConstant_(readScalar(harmonicSpringCoeffs_.lookup("springConstant")))
		{}


		// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

		scalar harmonicSpring::energy(const vector r) const
		{
			return 0.5*springConstant_*magSqr(r);
		}


		vector harmonicSpring::force(const vector r) const
		{
			return -springConstant_ * r;
		}


		bool harmonicSpring::read(const dictionary& tetherPotentialProperties)
		{
			tetherPotential::read(tetherPotentialProperties);

			harmonicSpringCoeffs_ =
				tetherPotentialProperties.subDict(typeName + "Coeffs");

			harmonicSpringCoeffs_.lookup("springConstant") >> springConstant_;

			return true;
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace tetherPotentials
} // End namespace tnbLib

// ************************************************************************* //