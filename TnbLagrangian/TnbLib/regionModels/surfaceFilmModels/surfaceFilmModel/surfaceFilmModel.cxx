#include <surfaceFilmModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{

		// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

		defineTypeNameAndDebug(surfaceFilmModel, 0);
		defineRunTimeSelectionTable(surfaceFilmModel, mesh);

		const dimensionedScalar surfaceFilmModel::Tref
		(
			"Tref",
			dimTemperature,
			298.15
		);


		// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

		surfaceFilmModel::surfaceFilmModel()
		{}


		// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

		surfaceFilmModel::~surfaceFilmModel()
		{}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace regionModels
} // End namespace tnbLib

// ************************************************************************* //