#pragma once
#include <uniformDimensionedFields.hxx>
#include <fvcGrad.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace RASModels
	{

		// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

		template<class BasicTurbulenceModel>
		buoyantKEpsilon<BasicTurbulenceModel>::buoyantKEpsilon
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
			kEpsilon<BasicTurbulenceModel>
			(
				alpha,
				rho,
				U,
				alphaRhoPhi,
				phi,
				transport,
				propertiesName,
				type
				),

			Cg_
			(
				dimensioned<scalar>::lookupOrAddToDict
				(
					"Cg",
					this->coeffDict_,
					1.0
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
		bool buoyantKEpsilon<BasicTurbulenceModel>::read()
		{
			if (kEpsilon<BasicTurbulenceModel>::read())
			{
				Cg_.readIfPresent(this->coeffDict());

				return true;
			}
			else
			{
				return false;
			}
		}


		template<class BasicTurbulenceModel>
		tmp<volScalarField>
			buoyantKEpsilon<BasicTurbulenceModel>::Gcoef() const
		{
			const uniformDimensionedVectorField& g =
				this->mesh_.objectRegistry::template
				lookupObject<uniformDimensionedVectorField>("g");

			return
				(Cg_*this->Cmu_)*this->alpha_*this->k_*(g & fvc::grad(this->rho_))
				/ (this->epsilon_ + this->epsilonMin_);
		}


		template<class BasicTurbulenceModel>
		tmp<fvScalarMatrix>
			buoyantKEpsilon<BasicTurbulenceModel>::kSource() const
		{
			const uniformDimensionedVectorField& g =
				this->mesh_.objectRegistry::template
				lookupObject<uniformDimensionedVectorField>("g");

			if (mag(g.value()) > small)
			{
				return -fvm::SuSp(Gcoef(), this->k_);
			}
			else
			{
				return kEpsilon<BasicTurbulenceModel>::kSource();
			}
		}


		template<class BasicTurbulenceModel>
		tmp<fvScalarMatrix>
			buoyantKEpsilon<BasicTurbulenceModel>::epsilonSource() const
		{
			const uniformDimensionedVectorField& g =
				this->mesh_.objectRegistry::template
				lookupObject<uniformDimensionedVectorField>("g");

			if (mag(g.value()) > small)
			{
				vector gHat(g.value() / mag(g.value()));

				volScalarField v(gHat & this->U_);
				volScalarField u
				(
					mag(this->U_ - gHat * v)
					+ dimensionedScalar(dimVelocity, small)
				);

				return -fvm::SuSp(this->C1_*tanh(mag(v) / u)*Gcoef(), this->epsilon_);
			}
			else
			{
				return kEpsilon<BasicTurbulenceModel>::epsilonSource();
			}
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace RASModels
} // End namespace tnbLib

// ************************************************************************* //