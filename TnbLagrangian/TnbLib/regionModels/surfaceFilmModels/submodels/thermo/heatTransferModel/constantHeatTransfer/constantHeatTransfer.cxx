#include <constantHeatTransfer.hxx>

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

			defineTypeNameAndDebug(constantHeatTransfer, 0);

			addToRunTimeSelectionTable
			(
				heatTransferModel,
				constantHeatTransfer,
				dictionary
			);

			// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

			constantHeatTransfer::constantHeatTransfer
			(
				surfaceFilmRegionModel& film,
				const dictionary& dict
			)
				:
				heatTransferModel(typeName, film, dict),
				c0_(readScalar(coeffDict_.lookup("c0")))
			{}


			// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

			constantHeatTransfer::~constantHeatTransfer()
			{}


			// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

			void constantHeatTransfer::correct()
			{}


			tmp<volScalarField> constantHeatTransfer::h() const
			{
				return volScalarField::New
				(
					"htc",
					filmModel_.regionMesh(),
					dimensionedScalar
					(
						dimEnergy / dimTime / sqr(dimLength) / dimTemperature,
						c0_
					)
				);
			}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// ************************************************************************* //