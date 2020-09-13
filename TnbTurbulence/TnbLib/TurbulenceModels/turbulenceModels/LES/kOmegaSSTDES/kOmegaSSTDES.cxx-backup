#include <kOmegaSSTDES.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace LESModels
	{

		// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

		template<class BasicTurbulenceModel>
		tmp<volScalarField::Internal> kOmegaSSTDES<BasicTurbulenceModel>::Lt() const
		{
			return sqrt(this->k_()) / (this->betaStar_*this->omega_());
		}


		template<class BasicTurbulenceModel>
		tmp<volScalarField::Internal> kOmegaSSTDES<BasicTurbulenceModel>::FDES
		(
			const volScalarField::Internal& F1,
			const volScalarField::Internal& F2
		) const
		{
			switch (FSST_)
			{
			case 0:
				return max(Lt() / (CDES_*this->delta()()), scalar(1));
			case 1:
				return max(Lt()*(1 - F1) / (CDES_*this->delta()()), scalar(1));
			case 2:
				return max(Lt()*(1 - F2) / (CDES_*this->delta()()), scalar(1));
			default:
				FatalErrorInFunction
					<< "Incorrect FSST = " << FSST_ << ", should be 0, 1 or 2"
					<< exit(FatalError);
				return F1;
			}
		}


		template<class BasicTurbulenceModel>
		tmp<volScalarField::Internal> kOmegaSSTDES<BasicTurbulenceModel>::epsilonByk
		(
			const volScalarField::Internal& F1,
			const volScalarField::Internal& F2
		) const
		{
			return this->betaStar_*this->omega_()*FDES(F1, F2);
		}


		// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

		template<class BasicTurbulenceModel>
		kOmegaSSTDES<BasicTurbulenceModel>::kOmegaSSTDES
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
			kOmegaSST
			<
			LESeddyViscosity<BasicTurbulenceModel>,
			BasicTurbulenceModel
			>
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

			CDES_
			(
				dimensioned<scalar>::lookupOrAddToDict
				(
					"CDES",
					this->coeffDict_,
					0.61
				)
			),
			FSST_(this->coeffDict_.lookupOrDefault("FSST", 2))
		{
			if (type == typeName)
			{
				this->printCoeffs(type);
			}
		}


		// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

		template<class BasicTurbulenceModel>
		bool kOmegaSSTDES<BasicTurbulenceModel>::read()
		{
			if
				(
					kOmegaSST<LESeddyViscosity<BasicTurbulenceModel>, BasicTurbulenceModel>
					::read()
					)
			{
				CDES_.readIfPresent(this->coeffDict());
				this->coeffDict().readIfPresent("FSST", FSST_);

				return true;
			}
			else
			{
				return false;
			}
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace LESModels
} // End namespace tnbLib

// ************************************************************************* //