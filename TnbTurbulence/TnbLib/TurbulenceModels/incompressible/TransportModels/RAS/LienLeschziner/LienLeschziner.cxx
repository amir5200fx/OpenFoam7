#include <LienLeschziner.hxx>

#include <wallDist.hxx>
#include <bound.hxx>
#include <addToRunTimeSelectionTable.hxx>

#include <fvc.hxx>  // added by amir
#include <fvm.hxx>  // added by amir
#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace incompressible
	{
		namespace RASModels
		{

			// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

			defineTypeNameAndDebug(LienLeschziner, 0);
			addToRunTimeSelectionTable(RASModel, LienLeschziner, dictionary);

			// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

			tmp<volScalarField> LienLeschziner::fMu() const
			{
				const volScalarField yStar(sqrt(k_)*y_ / nu());

				return
					(scalar(1) - exp(-Anu_ * yStar))
					/ ((scalar(1) + small) - exp(-Aeps_ * yStar));
			}


			tmp<volScalarField> LienLeschziner::f2() const
			{
				tmp<volScalarField> Rt = sqr(k_) / (nu()*epsilon_);

				return scalar(1) - 0.3*exp(-sqr(Rt));
			}


			tmp<volScalarField> LienLeschziner::E(const volScalarField& f2) const
			{
				const volScalarField yStar(sqrt(k_)*y_ / nu());
				const volScalarField le
				(
					kappa_*y_*((scalar(1) + small) - exp(-Aeps_ * yStar))
				);

				return
					(Ceps2_*pow(Cmu_, 0.75))
					*(f2*sqrt(k_)*epsilon_ / le)*exp(-AE_ * sqr(yStar));
			}


			void LienLeschziner::correctNut()
			{
				nut_ = Cmu_ * fMu()*sqr(k_) / epsilon_;
				nut_.correctBoundaryConditions();
			}


			// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

			LienLeschziner::LienLeschziner
			(
				const geometricOneField& alpha,
				const geometricOneField& rho,
				const volVectorField& U,
				const surfaceScalarField& alphaRhoPhi,
				const surfaceScalarField& phi,
				const transportModel& transport,
				const word& propertiesName,
				const word& type
			)
				:
				eddyViscosity<incompressible::RASModel>
				(
					type,
					alpha,
					rho,
					U,
					alphaRhoPhi,
					phi,
					transport,
					propertiesName
					),

				Ceps1_
				(
					dimensioned<scalar>::lookupOrAddToDict
					(
						"Ceps1",
						coeffDict_,
						1.44
					)
				),
				Ceps2_
				(
					dimensioned<scalar>::lookupOrAddToDict
					(
						"Ceps2",
						coeffDict_,
						1.92
					)
				),
				sigmak_
				(
					dimensioned<scalar>::lookupOrAddToDict
					(
						"sigmak",
						coeffDict_,
						1.0
					)
				),
				sigmaEps_
				(
					dimensioned<scalar>::lookupOrAddToDict
					(
						"sigmaEps",
						coeffDict_,
						1.3
					)
				),
				Cmu_
				(
					dimensioned<scalar>::lookupOrAddToDict
					(
						"Cmu",
						coeffDict_,
						0.09
					)
				),
				kappa_
				(
					dimensioned<scalar>::lookupOrAddToDict
					(
						"kappa",
						coeffDict_,
						0.41
					)
				),
				Anu_
				(
					dimensioned<scalar>::lookupOrAddToDict
					(
						"Anu",
						coeffDict_,
						0.016
					)
				),
				Aeps_
				(
					dimensioned<scalar>::lookupOrAddToDict
					(
						"Aeps",
						coeffDict_,
						0.263
					)
				),
				AE_
				(
					dimensioned<scalar>::lookupOrAddToDict
					(
						"AE",
						coeffDict_,
						0.00222
					)
				),

				k_
				(
					IOobject
					(
						IOobject::groupName("k", alphaRhoPhi.group()),
						runTime_.timeName(),
						mesh_,
						IOobject::MUST_READ,
						IOobject::AUTO_WRITE
					),
					mesh_
				),

				epsilon_
				(
					IOobject
					(
						IOobject::groupName("epsilon", alphaRhoPhi.group()),
						runTime_.timeName(),
						mesh_,
						IOobject::MUST_READ,
						IOobject::AUTO_WRITE
					),
					mesh_
				),

				y_(wallDist::New(mesh_).y())
			{
				bound(k_, kMin_);
				bound(epsilon_, epsilonMin_);

				if (type == typeName)
				{
					printCoeffs(type);
				}
			}


			// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

			bool LienLeschziner::read()
			{
				if (eddyViscosity<incompressible::RASModel>::read())
				{
					Ceps1_.readIfPresent(coeffDict());
					Ceps2_.readIfPresent(coeffDict());
					sigmak_.readIfPresent(coeffDict());
					sigmaEps_.readIfPresent(coeffDict());
					Cmu_.readIfPresent(coeffDict());
					kappa_.readIfPresent(coeffDict());
					Anu_.readIfPresent(coeffDict());
					Aeps_.readIfPresent(coeffDict());
					AE_.readIfPresent(coeffDict());

					return true;
				}
				else
				{
					return false;
				}
			}


			void LienLeschziner::correct()
			{
				if (!turbulence_)
				{
					return;
				}

				eddyViscosity<incompressible::RASModel>::correct();

				tmp<volTensorField> tgradU = fvc::grad(U_);
				volScalarField G
				(
					GName(),
					nut_*(tgradU() && twoSymm(tgradU()))
				);
				tgradU.clear();

				// Update epsilon and G at the wall
				epsilon_.boundaryFieldRef().updateCoeffs();

				const volScalarField f2(this->f2());

				// Dissipation equation
				tmp<fvScalarMatrix> epsEqn
				(
					fvm::ddt(epsilon_)
					+ fvm::div(phi_, epsilon_)
					- fvm::laplacian(DepsilonEff(), epsilon_)
					==
					Ceps1_ * G*epsilon_ / k_
					- fvm::Sp(Ceps2_*f2*epsilon_ / k_, epsilon_)
					+ E(f2)
				);

				epsEqn.ref().relax();
				epsEqn.ref().boundaryManipulate(epsilon_.boundaryFieldRef());
				solve(epsEqn);
				bound(epsilon_, epsilonMin_);


				// Turbulent kinetic energy equation
				tmp<fvScalarMatrix> kEqn
				(
					fvm::ddt(k_)
					+ fvm::div(phi_, k_)
					- fvm::laplacian(DkEff(), k_)
					==
					G
					- fvm::Sp(epsilon_ / k_, k_)
				);

				kEqn.ref().relax();
				solve(kEqn);
				bound(k_, kMin_);

				correctNut();
			}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace RASModels
	} // End namespace incompressible
} // End namespace tnbLib

// ************************************************************************* //