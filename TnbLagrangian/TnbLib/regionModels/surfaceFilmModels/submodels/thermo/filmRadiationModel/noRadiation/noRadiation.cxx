#include <noRadiation.hxx>

#include <volFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

			defineTypeNameAndDebug(noRadiation, 0);

			addToRunTimeSelectionTable
			(
				filmRadiationModel,
				noRadiation,
				dictionary
			);

			// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

			noRadiation::noRadiation
			(
				surfaceFilmRegionModel& film,
				const dictionary& dict
			)
				:
				filmRadiationModel(film)
			{}


			// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

			noRadiation::~noRadiation()
			{}


			// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

			void noRadiation::correct()
			{}


			tmp<volScalarField> noRadiation::Shs()
			{
				return volScalarField::New
				(
					typeName + ":Shs",
					film().regionMesh(),
					dimensionedScalar(dimMass / pow3(dimTime), 0)
				);
			}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// ************************************************************************* //