#include <primaryRadiation.hxx>

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

			defineTypeNameAndDebug(primaryRadiation, 0);

			addToRunTimeSelectionTable
			(
				filmRadiationModel,
				primaryRadiation,
				dictionary
			);

			// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

			primaryRadiation::primaryRadiation
			(
				surfaceFilmRegionModel& film,
				const dictionary& dict
			)
				:
				filmRadiationModel(typeName, film, dict),
				qinPrimary_
				(
					IOobject
					(
						"qin", // same name as qin on primary region to enable mapping
						film.time().timeName(),
						film.regionMesh(),
						IOobject::NO_READ,
						IOobject::NO_WRITE
					),
					film.regionMesh(),
					dimensionedScalar(dimMass / pow3(dimTime), 0),
					film.mappedPushedFieldPatchTypes<scalar>()
				)
			{}


			// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

			primaryRadiation::~primaryRadiation()
			{}


			// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

			void primaryRadiation::correct()
			{
				// Transfer qin from primary region
				qinPrimary_.correctBoundaryConditions();
			}


			tmp<volScalarField> primaryRadiation::Shs()
			{
				tmp<volScalarField> tShs
				(
					volScalarField::New
					(
						typeName + ":Shs",
						film().regionMesh(),
						dimensionedScalar(dimMass / pow3(dimTime), 0)
					)
				);

				scalarField& Shs = tShs.ref();
				const scalarField& qinP = qinPrimary_;
				const scalarField& alpha = filmModel_.alpha();

				Shs = qinP * alpha;

				return tShs;
			}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// ************************************************************************* //