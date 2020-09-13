#pragma once
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace laminarModels
	{

		// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

		template<class BasicTurbulenceModel>
		Giesekus<BasicTurbulenceModel>::Giesekus
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
			Maxwell<BasicTurbulenceModel>
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

			alphaG_("alphaG", dimless, this->coeffDict_)
		{
			if (type == typeName)
			{
				this->printCoeffs(type);
			}
		}


		// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

		template<class BasicTurbulenceModel>
		bool Giesekus<BasicTurbulenceModel>::read()
		{
			if (Maxwell<BasicTurbulenceModel>::read())
			{
				alphaG_.read(this->coeffDict());

				return true;
			}
			else
			{
				return false;
			}
		}


		template<class BasicTurbulenceModel>
		tmp<fvSymmTensorMatrix>
			Giesekus<BasicTurbulenceModel>::sigmaSource() const
		{
			return fvm::Su
			(
				this->alpha_*this->rho_
				*alphaG_*innerSqr(this->sigma_) / this->nuM_, this->sigma_
			);
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace laminarModels
} // End namespace tnbLib

// ************************************************************************* //