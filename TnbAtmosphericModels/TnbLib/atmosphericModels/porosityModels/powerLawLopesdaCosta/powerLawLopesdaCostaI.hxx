#pragma once
#include <volFields.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class RhoFieldType>
void tnbLib::porosityModels::powerLawLopesdaCosta::apply
(
	scalarField& Udiag,
	const scalarField& V,
	const RhoFieldType& rho,
	const vectorField& U
) const
{
	const scalar C1m1b2 = (C1_ - 1.0) / 2.0;

	forAll(cellZoneIDs_, zonei)
	{
		const labelList& cells = mesh_.cellZones()[cellZoneIDs_[zonei]];

		forAll(cells, i)
		{
			const label celli = cells[i];

			Udiag[celli] +=
				V[celli] * rho[celli]
				* Cd_*Sigma_[i] * pow(magSqr(U[celli]), C1m1b2);
		}
	}
}


template<class RhoFieldType>
void tnbLib::porosityModels::powerLawLopesdaCosta::apply
(
	tensorField& AU,
	const RhoFieldType& rho,
	const vectorField& U
) const
{
	const scalar C1m1b2 = (C1_ - 1.0) / 2.0;

	forAll(cellZoneIDs_, zonei)
	{
		const labelList& cells = mesh_.cellZones()[cellZoneIDs_[zonei]];

		forAll(cells, i)
		{
			const label celli = cells[i];

			AU[celli] =
				AU[celli]
				+ I
				* (
					0.5*rho[celli] * Cd_*Sigma_[i]
					* pow(magSqr(U[celli]), C1m1b2)
					);
		}
	}
}


// ************************************************************************* //