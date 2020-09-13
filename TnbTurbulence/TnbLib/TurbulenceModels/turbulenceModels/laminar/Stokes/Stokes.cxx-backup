#include <Stokes.hxx>

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
		Stokes<BasicTurbulenceModel>::Stokes
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
				)
		{}


		// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

		template<class BasicTurbulenceModel>
		const dictionary&
			Stokes<BasicTurbulenceModel>::coeffDict() const
		{
			return dictionary::null;
		}


		template<class BasicTurbulenceModel>
		bool Stokes<BasicTurbulenceModel>::read()
		{
			return true;
		}


		template<class BasicTurbulenceModel>
		tmp<volScalarField>
			Stokes<BasicTurbulenceModel>::nut() const
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
			Stokes<BasicTurbulenceModel>::nut
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
			Stokes<BasicTurbulenceModel>::nuEff() const
		{
			return volScalarField::New
			(
				IOobject::groupName("nuEff", this->alphaRhoPhi_.group()),
				this->nu()
			);
		}


		template<class BasicTurbulenceModel>
		tmp<scalarField>
			Stokes<BasicTurbulenceModel>::nuEff
			(
				const label patchi
			) const
		{
			return this->nu(patchi);
		}


		template<class BasicTurbulenceModel>
		tmp<volScalarField>
			Stokes<BasicTurbulenceModel>::k() const
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
			Stokes<BasicTurbulenceModel>::epsilon() const
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
			Stokes<BasicTurbulenceModel>::R() const
		{
			return volSymmTensorField::New
			(
				IOobject::groupName("R", this->alphaRhoPhi_.group()),
				this->mesh_,
				dimensionedSymmTensor(sqr(this->U_.dimensions()), Zero)
			);
		}


		template<class BasicTurbulenceModel>
		void Stokes<BasicTurbulenceModel>::correct()
		{
			laminarModel<BasicTurbulenceModel>::correct();
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace laminarModels
} // End namespace tnbLib

// ************************************************************************* //