#include <thixotropicViscosity.hxx>

#include <kinematicSingleLayer.hxx>
#include <addToRunTimeSelectionTable.hxx>


#include <fvmDdt.hxx>
#include <fvmDiv.hxx>
#include <fvcDiv.hxx>
#include <fvmSup.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

			defineTypeNameAndDebug(thixotropicViscosity, 0);

			addToRunTimeSelectionTable
			(
				filmViscosityModel,
				thixotropicViscosity,
				dictionary
			);


			// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

			thixotropicViscosity::thixotropicViscosity
			(
				surfaceFilmRegionModel& film,
				const dictionary& dict,
				volScalarField& mu
			)
				:
				filmViscosityModel(typeName, film, dict, mu),
				a_("a", dimless / dimTime, coeffDict_),
				b_("b", dimless, coeffDict_),
				d_("d", dimless, coeffDict_),
				c_("c", pow(dimTime, d_.value() - scalar(1)), coeffDict_),
				mu0_("mu0", dimPressure*dimTime, coeffDict_),
				muInf_("muInf", mu0_.dimensions(), coeffDict_),
				K_(1 - sqrt(muInf_ / mu0_)),
				lambda_
				(
					IOobject
					(
						typeName + ":lambda",
						film.regionMesh().time().timeName(),
						film.regionMesh(),
						IOobject::MUST_READ,
						IOobject::AUTO_WRITE
					),
					film.regionMesh()
				)
			{
				lambda_.min(1);
				lambda_.max(0);

				// Initialise viscosity to inf value because it cannot be evaluated yet
				mu_ = muInf_;
				mu_.correctBoundaryConditions();
			}


			// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

			thixotropicViscosity::~thixotropicViscosity()
			{}


			// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

			void thixotropicViscosity::correct
			(
				const volScalarField& p,
				const volScalarField& T
			)
			{
				const kinematicSingleLayer& film = filmType<kinematicSingleLayer>();

				const volVectorField& U = film.U();
				const volVectorField& Uw = film.Uw();
				const volScalarField& delta = film.delta();
				const volScalarField& deltaRho = film.deltaRho();
				const surfaceScalarField& phi = film.phi();
				const volScalarField& alpha = film.alpha();
				const Time& runTime = this->film().regionMesh().time();

				// Shear rate
				const volScalarField gDot
				(
					"gDot",
					alpha*mag(U - Uw) / (delta + film.deltaSmall())
				);

				if (debug && runTime.writeTime())
				{
					gDot.write();
				}

				const dimensionedScalar deltaRho0
				(
					"deltaRho0",
					deltaRho.dimensions(),
					rootVSmall
				);

				const surfaceScalarField phiU(phi / fvc::interpolate(deltaRho + deltaRho0));

				const dimensionedScalar c0("c0", dimless / dimTime, rootVSmall);
				const volScalarField coeff("coeff", -c_ * pow(gDot, d_) + c0);

				fvScalarMatrix lambdaEqn
				(
					fvm::ddt(lambda_)
					+ fvm::div(phiU, lambda_)
					- fvm::Sp(fvc::div(phiU), lambda_)
					==
					a_ * pow((1 - lambda_), b_)
					+ fvm::SuSp(coeff, lambda_)

					// Include the effect of the impinging droplets added with lambda = 0
					- fvm::Sp
					(
						max
						(
							-film.rhoSp(),
							dimensionedScalar(film.rhoSp().dimensions(), 0)
						) / (deltaRho + deltaRho0),
						lambda_
					)
				);

				lambdaEqn.relax();
				lambdaEqn.solve();

				lambda_.min(1);
				lambda_.max(0);

				mu_ = muInf_ / (sqr(1 - K_ * lambda_) + rootVSmall);
				mu_.correctBoundaryConditions();
			}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// ************************************************************************* //