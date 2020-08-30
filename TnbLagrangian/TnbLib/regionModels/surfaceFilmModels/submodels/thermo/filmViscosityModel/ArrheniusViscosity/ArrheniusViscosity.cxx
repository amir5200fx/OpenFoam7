#include <ArrheniusViscosity.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

			defineTypeNameAndDebug(ArrheniusViscosity, 0);

			addToRunTimeSelectionTable
			(
				filmViscosityModel,
				ArrheniusViscosity,
				dictionary
			);


			// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

			ArrheniusViscosity::ArrheniusViscosity
			(
				surfaceFilmRegionModel& film,
				const dictionary& dict,
				volScalarField& mu
			)
				:
				filmViscosityModel(typeName, film, dict, mu),
				viscosity_(filmViscosityModel::New(film, coeffDict_, mu)),
				k1_("k1", dimTemperature, coeffDict_),
				k2_("k2", dimTemperature, coeffDict_),
				Tref_("Tref", dimTemperature, coeffDict_)
			{}


			// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

			ArrheniusViscosity::~ArrheniusViscosity()
			{}


			// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

			void ArrheniusViscosity::correct
			(
				const volScalarField& p,
				const volScalarField& T
			)
			{
				viscosity_->correct(p, T);
				mu_ *= exp(k1_*((1 / (T + k2_)) - 1 / (Tref_ + k2_)));
				mu_.correctBoundaryConditions();
			}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// ************************************************************************* //