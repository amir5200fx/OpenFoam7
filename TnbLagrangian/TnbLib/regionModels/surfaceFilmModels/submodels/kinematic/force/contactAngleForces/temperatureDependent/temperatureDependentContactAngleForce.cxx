#include <temperatureDependentContactAngleForce.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

			defineTypeNameAndDebug(temperatureDependentContactAngleForce, 0);
			addToRunTimeSelectionTable
			(
				force,
				temperatureDependentContactAngleForce,
				dictionary
			);


			// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

			temperatureDependentContactAngleForce::temperatureDependentContactAngleForce
			(
				surfaceFilmRegionModel& film,
				const dictionary& dict
			)
				:
				contactAngleForce(typeName, film, dict),
				thetaPtr_(Function1<scalar>::New("theta", coeffDict_))
			{}


			// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

			temperatureDependentContactAngleForce::~temperatureDependentContactAngleForce()
			{}


			// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

			tmp<volScalarField> temperatureDependentContactAngleForce::theta() const
			{
				tmp<volScalarField> ttheta
				(
					volScalarField::New
					(
						typeName + ":theta",
						filmModel_.regionMesh(),
						dimensionedScalar(dimless, 0)
					)
				);

				volScalarField& theta = ttheta.ref();

				const volScalarField& T = filmModel_.T();

				theta.ref().field() = thetaPtr_->value(T());

				forAll(theta.boundaryField(), patchi)
				{
					if (!filmModel_.isCoupledPatch(patchi))
					{
						theta.boundaryFieldRef()[patchi] =
							thetaPtr_->value(T.boundaryField()[patchi]);
					}
				}

				return ttheta;
			}

			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// ************************************************************************* //