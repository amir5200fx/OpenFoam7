#include <noFilm.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <volFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

			defineTypeNameAndDebug(noFilm, 0);
			addToRunTimeSelectionTable(surfaceFilmModel, noFilm, mesh);

			// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

			noFilm::noFilm
			(
				const word& modelType,
				const fvMesh& mesh,
				const dimensionedVector& g,
				const word& regionType
			)
				:
				surfaceFilmModel(),
				mesh_(mesh)
			{}


			// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

			noFilm::~noFilm()
			{}


			// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

			tnbLib::scalar noFilm::CourantNumber() const
			{
				return 0;
			}


			tmp<volScalarField::Internal> noFilm::Srho() const
			{
				return volScalarField::Internal::New
				(
					"noFilm::Srho",
					mesh_,
					dimensionedScalar(dimMass / dimVolume / dimTime, 0)
				);
			}


			tmp<volScalarField::Internal> noFilm::Srho(const label i) const
			{
				return volScalarField::Internal::New
				(
					"noFilm::Srho(" + tnbLib::name(i) + ")",
					mesh_,
					dimensionedScalar(dimMass / dimVolume / dimTime, 0)
				);
			}


			tmp<volScalarField::Internal> noFilm::Sh() const
			{
				return volScalarField::Internal::New
				(
					"noFilm::Sh",
					mesh_,
					dimensionedScalar(dimEnergy / dimVolume / dimTime, 0)
				);
			}


			void noFilm::evolve()
			{}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// ************************************************************************* //