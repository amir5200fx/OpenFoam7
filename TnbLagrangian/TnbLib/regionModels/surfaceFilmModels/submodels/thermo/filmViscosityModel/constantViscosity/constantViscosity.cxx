#include <constantViscosity.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

			defineTypeNameAndDebug(constantViscosity, 0);

			addToRunTimeSelectionTable
			(
				filmViscosityModel,
				constantViscosity,
				dictionary
			);

			// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

			constantViscosity::constantViscosity
			(
				surfaceFilmRegionModel& film,
				const dictionary& dict,
				volScalarField& mu
			)
				:
				filmViscosityModel(typeName, film, dict, mu),
				mu0_("mu0", dimDynamicViscosity, coeffDict_)
			{
				mu_ == mu0_;
			}


			// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

			constantViscosity::~constantViscosity()
			{}


			// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

			void constantViscosity::correct
			(
				const volScalarField& p,
				const volScalarField& T
			)
			{
				mu_ == mu0_;
			}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// ************************************************************************* //