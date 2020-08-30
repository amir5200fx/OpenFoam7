#pragma once
#include <zeroGradientFvPatchFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace thermalBaffleModels
		{

			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

			inline tmp<scalarField> thermalBaffle::he
			(
				const scalarField& p,
				const scalarField& T,
				const label patchi
			) const
			{
				return thermo_->he(p, T, patchi);
			}


			inline tmp<volScalarField> thermalBaffle::he() const
			{
				return thermo_->he();
			}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace thermalBaffleModels
	} // End namespace regionModels
} // End namespace tnbLib

// ************************************************************************* //