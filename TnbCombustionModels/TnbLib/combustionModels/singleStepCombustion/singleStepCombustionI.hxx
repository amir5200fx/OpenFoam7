#pragma once
#include <fvmSup.hxx>

namespace tnbLib
{
	namespace combustionModels
	{

		// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

		template<class ReactionThermo, class ThermoType>
		singleStepCombustion<ReactionThermo, ThermoType>::singleStepCombustion
		(
			const word& modelType,
			ReactionThermo& thermo,
			const compressibleTurbulenceModel& turb,
			const word& combustionProperties
		)
			:
			ThermoCombustion<ReactionThermo>(modelType, thermo, turb),
			singleMixturePtr_(nullptr),
			wFuel_
			(
				IOobject
				(
					this->thermo().phasePropertyName("wFuel"),
					this->mesh().time().timeName(),
					this->mesh(),
					IOobject::NO_READ,
					IOobject::NO_WRITE
				),
				this->mesh(),
				dimensionedScalar(dimMass / dimVolume / dimTime, 0)
			),
			semiImplicit_(readBool(this->coeffs_.lookup("semiImplicit")))
		{
			if (isA<singleStepReactingMixture<ThermoType>>(this->thermo()))
			{
				singleMixturePtr_ =
					&dynamic_cast<singleStepReactingMixture<ThermoType>&>
					(
						this->thermo()
						);
			}
			else
			{
				FatalErrorInFunction
					<< "Inconsistent thermo package for " << this->type() << " model:\n"
					<< "    " << this->thermo().type() << nl << nl
					<< "Please select a thermo package based on "
					<< "singleStepReactingMixture" << exit(FatalError);
			}

			if (semiImplicit_)
			{
				Info << "Combustion mode: semi-implicit" << endl;
			}
			else
			{
				Info << "Combustion mode: explicit" << endl;
			}
		}


		// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

		template<class ReactionThermo, class ThermoType>
		singleStepCombustion<ReactionThermo, ThermoType>::~singleStepCombustion()
		{}


		// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

		template<class ReactionThermo, class ThermoType>
		tmp<fvScalarMatrix> singleStepCombustion<ReactionThermo, ThermoType>::R
		(
			volScalarField& Y
		) const
		{
			const label specieI =
				this->thermo().composition().species()[Y.member()];

			volScalarField wSpecie
			(
				wFuel_*singleMixturePtr_->specieStoichCoeffs()[specieI]
			);

			if (semiImplicit_)
			{
				const label fNorm = singleMixturePtr_->specieProd()[specieI];
				const volScalarField fres(singleMixturePtr_->fres(specieI));
				wSpecie /= max(fNorm*(Y - fres), scalar(1e-2));

				return -fNorm * wSpecie*fres + fNorm * fvm::Sp(wSpecie, Y);
			}
			else
			{
				return wSpecie + fvm::Sp(0.0*wSpecie, Y);
			}
		}


		template<class ReactionThermo, class ThermoType>
		tmp<volScalarField>
			singleStepCombustion<ReactionThermo, ThermoType>::Qdot() const
		{
			const label fuelI = singleMixturePtr_->fuelIndex();
			volScalarField& YFuel =
				const_cast<volScalarField&>(this->thermo().composition().Y(fuelI));

			return -singleMixturePtr_->qFuel()*(R(YFuel) & YFuel);
		}


		template<class ReactionThermo, class ThermoType>
		bool singleStepCombustion<ReactionThermo, ThermoType>::read()
		{
			if (ThermoCombustion<ReactionThermo>::read())
			{
				return true;
			}
			else
			{
				return false;
			}
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace combustionModels
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //