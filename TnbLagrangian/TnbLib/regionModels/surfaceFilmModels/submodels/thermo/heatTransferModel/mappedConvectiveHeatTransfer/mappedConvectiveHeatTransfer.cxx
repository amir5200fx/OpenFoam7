#include <mappedConvectiveHeatTransfer.hxx>

#include <zeroGradientFvPatchFields.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <kinematicSingleLayer.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

			defineTypeNameAndDebug(mappedConvectiveHeatTransfer, 0);

			addToRunTimeSelectionTable
			(
				heatTransferModel,
				mappedConvectiveHeatTransfer,
				dictionary
			);

			// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

			mappedConvectiveHeatTransfer::mappedConvectiveHeatTransfer
			(
				surfaceFilmRegionModel& film,
				const dictionary& dict
			)
				:
				heatTransferModel(film),
				htcConvPrimary_
				(
					IOobject
					(
						"htcConv",
						film.time().timeName(),
						film.primaryMesh(),
						IOobject::MUST_READ,
						IOobject::AUTO_WRITE
					),
					film.primaryMesh()
				),
				htcConvFilm_
				(
					IOobject
					(
						htcConvPrimary_.name(), // must have same name as above for mapping
						film.time().timeName(),
						film.regionMesh(),
						IOobject::NO_READ,
						IOobject::NO_WRITE
					),
					film.regionMesh(),
					dimensionedScalar(dimMass / pow3(dimTime) / dimTemperature, 0),
					film.mappedPushedFieldPatchTypes<scalar>()
				)
			{
				// Update the primary-side convective heat transfer coefficient
				htcConvPrimary_.correctBoundaryConditions();

				// Pull the data from the primary region via direct mapped BCs
				htcConvFilm_.correctBoundaryConditions();
			}


			// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

			mappedConvectiveHeatTransfer::~mappedConvectiveHeatTransfer()
			{}


			// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

			void mappedConvectiveHeatTransfer::correct()
			{
				// Update the primary-side convective heat transfer coefficient
				htcConvPrimary_.correctBoundaryConditions();

				// Pull the data from the primary region via direct mapped BCs
				htcConvFilm_.correctBoundaryConditions();
			}


			tmp<volScalarField> mappedConvectiveHeatTransfer::h() const
			{
				return htcConvFilm_;
			}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// ************************************************************************* //