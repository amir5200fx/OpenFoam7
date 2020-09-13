#pragma once
#include <surfaceInterpolate.hxx>
#include <fvcSurfaceIntegrate.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

			inline const Switch& kinematicSingleLayer::momentumPredictor() const
			{
				return momentumPredictor_;
			}


			inline label kinematicSingleLayer::nOuterCorr() const
			{
				return nOuterCorr_;
			}


			inline label kinematicSingleLayer::nCorr() const
			{
				return nCorr_;
			}


			inline label kinematicSingleLayer::nNonOrthCorr() const
			{
				return nNonOrthCorr_;
			}


			inline const dimensionedScalar& kinematicSingleLayer::deltaSmall() const
			{
				return deltaSmall_;
			}


			inline const volScalarField& kinematicSingleLayer::mu() const
			{
				return mu_;
			}


			inline const volScalarField& kinematicSingleLayer::sigma() const
			{
				return sigma_;
			}


			inline const volScalarField& kinematicSingleLayer::delta() const
			{
				return delta_;
			}


			inline const volScalarField& kinematicSingleLayer::alpha() const
			{
				return alpha_;
			}


			inline volVectorField& kinematicSingleLayer::USpPrimary()
			{
				return USpPrimary_;
			}


			inline volScalarField& kinematicSingleLayer::pSpPrimary()
			{
				return pSpPrimary_;
			}


			inline volScalarField& kinematicSingleLayer::rhoSpPrimary()
			{
				return rhoSpPrimary_;
			}


			inline volVectorField& kinematicSingleLayer::USp()
			{
				return USp_;
			}


			inline volScalarField& kinematicSingleLayer::pSp()
			{
				return pSp_;
			}


			inline volScalarField& kinematicSingleLayer::rhoSp()
			{
				return rhoSp_;
			}


			inline const volVectorField& kinematicSingleLayer::USp() const
			{
				return USp_;
			}


			inline const volScalarField& kinematicSingleLayer::pSp() const
			{
				return pSp_;
			}


			inline const volScalarField& kinematicSingleLayer::rhoSp() const
			{
				return rhoSp_;
			}


			inline const volVectorField& kinematicSingleLayer::UPrimary() const
			{
				return UPrimary_;
			}


			inline const volScalarField& kinematicSingleLayer::pPrimary() const
			{
				return pPrimary_;
			}


			inline const volScalarField& kinematicSingleLayer::rhoPrimary() const
			{
				return rhoPrimary_;
			}


			inline const volScalarField& kinematicSingleLayer::muPrimary() const
			{
				return muPrimary_;
			}


			inline const filmThermoModel& kinematicSingleLayer::filmThermo() const
			{
				return filmThermo_();
			}


			inline injectionModelList& kinematicSingleLayer::injection()
			{
				return injection_;
			}


			inline transferModelList& kinematicSingleLayer::transfer()
			{
				return transfer_;
			}


			inline const filmTurbulenceModel& kinematicSingleLayer::turbulence() const
			{
				return turbulence_();
			}


			inline tmp<volScalarField> kinematicSingleLayer::mass() const
			{
				return rho_ * delta_*magSf();
			}


			inline tmp<volScalarField> kinematicSingleLayer::deltaMass() const
			{
				return rhoSp_ * magSf()*time().deltaT();
			}


			inline tmp<volScalarField> kinematicSingleLayer::gNorm() const
			{
				return volScalarField::New("gNorm", g_ & nHat());
			}


			inline tmp<volScalarField> kinematicSingleLayer::gNormClipped() const
			{
				tmp<volScalarField> tgNormClipped
				(
					volScalarField::New("gNormClipped", g_ & nHat())
				);

				volScalarField& gNormClipped = tgNormClipped.ref();
				gNormClipped.min(0.0);

				return tgNormClipped;
			}


			inline tmp<volVectorField> kinematicSingleLayer::gTan() const
			{
				return volVectorField::New("gTan", g_ - nHat()*gNorm());
			}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// ************************************************************************* //