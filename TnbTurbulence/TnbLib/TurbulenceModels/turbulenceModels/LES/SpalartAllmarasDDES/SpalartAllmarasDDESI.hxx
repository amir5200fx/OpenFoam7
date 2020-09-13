#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace LESModels
	{

		// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

		template<class BasicTurbulenceModel>
		tmp<volScalarField> SpalartAllmarasDDES<BasicTurbulenceModel>::rd
		(
			const volScalarField& magGradU
		) const
		{
			tmp<volScalarField> tr
			(
				min
				(
					this->nuEff()
					/ (
						max
						(
							magGradU,
							dimensionedScalar(magGradU.dimensions(), small)
						)
						*sqr(this->kappa_*this->y_)
						),
					scalar(10)
				)
			);
			tr.ref().boundaryFieldRef() == 0.0;

			return tr;
		}


		template<class BasicTurbulenceModel>
		tmp<volScalarField> SpalartAllmarasDDES<BasicTurbulenceModel>::fd
		(
			const volScalarField& magGradU
		) const
		{
			return 1 - tanh(pow3(8 * rd(magGradU)));
		}


		// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

		template<class BasicTurbulenceModel>
		tmp<volScalarField> SpalartAllmarasDDES<BasicTurbulenceModel>::dTilda
		(
			const volScalarField& chi,
			const volScalarField& fv1,
			const volTensorField& gradU
		) const
		{
			return max
			(
				this->y_
				- fd(mag(gradU))
				*max
				(
					this->y_ - this->CDES_*this->delta(),
					dimensionedScalar(dimLength, 0)
				),
				dimensionedScalar(dimLength, small)
			);
		}


		// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

		template<class BasicTurbulenceModel>
		SpalartAllmarasDDES<BasicTurbulenceModel>::SpalartAllmarasDDES
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
			SpalartAllmarasDES<BasicTurbulenceModel>
			(
				alpha,
				rho,
				U,
				alphaRhoPhi,
				phi,
				transport,
				propertiesName
				)
		{}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace LESModels
} // End namespace tnbLib

// ************************************************************************* //