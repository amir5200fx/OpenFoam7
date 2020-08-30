#pragma once
#include <filmRadiationModel.hxx>
#include <heatTransferModel.hxx>
#include <phaseChangeModel.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

			inline const SLGThermo& thermoSingleLayer::thermo() const
			{
				return thermo_;
			}


			inline tmp<scalarField> thermoSingleLayer::hs
			(
				const scalarField& T,
				const label patchi
			) const
			{
				const scalarField& Cp = Cp_.boundaryField()[patchi];
				return Cp * (T - Tref.value());
			}


			inline tmp<volScalarField> thermoSingleLayer::hs
			(
				const volScalarField& T
			) const
			{
				return volScalarField::New
				(
					"hs(" + T.name() + ")",
					Cp_*(T - Tref)
				);
			}


			inline tmp<volScalarField> thermoSingleLayer::T
			(
				const volScalarField& hs
			) const
			{
				tmp<volScalarField> tT
				(
					volScalarField::New("T(" + hs.name() + ")", hs / Cp_ + Tref)
				);

				tT.ref().min(Tmax_);
				tT.ref().max(Tmin_);

				return tT;
			}


			inline const volScalarField& thermoSingleLayer::hsSp() const
			{
				return hsSp_;
			}


			inline const volScalarField& thermoSingleLayer::hsSpPrimary() const
			{
				return hsSpPrimary_;
			}


			inline const volScalarField& thermoSingleLayer::TPrimary() const
			{
				return TPrimary_;
			}


			inline const PtrList<volScalarField>& thermoSingleLayer::YPrimary() const
			{
				return YPrimary_;
			}


			inline const heatTransferModel& thermoSingleLayer::htcs() const
			{
				return htcs_();
			}


			inline const heatTransferModel& thermoSingleLayer::htcw() const
			{
				return htcw_();
			}


			inline const phaseChangeModel& thermoSingleLayer::phaseChange() const
			{
				return phaseChange_();
			}


			inline const filmRadiationModel& thermoSingleLayer::radiation() const
			{
				return radiation_();
			}


			inline tmp<scalarField> thermoSingleLayer::Qconvw(const label patchi) const
			{
				const scalarField htc(htcw_->h()().boundaryField()[patchi]);
				const scalarField& Tp = T_.boundaryField()[patchi];
				const scalarField& Twp = Tw_.boundaryField()[patchi];

				return htc * (Tp - Twp);
			}


			inline tmp<scalarField> thermoSingleLayer::Qconvp(const label patchi) const
			{
				const scalarField htc(htcs_->h()().boundaryField()[patchi]);
				const scalarField& Tp = T_.boundaryField()[patchi];
				const scalarField& Tpp = TPrimary_.boundaryField()[patchi];

				return htc * (Tp - Tpp);
			}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// ************************************************************************* //