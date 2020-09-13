#pragma once
#include <fvOptions.hxx>
#include <bound.hxx>

#include <surfaceMesh.hxx>  // added by amir
#include <fvBoundaryMesh.hxx> // added by amir
#include <fvsPatchFields.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace RASModels
	{

		// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

		template<class BasicTurbulenceModel>
		void kEpsilon<BasicTurbulenceModel>::correctNut()
		{
			this->nut_ = Cmu_ * sqr(k_) / epsilon_;
			this->nut_.correctBoundaryConditions();
			fv::options::New(this->mesh_).correct(this->nut_);

			BasicTurbulenceModel::correctNut();
		}


		template<class BasicTurbulenceModel>
		tmp<fvScalarMatrix> kEpsilon<BasicTurbulenceModel>::kSource() const
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
		tmp<fvScalarMatrix> kEpsilon<BasicTurbulenceModel>::epsilonSource() const
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
		kEpsilon<BasicTurbulenceModel>::kEpsilon
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
		bool kEpsilon<BasicTurbulenceModel>::read()
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
		void kEpsilon<BasicTurbulenceModel>::correct()
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

			volScalarField::Internal divU
			(
				fvc::div(fvc::absolute(this->phi(), U))().v()
			);

			tmp<volTensorField> tgradU = fvc::grad(U);
			volScalarField::Internal G
			(
				this->GName(),
				nut.v()*(dev(twoSymm(tgradU().v())) && tgradU().v())
			);
			tgradU.clear();

			// Update epsilon and G at the wall
			epsilon_.boundaryFieldRef().updateCoeffs();

			// Dissipation equation
			tmp<fvScalarMatrix> epsEqn
			(
				fvm::ddt(alpha, rho, epsilon_)
				+ fvm::div(alphaRhoPhi, epsilon_)
				- fvm::laplacian(alpha*rho*DepsilonEff(), epsilon_)
				==
				C1_ * alpha()*rho()*G*epsilon_() / k_()
				- fvm::SuSp(((2.0 / 3.0)*C1_ - C3_)*alpha()*rho()*divU, epsilon_)
				- fvm::Sp(C2_*alpha()*rho()*epsilon_() / k_(), epsilon_)
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
				alpha()*rho()*G
				- fvm::SuSp((2.0 / 3.0)*alpha()*rho()*divU, k_)
				- fvm::Sp(alpha()*rho()*epsilon_() / k_(), k_)
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