#include <azizChen.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace pairPotentials
	{

		// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

		defineTypeNameAndDebug(azizChen, 0);

		addToRunTimeSelectionTable
		(
			pairPotential,
			azizChen,
			dictionary
		);


		// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

		azizChen::azizChen
		(
			const word& name,
			const dictionary& azizChen
		)
			:
			pairPotential(name, azizChen),
			azizChenCoeffs_(azizChen.subDict(typeName + "Coeffs")),
			epsilon_(readScalar(azizChenCoeffs_.lookup("epsilon"))),
			rm_(readScalar(azizChenCoeffs_.lookup("rm"))),
			A_(readScalar(azizChenCoeffs_.lookup("A"))),
			alpha_(readScalar(azizChenCoeffs_.lookup("alpha"))),
			C6_(readScalar(azizChenCoeffs_.lookup("C6"))),
			C8_(readScalar(azizChenCoeffs_.lookup("C8"))),
			C10_(readScalar(azizChenCoeffs_.lookup("C10"))),
			D_(readScalar(azizChenCoeffs_.lookup("D"))),
			gamma_(readScalar(azizChenCoeffs_.lookup("gamma")))
		{
			setLookupTables();
		}


		// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

		scalar azizChen::unscaledEnergy(const scalar r) const
		{
			scalar x = r / rm_;

			scalar F = 1.0;

			if (x < D_)
			{
				F = exp(-pow(((D_ / x) - 1.0), 2));
			}

			return
				epsilon_
				* (
					A_ * tnbLib::pow(x, gamma_)*exp(-alpha_ * x)
					- (
					(C6_ / tnbLib::pow(x, 6))
						+ (C8_ / tnbLib::pow(x, 8))
						+ (C10_ / tnbLib::pow(x, 10))
						)
					*F
					);
		}


		bool azizChen::read(const dictionary& azizChen)
		{
			pairPotential::read(azizChen);

			azizChenCoeffs_ = azizChen.subDict(typeName + "Coeffs");

			azizChenCoeffs_.lookup("epsilon") >> epsilon_;
			azizChenCoeffs_.lookup("rm") >> rm_;
			azizChenCoeffs_.lookup("A") >> A_;
			azizChenCoeffs_.lookup("alpha") >> alpha_;
			azizChenCoeffs_.lookup("C6") >> C6_;
			azizChenCoeffs_.lookup("C8") >> C8_;
			azizChenCoeffs_.lookup("C10") >> C10_;
			azizChenCoeffs_.lookup("D") >> D_;
			azizChenCoeffs_.lookup("gamma") >> gamma_;

			return true;
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace pairPotentials
} // End namespace tnbLib

// ************************************************************************* //