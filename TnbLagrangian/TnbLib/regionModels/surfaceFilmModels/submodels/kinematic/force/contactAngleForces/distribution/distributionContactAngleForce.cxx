#include <distributionContactAngleForce.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

			defineTypeNameAndDebug(distributionContactAngleForce, 0);
			addToRunTimeSelectionTable(force, distributionContactAngleForce, dictionary);


			// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

			distributionContactAngleForce::distributionContactAngleForce
			(
				surfaceFilmRegionModel& film,
				const dictionary& dict
			)
				:
				contactAngleForce(typeName, film, dict),
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

			distributionContactAngleForce::~distributionContactAngleForce()
			{}


			// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

			tmp<volScalarField> distributionContactAngleForce::theta() const
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

				forAll(thetai, celli)
				{
					thetai[celli] = distribution_->sample();
				}

				forAll(theta.boundaryField(), patchi)
				{
					if (!filmModel_.isCoupledPatch(patchi))
					{
						fvPatchField<scalar>& thetaf = theta.boundaryFieldRef()[patchi];

						forAll(thetaf, facei)
						{
							thetaf[facei] = distribution_->sample();
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