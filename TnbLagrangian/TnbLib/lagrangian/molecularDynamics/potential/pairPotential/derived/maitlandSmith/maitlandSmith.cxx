#include <maitlandSmith.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace pairPotentials
	{

		// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

		defineTypeNameAndDebug(maitlandSmith, 0);

		addToRunTimeSelectionTable
		(
			pairPotential,
			maitlandSmith,
			dictionary
		);


		// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

		maitlandSmith::maitlandSmith
		(
			const word& name,
			const dictionary& maitlandSmith
		)
			:
			pairPotential(name, maitlandSmith),
			maitlandSmithCoeffs_(maitlandSmith.subDict(typeName + "Coeffs")),
			m_(readScalar(maitlandSmithCoeffs_.lookup("m"))),
			gamma_(readScalar(maitlandSmithCoeffs_.lookup("gamma"))),
			rm_(readScalar(maitlandSmithCoeffs_.lookup("rm"))),
			epsilon_(readScalar(maitlandSmithCoeffs_.lookup("epsilon")))
		{
			setLookupTables();
		}


		// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

		scalar maitlandSmith::unscaledEnergy(const scalar r) const
		{
			scalar nr = (m_ + gamma_ * (r / rm_ - 1.0));

			return epsilon_
				* (
				(6.0 / (nr - 6.0))*tnbLib::pow(r / rm_, -nr)
					- (nr / (nr - 6.0))*tnbLib::pow(r / rm_, -6)
					);
		}


		bool maitlandSmith::read(const dictionary& maitlandSmith)
		{
			pairPotential::read(maitlandSmith);

			maitlandSmithCoeffs_ = maitlandSmith.subDict(typeName + "Coeffs");

			maitlandSmithCoeffs_.lookup("m") >> m_;
			maitlandSmithCoeffs_.lookup("gamma") >> gamma_;
			maitlandSmithCoeffs_.lookup("rm") >> rm_;
			maitlandSmithCoeffs_.lookup("epsilon") >> epsilon_;

			return true;
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace pairPotentials
} // End namespace tnbLib

// ************************************************************************* //