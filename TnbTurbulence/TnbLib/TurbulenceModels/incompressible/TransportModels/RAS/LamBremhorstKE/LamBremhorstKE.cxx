#include <LamBremhorstKE.hxx>

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

			defineTypeNameAndDebug(LamBremhorstKE, 0);
			addToRunTimeSelectionTable(RASModel, LamBremhorstKE, dictionary);

			// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

			tmp<volScalarField> LamBremhorstKE::Rt() const
			{
				return sqr(k_) / (nu()*epsilon_);
			}


			tmp<volScalarField> LamBremhorstKE::fMu(const volScalarField& Rt) const
			{
				tmp<volScalarField> Ry(sqrt(k_)*y_ / nu());
				return sqr(scalar(1) - exp(-0.0165*Ry))*(scalar(1) + 20.5 / (Rt + small));
			}


			tmp<volScalarField> LamBremhorstKE::f1(const volScalarField& fMu) const
			{
				return scalar(1) + pow3(0.05 / (fMu + small));
			}


			tmp<volScalarField> LamBremhorstKE::f2(const volScalarField& Rt) const
			{
				return scalar(1) - exp(-sqr(Rt));
			}


			void LamBremhorstKE::correctNut(const volScalarField& fMu)
			{
				nut_ = Cmu_ * fMu*sqr(k_) / epsilon_;
				nut_.correctBoundaryConditions();
			}


			// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

			void LamBremhorstKE::correctNut()
			{
				correctNut(fMu(Rt()));
			}


			// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

			LamBremhorstKE::LamBremhorstKE
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

				Cmu_
				(
					dimensioned<scalar>::lookupOrAddToDict
					(
						"Cmu",
						coeffDict_,
						0.09
					)
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
				sigmaEps_
				(
					dimensioned<scalar>::lookupOrAddToDict
					(
						"alphaEps",
						coeffDict_,
						1.3
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

			bool LamBremhorstKE::read()
			{
				if (eddyViscosity<incompressible::RASModel>::read())
				{
					Cmu_.readIfPresent(coeffDict());
					Ceps1_.readIfPresent(coeffDict());
					Ceps2_.readIfPresent(coeffDict());
					sigmaEps_.readIfPresent(coeffDict());

					return true;
				}
				else
				{
					return false;
				}
			}


			void LamBremhorstKE::correct()
			{
				if (!turbulence_)
				{
					return;
				}

				eddyViscosity<incompressible::RASModel>::correct();

				tmp<volTensorField> tgradU = fvc::grad(U_);
				volScalarField G(GName(), nut_*(twoSymm(tgradU()) && tgradU()));
				tgradU.clear();

				// Update epsilon and G at the wall
				epsilon_.boundaryFieldRef().updateCoeffs();

				const volScalarField Rt(this->Rt());
				const volScalarField fMu(this->fMu(Rt));

				// Dissipation equation
				tmp<fvScalarMatrix> epsEqn
				(
					fvm::ddt(epsilon_)
					+ fvm::div(phi_, epsilon_)
					- fvm::laplacian(DepsilonEff(), epsilon_)
					==
					Ceps1_ * f1(fMu)*G*epsilon_ / k_
					- fvm::Sp(Ceps2_*f2(Rt)*epsilon_ / k_, epsilon_)
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
					G - fvm::Sp(epsilon_ / k_, k_)
				);

				kEqn.ref().relax();
				solve(kEqn);
				bound(k_, kMin_);

				correctNut(fMu);
			}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace RASModels
	} // End namespace incompressible
} // End namespace tnbLib

// ************************************************************************* //