#pragma once
#include <fvOptions.hxx>
#include <bound.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace RASModels
	{

		// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

		template<class BasicTurbulenceModel>
		tmp<volScalarField> LaunderSharmaKE<BasicTurbulenceModel>::fMu() const
		{
			return exp(-3.4 / sqr(scalar(1) + sqr(k_) / (this->nu()*epsilon_) / 50.0));
		}


		template<class BasicTurbulenceModel>
		tmp<volScalarField> LaunderSharmaKE<BasicTurbulenceModel>::f2() const
		{
			return
				scalar(1)
				- 0.3*exp(-min(sqr(sqr(k_) / (this->nu()*epsilon_)), scalar(50.0)));
		}


		template<class BasicTurbulenceModel>
		void LaunderSharmaKE<BasicTurbulenceModel>::correctNut()
		{
			this->nut_ = Cmu_ * fMu()*sqr(k_) / epsilon_;
			this->nut_.correctBoundaryConditions();
			fv::options::New(this->mesh_).correct(this->nut_);

			BasicTurbulenceModel::correctNut();
		}


		template<class BasicTurbulenceModel>
		tmp<fvScalarMatrix> LaunderSharmaKE<BasicTurbulenceModel>::kSource() const
		{
			return tmp<fvScalarMatrix>
				(
					new fvScalarMatrix
					(
						k_,
						dimVolume*this->rho_.dimensions()*k_.dimensions()
						/ dimTime
					)
					);
		}


		template<class BasicTurbulenceModel>
		tmp<fvScalarMatrix> LaunderSharmaKE<BasicTurbulenceModel>::epsilonSource() const
		{
			return tmp<fvScalarMatrix>
				(
					new fvScalarMatrix
					(
						epsilon_,
						dimVolume*this->rho_.dimensions()*epsilon_.dimensions()
						/ dimTime
					)
					);
		}


		// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

		template<class BasicTurbulenceModel>
		LaunderSharmaKE<BasicTurbulenceModel>::LaunderSharmaKE
		(
			const alphaField& alpha,
			const rhoField& rho,
			const volVectorField& U,
			const surfaceScalarField& alphaRhoPhi,
			const surfaceScalarField& phi,
			const transportModel& transport,
			const word& propertiesName,
			const word& type
		)
			:
			eddyViscosity<RASModel<BasicTurbulenceModel>>
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
					this->coeffDict_,
					0.09
				)
			),
			C1_
			(
				dimensioned<scalar>::lookupOrAddToDict
				(
					"C1",
					this->coeffDict_,
					1.44
				)
			),
			C2_
			(
				dimensioned<scalar>::lookupOrAddToDict
				(
					"C2",
					this->coeffDict_,
					1.92
				)
			),
			C3_
			(
				dimensioned<scalar>::lookupOrAddToDict
				(
					"C3",
					this->coeffDict_,
					0
				)
			),
			sigmak_
			(
				dimensioned<scalar>::lookupOrAddToDict
				(
					"sigmak",
					this->coeffDict_,
					1.0
				)
			),
			sigmaEps_
			(
				dimensioned<scalar>::lookupOrAddToDict
				(
					"sigmaEps",
					this->coeffDict_,
					1.3
				)
			),

			k_
			(
				IOobject
				(
					"k",
					this->runTime_.timeName(),
					this->mesh_,
					IOobject::MUST_READ,
					IOobject::AUTO_WRITE
				),
				this->mesh_
			),

			epsilon_
			(
				IOobject
				(
					"epsilon",
					this->runTime_.timeName(),
					this->mesh_,
					IOobject::MUST_READ,
					IOobject::AUTO_WRITE
				),
				this->mesh_
			)
		{
			bound(k_, this->kMin_);
			bound(epsilon_, this->epsilonMin_);

			if (type == typeName)
			{
				this->printCoeffs(type);
			}
		}


		// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

		template<class BasicTurbulenceModel>
		bool LaunderSharmaKE<BasicTurbulenceModel>::read()
		{
			if (eddyViscosity<RASModel<BasicTurbulenceModel>>::read())
			{
				Cmu_.readIfPresent(this->coeffDict());
				C1_.readIfPresent(this->coeffDict());
				C2_.readIfPresent(this->coeffDict());
				C3_.readIfPresent(this->coeffDict());
				sigmak_.readIfPresent(this->coeffDict());
				sigmaEps_.readIfPresent(this->coeffDict());

				return true;
			}
			else
			{
				return false;
			}
		}


		template<class BasicTurbulenceModel>
		void LaunderSharmaKE<BasicTurbulenceModel>::correct()
		{
			if (!this->turbulence_)
			{
				return;
			}

			// Local references
			const alphaField& alpha = this->alpha_;
			const rhoField& rho = this->rho_;
			const surfaceScalarField& alphaRhoPhi = this->alphaRhoPhi_;
			const volVectorField& U = this->U_;
			volScalarField& nut = this->nut_;
			fv::options& fvOptions(fv::options::New(this->mesh_));

			eddyViscosity<RASModel<BasicTurbulenceModel>>::correct();

			volScalarField divU(fvc::div(fvc::absolute(this->phi(), U)));

			// Calculate parameters and coefficients for Launder-Sharma low-Reynolds
			// number model

			volScalarField E(2.0*this->nu()*nut*fvc::magSqrGradGrad(U));
			volScalarField D(2.0*this->nu()*magSqr(fvc::grad(sqrt(k_))));

			tmp<volTensorField> tgradU = fvc::grad(U);
			volScalarField G(this->GName(), nut*(tgradU() && dev(twoSymm(tgradU()))));
			tgradU.clear();


			// Dissipation equation
			tmp<fvScalarMatrix> epsEqn
			(
				fvm::ddt(alpha, rho, epsilon_)
				+ fvm::div(alphaRhoPhi, epsilon_)
				- fvm::laplacian(alpha*rho*DepsilonEff(), epsilon_)
				==
				C1_ * alpha*rho*G*epsilon_ / k_
				- fvm::SuSp(((2.0 / 3.0)*C1_ - C3_)*alpha*rho*divU, epsilon_)
				- fvm::Sp(C2_*f2()*alpha*rho*epsilon_ / k_, epsilon_)
				+ alpha * rho*E
				+ epsilonSource()
				+ fvOptions(alpha, rho, epsilon_)
			);

			epsEqn.ref().relax();
			fvOptions.constrain(epsEqn.ref());
			epsEqn.ref().boundaryManipulate(epsilon_.boundaryFieldRef());
			solve(epsEqn);
			fvOptions.correct(epsilon_);
			bound(epsilon_, this->epsilonMin_);


			// Turbulent kinetic energy equation
			tmp<fvScalarMatrix> kEqn
			(
				fvm::ddt(alpha, rho, k_)
				+ fvm::div(alphaRhoPhi, k_)
				- fvm::laplacian(alpha*rho*DkEff(), k_)
				==
				alpha * rho*G - fvm::SuSp(2.0 / 3.0*alpha*rho*divU, k_)
				- fvm::Sp(alpha*rho*(epsilon_ + D) / k_, k_)
				+ kSource()
				+ fvOptions(alpha, rho, k_)
			);

			kEqn.ref().relax();
			fvOptions.constrain(kEqn.ref());
			solve(kEqn);
			fvOptions.correct(k_);
			bound(k_, this->kMin_);

			correctNut();
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace RASModels
} // End namespace tnbLib

// ************************************************************************* //