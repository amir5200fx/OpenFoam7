#include <LESeddyViscosity.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace LESModels
	{

		// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

		template<class BasicTurbulenceModel>
		LESeddyViscosity<BasicTurbulenceModel>::LESeddyViscosity
		(
			const word& type,
			const alphaField& alpha,
			const rhoField& rho,
			const volVectorField& U,
			const surfaceScalarField& alphaRhoPhi,
			const surfaceScalarField& phi,
			const transportModel& transport,
			const word& propertiesName
		)
			:
			eddyViscosity<LESModel<BasicTurbulenceModel>>
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

			Ce_
			(
				dimensioned<scalar>::lookupOrAddToDict
				(
					"Ce",
					this->coeffDict_,
					1.048
				)
			)
		{}


		// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

		template<class BasicTurbulenceModel>
		bool LESeddyViscosity<BasicTurbulenceModel>::read()
		{
			if (eddyViscosity<LESModel<BasicTurbulenceModel>>::read())
			{
				Ce_.readIfPresent(this->coeffDict());

				return true;
			}
			else
			{
				return false;
			}
		}


		template<class BasicTurbulenceModel>
		tmp<volScalarField> LESeddyViscosity<BasicTurbulenceModel>::epsilon() const
		{
			tmp<volScalarField> tk(this->k());

			return volScalarField::New
			(
				IOobject::groupName("epsilon", this->alphaRhoPhi_.group()),
				Ce_*tk()*sqrt(tk()) / this->delta()
			);
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace LESModels
} // End namespace tnbLib

// ************************************************************************* //