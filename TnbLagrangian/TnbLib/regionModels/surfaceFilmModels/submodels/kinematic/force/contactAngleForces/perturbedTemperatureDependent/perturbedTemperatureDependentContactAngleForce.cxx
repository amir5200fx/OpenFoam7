#include <perturbedTemperatureDependentContactAngleForce.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

			defineTypeNameAndDebug(perturbedTemperatureDependentContactAngleForce, 0);
			addToRunTimeSelectionTable
			(
				force,
				perturbedTemperatureDependentContactAngleForce,
				dictionary
			);


			// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

			perturbedTemperatureDependentContactAngleForce::
				perturbedTemperatureDependentContactAngleForce
				(
					surfaceFilmRegionModel& film,
					const dictionary& dict
				)
				:
				contactAngleForce(typeName, film, dict),
				thetaPtr_(Function1<scalar>::New("theta", coeffDict_)),
				rndGen_(label(0)),
				distribution_
				(
					distributionModel::New
					(
						coeffDict_.subDict("distribution"),
						rndGen_
					)
				)
			{}


			// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

			perturbedTemperatureDependentContactAngleForce::
				~perturbedTemperatureDependentContactAngleForce()
			{}


			// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

			tmp<volScalarField>
				perturbedTemperatureDependentContactAngleForce::theta() const
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
				volScalarField::Internal& thetai = theta.ref();

				const volScalarField& T = filmModel_.T();

				// Initialize with the function of temperature
				thetai.field() = thetaPtr_->value(T());

				// Add the stochastic perturbation
				forAll(thetai, celli)
				{
					thetai[celli] += distribution_->sample();
				}

				forAll(theta.boundaryField(), patchi)
				{
					if (!filmModel_.isCoupledPatch(patchi))
					{
						fvPatchField<scalar>& thetaf = theta.boundaryFieldRef()[patchi];

						// Initialize with the function of temperature
						thetaf = thetaPtr_->value(T.boundaryField()[patchi]);

						// Add the stochastic perturbation
						forAll(thetaf, facei)
						{
							thetaf[facei] += distribution_->sample();
						}
					}
				}

				return ttheta;
			}

			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// ************************************************************************* //