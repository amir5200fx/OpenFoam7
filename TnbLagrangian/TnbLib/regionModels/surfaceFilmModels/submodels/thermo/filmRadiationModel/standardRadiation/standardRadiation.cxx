#include <standardRadiation.hxx>

#include <volFields.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <zeroGradientFvPatchFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

			defineTypeNameAndDebug(standardRadiation, 0);

			addToRunTimeSelectionTable
			(
				filmRadiationModel,
				standardRadiation,
				dictionary
			);

			// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

			standardRadiation::standardRadiation
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
				),
				qrNet_
				(
					IOobject
					(
						"qrNet",
						film.time().timeName(),
						film.regionMesh(),
						IOobject::NO_READ,
						IOobject::NO_WRITE
					),
					film.regionMesh(),
					dimensionedScalar(dimMass / pow3(dimTime), 0),
					zeroGradientFvPatchScalarField::typeName
				),
				beta_(readScalar(coeffDict_.lookup("beta"))),
				kappaBar_(readScalar(coeffDict_.lookup("kappaBar")))
			{}


			// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

			standardRadiation::~standardRadiation()
			{}


			// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

			void standardRadiation::correct()
			{
				// Transfer qr from primary region
				qinPrimary_.correctBoundaryConditions();
			}


			tmp<volScalarField> standardRadiation::Shs()
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
				const scalarField& delta = filmModel_.delta();
				const scalarField& alpha = filmModel_.alpha();

				Shs = beta_ * qinP*alpha*(1.0 - exp(-kappaBar_ * delta));

				// Update net qr on local region
				qrNet_.primitiveFieldRef() = qinP - Shs;
				qrNet_.correctBoundaryConditions();

				return tShs;
			}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// ************************************************************************* //