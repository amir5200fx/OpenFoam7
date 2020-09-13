#pragma once
#include <fvOptions.hxx>
#include <wallFvPatch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace RASModels
	{

		// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

		template<class BasicTurbulenceModel>
		void SSG<BasicTurbulenceModel>::correctNut()
		{
			this->nut_ = this->Cmu_*sqr(k_) / epsilon_;
			this->nut_.correctBoundaryConditions();
			fv::options::New(this->mesh_).correct(this->nut_);

			BasicTurbulenceModel::correctNut();
		}


		// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

		template<class BasicTurbulenceModel>
		SSG<BasicTurbulenceModel>::SSG
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
			ReynoldsStress<RASModel<BasicTurbulenceModel>>
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
					3.4
				)
			),
			C1s_
			(
				dimensioned<scalar>::lookupOrAddToDict
				(
					"C1s",
					this->coeffDict_,
					1.8
				)
			),
			C2_
			(
				dimensioned<scalar>::lookupOrAddToDict
				(
					"C2",
					this->coeffDict_,
					4.2
				)
			),
			C3_
			(
				dimensioned<scalar>::lookupOrAddToDict
				(
					"C3",
					this->coeffDict_,
					0.8
				)
			),
			C3s_
			(
				dimensioned<scalar>::lookupOrAddToDict
				(
					"C3s",
					this->coeffDict_,
					1.3
				)
			),
			C4_
			(
				dimensioned<scalar>::lookupOrAddToDict
				(
					"C4",
					this->coeffDict_,
					1.25
				)
			),
			C5_
			(
				dimensioned<scalar>::lookupOrAddToDict
				(
					"C5",
					this->coeffDict_,
					0.4
				)
			),

			Ceps1_
			(
				dimensioned<scalar>::lookupOrAddToDict
				(
					"Ceps1",
					this->coeffDict_,
					1.44
				)
			),
			Ceps2_
			(
				dimensioned<scalar>::lookupOrAddToDict
				(
					"Ceps2",
					this->coeffDict_,
					1.92
				)
			),
			Cs_
			(
				dimensioned<scalar>::lookupOrAddToDict
				(
					"Cs",
					this->coeffDict_,
					0.25
				)
			),
			Ceps_
			(
				dimensioned<scalar>::lookupOrAddToDict
				(
					"Ceps",
					this->coeffDict_,
					0.15
				)
			),

			k_
			(
				IOobject
				(
					"k",
					this->runTime_.timeName(),
					this->mesh_,
					IOobject::NO_READ,
					IOobject::AUTO_WRITE
				),
				0.5*tr(this->R_)
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
			if (type == typeName)
			{
				this->printCoeffs(type);

				this->boundNormalStress(this->R_);
				bound(epsilon_, this->epsilonMin_);
				k_ = 0.5*tr(this->R_);
			}
		}


		// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

		template<class BasicTurbulenceModel>
		bool SSG<BasicTurbulenceModel>::read()
		{
			if (ReynoldsStress<RASModel<BasicTurbulenceModel>>::read())
			{
				Cmu_.readIfPresent(this->coeffDict());
				C1_.readIfPresent(this->coeffDict());
				C1s_.readIfPresent(this->coeffDict());
				C2_.readIfPresent(this->coeffDict());
				C3_.readIfPresent(this->coeffDict());
				C3s_.readIfPresent(this->coeffDict());
				C4_.readIfPresent(this->coeffDict());
				C5_.readIfPresent(this->coeffDict());

				Ceps1_.readIfPresent(this->coeffDict());
				Ceps2_.readIfPresent(this->coeffDict());
				Cs_.readIfPresent(this->coeffDict());
				Ceps_.readIfPresent(this->coeffDict());

				return true;
			}
			else
			{
				return false;
			}
		}


		template<class BasicTurbulenceModel>
		tmp<volSymmTensorField> SSG<BasicTurbulenceModel>::DREff() const
		{
			return volSymmTensorField::New
			(
				"DREff",
				(Cs_*(this->k_ / this->epsilon_))*this->R_ + I * this->nu()
			);
		}


		template<class BasicTurbulenceModel>
		tmp<volSymmTensorField> SSG<BasicTurbulenceModel>::DepsilonEff() const
		{
			return volSymmTensorField::New
			(
				"DepsilonEff",
				(Ceps_*(this->k_ / this->epsilon_))*this->R_ + I * this->nu()
			);
		}


		template<class BasicTurbulenceModel>
		void SSG<BasicTurbulenceModel>::correct()
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
			volSymmTensorField& R = this->R_;
			fv::options& fvOptions(fv::options::New(this->mesh_));

			ReynoldsStress<RASModel<BasicTurbulenceModel>>::correct();

			tmp<volTensorField> tgradU(fvc::grad(U));
			const volTensorField& gradU = tgradU();

			volSymmTensorField P(-twoSymm(R & gradU));
			volScalarField G(this->GName(), 0.5*mag(tr(P)));

			// Update epsilon and G at the wall
			epsilon_.boundaryFieldRef().updateCoeffs();

			// Dissipation equation
			tmp<fvScalarMatrix> epsEqn
			(
				fvm::ddt(alpha, rho, epsilon_)
				+ fvm::div(alphaRhoPhi, epsilon_)
				- fvm::laplacian(alpha*rho*DepsilonEff(), epsilon_)
				==
				Ceps1_ * alpha*rho*G*epsilon_ / k_
				- fvm::Sp(Ceps2_*alpha*rho*epsilon_ / k_, epsilon_)
				+ fvOptions(alpha, rho, epsilon_)
			);

			epsEqn.ref().relax();
			fvOptions.constrain(epsEqn.ref());
			epsEqn.ref().boundaryManipulate(epsilon_.boundaryFieldRef());
			solve(epsEqn);
			fvOptions.correct(epsilon_);
			bound(epsilon_, this->epsilonMin_);


			// Correct the trace of the tensorial production to be consistent
			// with the near-wall generation from the wall-functions
			const fvPatchList& patches = this->mesh_.boundary();

			forAll(patches, patchi)
			{
				const fvPatch& curPatch = patches[patchi];

				if (isA<wallFvPatch>(curPatch))
				{
					forAll(curPatch, facei)
					{
						label celli = curPatch.faceCells()[facei];
						P[celli] *= min
						(
							G[celli] / (0.5*mag(tr(P[celli])) + small),
							1.0
						);
					}
				}
			}

			volSymmTensorField b(dev(R) / (2 * k_));
			volSymmTensorField S(symm(gradU));
			volTensorField Omega(skew(gradU));

			// Reynolds stress equation
			tmp<fvSymmTensorMatrix> REqn
			(
				fvm::ddt(alpha, rho, R)
				+ fvm::div(alphaRhoPhi, R)
				- fvm::laplacian(alpha*rho*DREff(), R)
				+ fvm::Sp(((C1_ / 2)*epsilon_ + (C1s_ / 2)*G)*alpha*rho / k_, R)
				==
				alpha * rho*P
				- ((1.0 / 3.0)*I)*(((2.0 - C1_)*epsilon_ - C1s_ * G)*alpha*rho)
				+ (C2_*(alpha*rho*epsilon_))*dev(innerSqr(b))
				+ alpha * rho*k_
				*(
				(C3_ - C3s_ * mag(b))*dev(S)
					+ C4_ * dev(twoSymm(b&S))
					+ C5_ * twoSymm(b&Omega)
					)
				+ fvOptions(alpha, rho, R)
			);

			REqn.ref().relax();
			fvOptions.constrain(REqn.ref());
			solve(REqn);
			fvOptions.correct(R);

			this->boundNormalStress(R);

			k_ = 0.5*tr(R);

			correctNut();

			// Correct wall shear-stresses when applying wall-functions
			this->correctWallShearStress(R);
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace RASModels
} // End namespace tnbLib

// ************************************************************************* //