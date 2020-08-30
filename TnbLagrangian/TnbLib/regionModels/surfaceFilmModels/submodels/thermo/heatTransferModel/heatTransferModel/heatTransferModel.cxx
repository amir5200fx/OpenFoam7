#include <heatTransferModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

			defineTypeNameAndDebug(heatTransferModel, 0);
			defineRunTimeSelectionTable(heatTransferModel, dictionary);

			// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

			heatTransferModel::heatTransferModel
			(
				surfaceFilmRegionModel& film
			)
				:
				filmSubModelBase(film)
			{}


			heatTransferModel::heatTransferModel
			(
				const word& modelType,
				surfaceFilmRegionModel& film,
				const dictionary& dict
			)
				:
				filmSubModelBase(film, dict, typeName, modelType)
			{}


			// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

			heatTransferModel::~heatTransferModel()
			{}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// ************************************************************************* //