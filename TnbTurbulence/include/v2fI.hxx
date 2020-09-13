#pragma once
#include <fvOptions.hxx>
#include <bound.hxx>

#include <surfaceMesh.hxx>  // added by amir
#include <fvBoundaryMesh.hxx>  // added by amir
#include <fvsPatchFields.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace RASModels
	{

		// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

		template<class BasicTurbulenceModel>
		tmp<volScalarField> v2f<BasicTurbulenceModel>::Ts() const
		{
			return max(k_ / epsilon_, 6.0*sqrt(this->nu() / epsilon_));
		}


		template<class BasicTurbulenceModel>
		tmp<volScalarField> v2f<BasicTurbulenceModel>::Ls() const
		{
			return
				CL_ * max(pow(k_, 1.5)
					/ epsilon_, Ceta_*pow025(pow3(this->nu()) / epsilon_));
		}


		template<class BasicTurbulenceModel>
		void v2f<BasicTurbulenceModel>::correctNut()
		{
			this->nut_ = min(CmuKEps_*sqr(k_) / epsilon_, this->Cmu_*v2_*Ts());
			this->nut_.correctBoundaryConditions();
			fv::options::New(this->mesh_).correct(this->nut_);

			BasicTurbulenceModel::correctNut();
		}


		// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

		template<class BasicTurbulenceModel>
		v2f<BasicTurbulenceModel>::v2f
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
			v2fBase(),

			Cmu_
			(
				dimensioned<scalar>::lookupOrAddToDict
				(
					"Cmu",
					this->coeffDict_,
					0.22
				)
			),
			CmuKEps_
			(
				dimensioned<scalar>::lookupOrAddToDict
				(
					"CmuKEps",
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
					1.4
				)
			),
			C2_
			(
				dimensioned<scalar>::lookupOrAddToDict
				(
					"C2",
					this->coeffDict_,
					0.3
				)
			),
			CL_
			(
				dimensioned<scalar>::lookupOrAddToDict
				(
					"CL",
					this->coeffDict_,
					0.23
				)
			),
			Ceta_
			(
				dimensioned<scalar>::lookupOrAddToDict
				(
					"Ceta",
					this->coeffDict_,
					70.0
				)
			),
			Ceps2_
			(
				dimensioned<scalar>::lookupOrAddToDict
				(
					"Ceps2",
					this->coeffDict_,
					1.9
				)
			),
			Ceps3_
			(
				dimensioned<scalar>::lookupOrAddToDict
				(
					"Ceps3",
					this->coeffDict_,
					-0.33
				)
			),
			sigmaK_
			(
				dimensioned<scalar>::lookupOrAddToDict
				(
					"sigmaK",
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
					IOobject::groupName("k", alphaRhoPhi.group()),
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
					IOobject::groupName("epsilon", alphaRhoPhi.group()),
					this->runTime_.timeName(),
					this->mesh_,
					IOobject::MUST_READ,
					IOobject::AUTO_WRITE
				),
				this->mesh_
			),
			v2_
			(
				IOobject
				(
					IOobject::groupName("v2", alphaRhoPhi.group()),
					this->runTime_.timeName(),
					this->mesh_,
					IOobject::MUST_READ,
					IOobject::AUTO_WRITE
				),
				this->mesh_
			),
			f_
			(
				IOobject
				(
					IOobject::groupName("f", alphaRhoPhi.group()),
					this->runTime_.timeName(),
					this->mesh_,
					IOobject::MUST_READ,
					IOobject::AUTO_WRITE
				),
				this->mesh_
			),
			v2Min_(dimensionedScalar(v2_.dimensions(), small)),
			fMin_(dimensionedScalar(f_.dimensions(), 0))
		{
			bound(k_, this->kMin_);
			bound(epsilon_, this->epsilonMin_);
			bound(v2_, v2Min_);
			bound(f_, fMin_);

			if (type == typeName)
			{
				this->printCoeffs(type);
			}
		}


		// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

		template<class BasicTurbulenceModel>
		bool v2f<BasicTurbulenceModel>::read()
		{
			if (eddyViscosity<RASModel<BasicTurbulenceModel>>::read())
			{
				Cmu_.readIfPresent(this->coeffDict());
				CmuKEps_.readIfPresent(this->coeffDict());
				C1_.readIfPresent(this->coeffDict());
				C2_.readIfPresent(this->coeffDict());
				CL_.readIfPresent(this->coeffDict());
				Ceta_.readIfPresent(this->coeffDict());
				Ceps2_.readIfPresent(this->coeffDict());
				Ceps3_.readIfPresent(this->coeffDict());
				sigmaK_.readIfPresent(this->coeffDict());
				sigmaEps_.readIfPresent(this->coeffDict());

				return true;
			}
			else
			{
				return false;
			}
		}


		template<class BasicTurbulenceModel>
		void v2f<BasicTurbulenceModel>::correct()
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

			// Use N=6 so that f=0 at walls
			const dimensionedScalar N("N", dimless, 6.0);

			const volTensorField gradU(fvc::grad(U));
			const volScalarField S2(2 * magSqr(dev(symm(gradU))));

			const volScalarField G(this->GName(), nut*S2);
			const volScalarField Ts(this->Ts());
			const volScalarField L2(type() + ":L2", sqr(Ls()));
			const volScalarField v2fAlpha
			(
				type() + ":alpha",
				1.0 / Ts * ((C1_ - N)*v2_ - 2.0 / 3.0*k_*(C1_ - 1.0))
			);

			const volScalarField Ceps1
			(
				"Ceps1",
				1.4*(1.0 + 0.05*min(sqrt(k_ / v2_), scalar(100.0)))
			);

			// Update epsilon (and possibly G) at the wall
			epsilon_.boundaryFieldRef().updateCoeffs();

			// Dissipation equation
			tmp<fvScalarMatrix> epsEqn
			(
				fvm::ddt(alpha, rho, epsilon_)
				+ fvm::div(alphaRhoPhi, epsilon_)
				- fvm::laplacian(alpha*rho*DepsilonEff(), epsilon_)
				==
				Ceps1 * alpha*rho*G / Ts
				- fvm::SuSp(((2.0 / 3.0)*Ceps1 + Ceps3_)*alpha*rho*divU, epsilon_)
				- fvm::Sp(Ceps2_*alpha*rho / Ts, epsilon_)
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
				alpha * rho*G
				- fvm::SuSp((2.0 / 3.0)*alpha*rho*divU, k_)
				- fvm::Sp(alpha*rho*epsilon_ / k_, k_)
				+ fvOptions(alpha, rho, k_)
			);

			kEqn.ref().relax();
			fvOptions.constrain(kEqn.ref());
			solve(kEqn);
			fvOptions.correct(k_);
			bound(k_, this->kMin_);


			// Relaxation function equation
			tmp<fvScalarMatrix> fEqn
			(
				-fvm::laplacian(f_)
				==
				-fvm::Sp(1.0 / L2, f_)
				- 1.0 / L2 / k_ * (v2fAlpha - C2_ * G)
			);

			fEqn.ref().relax();
			fvOptions.constrain(fEqn.ref());
			solve(fEqn);
			fvOptions.correct(f_);
			bound(f_, fMin_);


			// Turbulence stress normal to streamlines equation
			tmp<fvScalarMatrix> v2Eqn
			(
				fvm::ddt(alpha, rho, v2_)
				+ fvm::div(alphaRhoPhi, v2_)
				- fvm::laplacian(alpha*rho*DkEff(), v2_)
				==
				alpha * rho*min(k_*f_, C2_*G - v2fAlpha)
				- fvm::Sp(N*alpha*rho*epsilon_ / k_, v2_)
				+ fvOptions(alpha, rho, v2_)
			);

			v2Eqn.ref().relax();
			fvOptions.constrain(v2Eqn.ref());
			solve(v2Eqn);
			fvOptions.correct(v2_);
			bound(v2_, v2Min_);

			correctNut();
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace RASModels
} // End namespace tnbLib

// ************************************************************************* //