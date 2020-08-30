#include <liquidViscosity.hxx>

#include <thermoSingleLayer.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

			defineTypeNameAndDebug(liquidViscosity, 0);

			addToRunTimeSelectionTable
			(
				filmViscosityModel,
				liquidViscosity,
				dictionary
			);

			// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

			liquidViscosity::liquidViscosity
			(
				surfaceFilmRegionModel& film,
				const dictionary& dict,
				volScalarField& mu
			)
				:
				filmViscosityModel(typeName, film, dict, mu)
			{}


			// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

			liquidViscosity::~liquidViscosity()
			{}


			// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

			void liquidViscosity::correct
			(
				const volScalarField& p,
				const volScalarField& T
			)
			{
				const thermoSingleLayer& film = filmType<thermoSingleLayer>();

				mu_ = film.filmThermo().mu();
			}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// ************************************************************************* //