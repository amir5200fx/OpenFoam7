#include <filmTurbulenceModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

			defineTypeNameAndDebug(filmTurbulenceModel, 0);
			defineRunTimeSelectionTable(filmTurbulenceModel, dictionary);

			// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

			filmTurbulenceModel::filmTurbulenceModel(surfaceFilmRegionModel& film)
				:
				filmSubModelBase(film)
			{}


			filmTurbulenceModel::filmTurbulenceModel
			(
				const word& modelType,
				surfaceFilmRegionModel& film,
				const dictionary& dict
			)
				:
				filmSubModelBase(film, dict, typeName, modelType)
			{}


			// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

			filmTurbulenceModel::~filmTurbulenceModel()
			{}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// ************************************************************************* //