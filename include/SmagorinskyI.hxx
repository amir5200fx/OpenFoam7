#pragma once
#include <fvOptions.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace LESModels
	{

		// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

		template<class BasicTurbulenceModel>
		tmp<volScalarField> Smagorinsky<BasicTurbulenceModel>::k
		(
			const tmp<volTensorField>& gradU
		) const
		{
			volSymmTensorField D(symm(gradU));

			volScalarField a(this->Ce_ / this->delta());
			volScalarField b((2.0 / 3.0)*tr(D));
			volScalarField c(2 * Ck_*this->delta()*(dev(D) && D));

			return volScalarField::New
			(
				IOobject::groupName("k", this->alphaRhoPhi_.group()),
				sqr((-b + sqrt(sqr(b) + 4 * a*c)) / (2 * a))
			);
		}


		template<class BasicTurbulenceModel>
		void Smagorinsky<BasicTurbulenceModel>::correctNut()
		{
			volScalarField k(this->k(fvc::grad(this->U_)));

			this->nut_ = Ck_ * this->delta()*sqrt(k);
			this->nut_.correctBoundaryConditions();
			fv::options::New(this->mesh_).correct(this->nut_);

			BasicTurbulenceModel::correctNut();
		}


		// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

		template<class BasicTurbulenceModel>
		Smagorinsky<BasicTurbulenceModel>::Smagorinsky
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
			LESeddyViscosity<BasicTurbulenceModel>
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
			)
		{
			if (type == typeName)
			{
				this->printCoeffs(type);
			}
		}


		// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

		template<class BasicTurbulenceModel>
		bool Smagorinsky<BasicTurbulenceModel>::read()
		{
			if (LESeddyViscosity<BasicTurbulenceModel>::read())
			{
				Ck_.readIfPresent(this->coeffDict());

				return true;
			}
			else
			{
				return false;
			}
		}


		template<class BasicTurbulenceModel>
		tmp<volScalarField> Smagorinsky<BasicTurbulenceModel>::epsilon() const
		{
			volScalarField k(this->k(fvc::grad(this->U_)));

			return volScalarField::New
			(
				IOobject::groupName("epsilon", this->alphaRhoPhi_.group()),
				this->Ce_*k*sqrt(k) / this->delta()
			);
		}


		template<class BasicTurbulenceModel>
		void Smagorinsky<BasicTurbulenceModel>::correct()
		{
			LESeddyViscosity<BasicTurbulenceModel>::correct();
			correctNut();
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace LESModels
} // End namespace tnbLib

// ************************************************************************* //