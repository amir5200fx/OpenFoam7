#include <filmThermoModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

			defineTypeNameAndDebug(filmThermoModel, 0);
			defineRunTimeSelectionTable(filmThermoModel, dictionary);

			// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

			filmThermoModel::filmThermoModel
			(
				surfaceFilmRegionModel& film
			)
				:
				filmSubModelBase(film)
			{}


			filmThermoModel::filmThermoModel
			(
				const word& modelType,
				surfaceFilmRegionModel& film,
				const dictionary& dict
			)
				:
				filmSubModelBase(film, dict, typeName, modelType)
			{}


			// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

			filmThermoModel::~filmThermoModel()
			{}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// ************************************************************************* //