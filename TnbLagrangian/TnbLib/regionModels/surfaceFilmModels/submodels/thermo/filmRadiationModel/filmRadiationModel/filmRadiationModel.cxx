#include <filmRadiationModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

			defineTypeNameAndDebug(filmRadiationModel, 0);
			defineRunTimeSelectionTable(filmRadiationModel, dictionary);

			// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

			filmRadiationModel::filmRadiationModel(surfaceFilmRegionModel& film)
				:
				filmSubModelBase(film)
			{}


			filmRadiationModel::filmRadiationModel
			(
				const word& modelType,
				surfaceFilmRegionModel& film,
				const dictionary& dict
			)
				:
				filmSubModelBase(film, dict, typeName, modelType)
			{}


			// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

			filmRadiationModel::~filmRadiationModel()
			{}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// ************************************************************************* //