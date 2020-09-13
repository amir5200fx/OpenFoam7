#pragma once
#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <fvcGrad.hxx>
#include <fvcDiv.hxx>
#include <fvmLaplacian.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace laminarModels
	{

		// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

		template<class BasicTurbulenceModel>
		generalizedNewtonian<BasicTurbulenceModel>::generalizedNewtonian
		(
			const alphaField& alpha,
			const rhoField& rho,
			const volVectorField& U,
			const surfaceScalarField& alphaRhoPhi,
			const surfaceScalarField& phi,
			const transportModel& transport,
			const word& propertiesName
		)
			:
			linearViscousStress<laminarModel<BasicTurbulenceModel>>
			(
				typeName,
				alpha,
				rho,
				U,
				alphaRhoPhi,
				phi,
				transport,
				propertiesName
				),

			viscosityModel_
			(
				generalizedNewtonianViscosityModel::New
				(
					this->coeffDict_
				)
			),

			nu_
			(
				IOobject
				(
					IOobject::groupName("generalizedNewtonian:nu", alphaRhoPhi.group()),
					this->runTime_.timeName(),
					this->mesh_,
					IOobject::NO_READ,
					IOobject::AUTO_WRITE
				),
				viscosityModel_->nu(this->nu(), strainRate())
			)
		{}


		// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

		template<class BasicTurbulenceModel>
		tnbLib::tmp<tnbLib::volScalarField>
			generalizedNewtonian<BasicTurbulenceModel>::strainRate() const
		{
			return sqrt(2.0)*mag(symm(fvc::grad(this->U())));
		}


		// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

		template<class BasicTurbulenceModel>
		bool generalizedNewtonian<BasicTurbulenceModel>::read()
		{
			viscosityModel_->read(this->coeffDict_);

			return true;
		}


		template<class BasicTurbulenceModel>
		tmp<volScalarField>
			generalizedNewtonian<BasicTurbulenceModel>::nut() const
		{
			return volScalarField::New
			(
				IOobject::groupName("nut", this->alphaRhoPhi_.group()),
				this->mesh_,
				dimensionedScalar(dimViscosity, 0)
			);
		}


		template<class BasicTurbulenceModel>
		tmp<scalarField>
			generalizedNewtonian<BasicTurbulenceModel>::nut
			(
				const label patchi
			) const
		{
			return tmp<scalarField>
				(
					new scalarField(this->mesh_.boundary()[patchi].size(), 0.0)
					);
		}


		template<class BasicTurbulenceModel>
		tmp<volScalarField>
			generalizedNewtonian<BasicTurbulenceModel>::nuEff() const
		{
			return volScalarField::New
			(
				IOobject::groupName("nuEff", this->alphaRhoPhi_.group()),
				nu_
			);
		}


		template<class BasicTurbulenceModel>
		tmp<scalarField>
			generalizedNewtonian<BasicTurbulenceModel>::nuEff
			(
				const label patchi
			) const
		{
			return nu_.boundaryField()[patchi];
		}


		template<class BasicTurbulenceModel>
		tmp<volScalarField>
			generalizedNewtonian<BasicTurbulenceModel>::k() const
		{
			return volScalarField::New
			(
				IOobject::groupName("k", this->alphaRhoPhi_.group()),
				this->mesh_,
				dimensionedScalar(sqr(this->U_.dimensions()), 0)
			);
		}


		template<class BasicTurbulenceModel>
		tmp<volScalarField>
			generalizedNewtonian<BasicTurbulenceModel>::epsilon() const
		{
			return volScalarField::New
			(
				IOobject::groupName("epsilon", this->alphaRhoPhi_.group()),
				this->mesh_,
				dimensionedScalar(sqr(this->U_.dimensions()) / dimTime, 0)
			);
		}


		template<class BasicTurbulenceModel>
		tmp<volSymmTensorField>
			generalizedNewtonian<BasicTurbulenceModel>::R() const
		{
			return volSymmTensorField::New
			(
				IOobject::groupName("R", this->alphaRhoPhi_.group()),
				this->mesh_,
				dimensionedSymmTensor(sqr(this->U_.dimensions()), Zero)
			);
		}


		template<class BasicTurbulenceModel>
		void generalizedNewtonian<BasicTurbulenceModel>::correct()
		{
			nu_ = viscosityModel_->nu(this->nu(), strainRate());
			laminarModel<BasicTurbulenceModel>::correct();
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace laminarModels
} // End namespace tnbLib

// ************************************************************************* //