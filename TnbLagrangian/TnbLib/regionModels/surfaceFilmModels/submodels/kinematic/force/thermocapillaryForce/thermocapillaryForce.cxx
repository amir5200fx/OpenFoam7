#include <thermocapillaryForce.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvcGrad.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

			defineTypeNameAndDebug(thermocapillaryForce, 0);
			addToRunTimeSelectionTable(force, thermocapillaryForce, dictionary);

			// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

			thermocapillaryForce::thermocapillaryForce
			(
				surfaceFilmRegionModel& film,
				const dictionary& dict
			)
				:
				force(film)
			{}


			// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

			thermocapillaryForce::~thermocapillaryForce()
			{}


			// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

			tmp<fvVectorMatrix> thermocapillaryForce::correct(volVectorField& U)
			{
				const volScalarField& sigma = filmModel_.sigma();

				tmp<fvVectorMatrix>
					tfvm(new fvVectorMatrix(U, dimForce / dimArea * dimVolume));

				tfvm.ref() += fvc::grad(sigma);

				return tfvm;
			}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// ************************************************************************* //