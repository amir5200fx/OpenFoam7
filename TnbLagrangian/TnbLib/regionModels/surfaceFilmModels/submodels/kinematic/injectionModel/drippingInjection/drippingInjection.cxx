#include <drippingInjection.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <fvMesh.hxx>
#include <Time.hxx>
#include <mathematicalConstants.hxx>
#include <Random.hxx>
#include <volFields.hxx>
#include <kinematicSingleLayer.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

			defineTypeNameAndDebug(drippingInjection, 0);
			addToRunTimeSelectionTable(injectionModel, drippingInjection, dictionary);

			// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

			drippingInjection::drippingInjection
			(
				surfaceFilmRegionModel& film,
				const dictionary& dict
			)
				:
				injectionModel(type(), film, dict),
				deltaStable_(readScalar(coeffDict_.lookup("deltaStable"))),
				particlesPerParcel_(readScalar(coeffDict_.lookup("particlesPerParcel"))),
				rndGen_(label(0)),
				parcelDistribution_
				(
					distributionModel::New
					(
						coeffDict_.subDict("parcelDistribution"),
						rndGen_
					)
				),
				diameter_(film.regionMesh().nCells(), -1.0)
			{}


			// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

			drippingInjection::~drippingInjection()
			{}


			// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

			void drippingInjection::correct
			(
				scalarField& availableMass,
				scalarField& massToInject,
				scalarField& diameterToInject
			)
			{
				const kinematicSingleLayer& film =
					refCast<const kinematicSingleLayer>(this->film());

				const scalar pi = constant::mathematical::pi;

				// calculate available dripping mass
				tmp<volScalarField> tgNorm(film.gNorm());
				const scalarField& gNorm = tgNorm();
				const scalarField& magSf = film.magSf();

				const scalarField& delta = film.delta();
				const scalarField& rho = film.rho();

				scalarField massDrip(film.regionMesh().nCells(), 0.0);

				forAll(gNorm, i)
				{
					if (gNorm[i] > small)
					{
						const scalar ddelta = max(0.0, delta[i] - deltaStable_);
						massDrip[i] +=
							min(availableMass[i], max(0.0, ddelta*rho[i] * magSf[i]));
					}
				}


				// Collect the data to be transferred
				forAll(massDrip, celli)
				{
					if (massDrip[celli] > 0)
					{
						// set new particle diameter if not already set
						if (diameter_[celli] < 0)
						{
							diameter_[celli] = parcelDistribution_->sample();
						}

						scalar& diam = diameter_[celli];
						scalar rhoc = rho[celli];
						scalar minMass = particlesPerParcel_ * rhoc*pi / 6 * pow3(diam);

						if (massDrip[celli] > minMass)
						{
							// All drip mass can be injected
							massToInject[celli] += massDrip[celli];
							availableMass[celli] -= massDrip[celli];

							// Set particle diameter
							diameterToInject[celli] = diam;

							// Retrieve new particle diameter sample
							diam = parcelDistribution_->sample();

							addToInjectedMass(massDrip[celli]);
						}
						else
						{
							// Particle mass below minimum threshold - cannot be injected
							massToInject[celli] = 0.0;
							diameterToInject[celli] = 0.0;
						}
					}
					else
					{
						massToInject[celli] = 0.0;
						diameterToInject[celli] = 0.0;
					}
				}

				injectionModel::correct();
			}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// ************************************************************************* //