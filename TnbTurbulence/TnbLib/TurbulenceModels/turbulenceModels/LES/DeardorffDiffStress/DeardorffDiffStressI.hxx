#pragma once
#include <fvOptions.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace LESModels
	{

		// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

		template<class BasicTurbulenceModel>
		void DeardorffDiffStress<BasicTurbulenceModel>::correctNut()
		{
			this->nut_ = Ck_ * sqrt(this->k())*this->delta();
			this->nut_.correctBoundaryConditions();
			fv::options::New(this->mesh_).correct(this->nut_);

			BasicTurbulenceModel::correctNut();
		}


		// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

		template<class BasicTurbulenceModel>
		DeardorffDiffStress<BasicTurbulenceModel>::DeardorffDiffStress
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
			ReynoldsStress<LESModel<BasicTurbulenceModel>>
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

			Ck_
			(
				dimensioned<scalar>::lookupOrAddToDict
				(
					"Ck",
					this->coeffDict_,
					0.094
				)
			),
			Cm_
			(
				dimensioned<scalar>::lookupOrAddToDict
				(
					"Cm",
					this->coeffDict_,
					4.13
				)
			),
			Ce_
			(
				dimensioned<scalar>::lookupOrAddToDict
				(
					"Ce",
					this->coeffDict_,
					1.05
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
			)
		{
			if (type == typeName)
			{
				this->printCoeffs(type);
				this->boundNormalStress(this->R_);
			}
		}


		// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

		template<class BasicTurbulenceModel>
		bool DeardorffDiffStress<BasicTurbulenceModel>::read()
		{
			if (ReynoldsStress<LESModel<BasicTurbulenceModel>>::read())
			{
				Ck_.readIfPresent(this->coeffDict());
				Cm_.readIfPresent(this->coeffDict());
				Ce_.readIfPresent(this->coeffDict());
				Cs_.readIfPresent(this->coeffDict());

				return true;
			}
			else
			{
				return false;
			}
		}


		template<class BasicTurbulenceModel>
		tmp<volScalarField> DeardorffDiffStress<BasicTurbulenceModel>::epsilon() const
		{
			volScalarField k(this->k());

			return volScalarField::New
			(
				IOobject::groupName("epsilon", this->alphaRhoPhi_.group()),
				this->Ce_*k*sqrt(k) / this->delta()
			);
		}


		template<class BasicTurbulenceModel>
		void DeardorffDiffStress<BasicTurbulenceModel>::correct()
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

			ReynoldsStress<LESModel<BasicTurbulenceModel>>::correct();

			tmp<volTensorField> tgradU(fvc::grad(U));
			const volTensorField& gradU = tgradU();

			volSymmTensorField D(symm(gradU));

			volSymmTensorField P(-twoSymm(R & gradU));

			volScalarField k(this->k());

			tmp<fvSymmTensorMatrix> REqn
			(
				fvm::ddt(alpha, rho, R)
				+ fvm::div(alphaRhoPhi, R)
				- fvm::laplacian(I*this->nu() + Cs_ * (k / this->epsilon())*R, R)
				+ fvm::Sp(Cm_*alpha*rho*sqrt(k) / this->delta(), R)
				==
				alpha * rho*P
				+ (4.0 / 5.0)*alpha*rho*k*D
				- ((2.0 / 3.0)*(1.0 - Cm_ / this->Ce_)*I)*(alpha*rho*this->epsilon())
				+ fvOptions(alpha, rho, R)
			);

			REqn.ref().relax();
			fvOptions.constrain(REqn.ref());
			REqn.ref().solve();
			fvOptions.correct(R);
			this->boundNormalStress(R);

			correctNut();
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace LESModels
} // End namespace tnbLib

// ************************************************************************* //