#include <laminar.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvMesh.hxx>
#include <fvMatrices.hxx>
#include <Time.hxx>
#include <volFields.hxx>
#include <fvmSup.hxx>
#include <kinematicSingleLayer.hxx>
#include <extrapolatedCalculatedFvPatchFields.hxx>

#include <filmThermoModel.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

			defineTypeNameAndDebug(laminar, 0);
			addToRunTimeSelectionTable(filmTurbulenceModel, laminar, dictionary);

			// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

			laminar::laminar
			(
				surfaceFilmRegionModel& film,
				const dictionary& dict
			)
				:
				filmTurbulenceModel(type(), film, dict),
				Cf_(readScalar(coeffDict_.lookup("Cf")))
			{}


			// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

			laminar::~laminar()
			{}


			// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

			tmp<volVectorField> laminar::Us() const
			{
				tmp<volVectorField> tUs
				(
					volVectorField::New
					(
						typeName + ":Us",
						filmModel_.regionMesh(),
						dimensionedVector(dimVelocity, Zero),
						extrapolatedCalculatedFvPatchVectorField::typeName
					)
				);

				// apply quadratic profile
				tUs.ref() = tnbLib::sqrt(2.0)*filmModel_.U();
				tUs.ref().correctBoundaryConditions();

				return tUs;
			}


			tmp<volScalarField> laminar::mut() const
			{
				return tmp<volScalarField>
					(
						volScalarField::New
						(
							typeName + ":mut",
							filmModel_.regionMesh(),
							dimensionedScalar(dimMass / dimLength / dimTime, 0)
						)
						);
			}


			void laminar::correct()
			{}


			tmp<fvVectorMatrix> laminar::Su(volVectorField& U) const
			{
				// local reference to film model
				const kinematicSingleLayer& film =
					static_cast<const kinematicSingleLayer&>(filmModel_);

				// local references to film fields
				const volScalarField& mu = film.mu();
				const volVectorField& Uw = film.Uw();
				const volScalarField& delta = film.delta();
				const volVectorField& Up = film.UPrimary();
				const volScalarField& rhop = film.rhoPrimary();

				// employ simple coeff-based model
				volScalarField Cs("Cs", Cf_*rhop*mag(Up - U));
				volScalarField Cw("Cw", mu / ((1.0 / 3.0)*(delta + film.deltaSmall())));
				Cw.min(5000.0);

				return
					(
						-fvm::Sp(Cs, U) + Cs * Up // surface contribution
						- fvm::Sp(Cw, U) + Cw * Uw // wall contribution
						);
			}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// ************************************************************************* //