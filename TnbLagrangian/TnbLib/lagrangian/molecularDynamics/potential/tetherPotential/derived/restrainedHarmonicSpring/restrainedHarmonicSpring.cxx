#include <restrainedHarmonicSpring.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace tetherPotentials
	{

		// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

		defineTypeNameAndDebug(restrainedHarmonicSpring, 0);

		addToRunTimeSelectionTable
		(
			tetherPotential,
			restrainedHarmonicSpring,
			dictionary
		);


		// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

		restrainedHarmonicSpring::restrainedHarmonicSpring
		(
			const word& name,
			const dictionary& tetherPotentialProperties
		)
			:
			tetherPotential(name, tetherPotentialProperties),
			restrainedHarmonicSpringCoeffs_
			(
				tetherPotentialProperties.subDict(typeName + "Coeffs")
			),
			springConstant_
			(
				readScalar(restrainedHarmonicSpringCoeffs_.lookup("springConstant"))
			),
			rR_
			(
				readScalar(restrainedHarmonicSpringCoeffs_.lookup("rR"))
			)
		{}

		// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

		scalar restrainedHarmonicSpring::energy(const vector r) const
		{
			scalar magR = mag(r);

			if (magR < rR_)
			{
				return 0.5 * springConstant_ * magSqr(r);
			}
			else
			{
				return 0.5 * springConstant_ * rR_ * rR_
					+ springConstant_ * rR_ * (magR - rR_);
			}
		}


		vector restrainedHarmonicSpring::force(const vector r) const
		{
			scalar magR = mag(r);

			if (magR < rR_)
			{
				return -springConstant_ * r;
			}
			else
			{
				return -springConstant_ * rR_ * r / magR;
			}
		}


		bool restrainedHarmonicSpring::read
		(
			const dictionary& tetherPotentialProperties
		)
		{
			tetherPotential::read(tetherPotentialProperties);

			restrainedHarmonicSpringCoeffs_ =
				tetherPotentialProperties.subDict(typeName + "Coeffs");

			restrainedHarmonicSpringCoeffs_.lookup("springConstant") >> springConstant_;
			restrainedHarmonicSpringCoeffs_.lookup("rR") >> rR_;

			return true;
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace tetherPotentials
} // End namespace tnbLib

// ************************************************************************* //
