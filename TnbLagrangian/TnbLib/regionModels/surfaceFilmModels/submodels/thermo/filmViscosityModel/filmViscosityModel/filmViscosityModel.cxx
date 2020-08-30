#include <filmViscosityModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

			defineTypeNameAndDebug(filmViscosityModel, 0);
			defineRunTimeSelectionTable(filmViscosityModel, dictionary);

			// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

			filmViscosityModel::filmViscosityModel
			(
				const word& modelType,
				surfaceFilmRegionModel& film,
				const dictionary& dict,
				volScalarField& mu
			)
				:
				filmSubModelBase(film, dict, typeName, modelType),
				mu_(mu)
			{}


			// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

			filmViscosityModel::~filmViscosityModel()
			{}


			// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

			void filmViscosityModel::info(Ostream& os) const
			{}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // end namespace surfaceFilmModels
	} // end namespace regionModels
} // end namespace tnbLib

// ************************************************************************* //