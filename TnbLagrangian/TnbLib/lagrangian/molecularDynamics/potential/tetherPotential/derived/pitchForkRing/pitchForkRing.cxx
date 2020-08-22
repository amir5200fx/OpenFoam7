#include <pitchForkRing.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace tetherPotentials
	{

		// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

		defineTypeNameAndDebug(pitchForkRing, 0);

		addToRunTimeSelectionTable
		(
			tetherPotential,
			pitchForkRing,
			dictionary
		);


		// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

		pitchForkRing::pitchForkRing
		(
			const word& name,
			const dictionary& tetherPotentialProperties
		)
			:
			tetherPotential(name, tetherPotentialProperties),
			pitchForkRingCoeffs_
			(
				tetherPotentialProperties.subDict(typeName + "Coeffs")
			),
			mu_(readScalar(pitchForkRingCoeffs_.lookup("mu"))),
			alpha_(readScalar(pitchForkRingCoeffs_.lookup("alpha"))),
			rOrbit_(readScalar(pitchForkRingCoeffs_.lookup("rOrbit")))
		{}


		// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

		scalar pitchForkRing::energy(const vector r) const
		{
			scalar p = sqrt(r.x()*r.x() + r.y()*r.y());

			scalar pMinusRSqr = sqr(p - rOrbit_);

			return
				-0.5 * mu_ * pMinusRSqr
				+ 0.25 * pMinusRSqr * pMinusRSqr
				+ 0.5 * alpha_ * r.z() * r.z();
		}


		vector pitchForkRing::force(const vector r) const
		{
			scalar p = sqrt(r.x()*r.x() + r.y()*r.y());

			scalar pMinusR = (p - rOrbit_);

			return vector
			(
				(mu_ - sqr(pMinusR)) * pMinusR * r.x() / (p + vSmall),
				(mu_ - sqr(pMinusR)) * pMinusR * r.y() / (p + vSmall),
				-alpha_ * r.z()
			);
		}


		bool pitchForkRing::read(const dictionary& tetherPotentialProperties)
		{
			tetherPotential::read(tetherPotentialProperties);

			pitchForkRingCoeffs_ =
				tetherPotentialProperties.subDict(typeName + "Coeffs");

			pitchForkRingCoeffs_.lookup("mu") >> mu_;
			pitchForkRingCoeffs_.lookup("alpha") >> alpha_;
			pitchForkRingCoeffs_.lookup("rOrbit") >> rOrbit_;

			return true;
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace tetherPotentials
} // End namespace tnbLib

// ************************************************************************* //