#pragma once
#include <geometricOneField.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class AlphaFieldType, class RhoFieldType>
void tnbLib::porosityModels::solidification::apply
(
	scalarField& Udiag,
	const scalarField& V,
	const AlphaFieldType& alpha,
	const RhoFieldType& rho,
	const volVectorField& U
) const
{
	const volScalarField& T = mesh_.lookupObject<volScalarField>
		(
			IOobject::groupName(TName_, U.group())
			);

	forAll(cellZoneIDs_, zoneI)
	{
		const labelList& cells = mesh_.cellZones()[cellZoneIDs_[zoneI]];

		forAll(cells, i)
		{
			const label celli = cells[i];
			Udiag[celli] +=
				V[celli] * alpha[celli] * rho[celli] * D_->value(T[celli]);
		}
	}
}


template<class AlphaFieldType, class RhoFieldType>
void tnbLib::porosityModels::solidification::apply
(
	tensorField& AU,
	const AlphaFieldType& alpha,
	const RhoFieldType& rho,
	const volVectorField& U
) const
{
	const volScalarField& T = mesh_.lookupObject<volScalarField>
		(
			IOobject::groupName(TName_, U.group())
			);

	forAll(cellZoneIDs_, zoneI)
	{
		const labelList& cells = mesh_.cellZones()[cellZoneIDs_[zoneI]];

		forAll(cells, i)
		{
			const label celli = cells[i];
			AU[celli] +=
				tensor::I*alpha[celli] * rho[celli] * D_->value(T[celli]);
		}
	}
}


template<class RhoFieldType>
void tnbLib::porosityModels::solidification::apply
(
	scalarField& Udiag,
	const scalarField& V,
	const RhoFieldType& rho,
	const volVectorField& U
) const
{
	if (alphaName_ == "none")
	{
		return apply(Udiag, V, geometricOneField(), rho, U);
	}
	else
	{
		const volScalarField& alpha = mesh_.lookupObject<volScalarField>
			(
				IOobject::groupName(alphaName_, U.group())
				);

		return apply(Udiag, V, alpha, rho, U);
	}
}


template<class RhoFieldType>
void tnbLib::porosityModels::solidification::apply
(
	tensorField& AU,
	const RhoFieldType& rho,
	const volVectorField& U
) const
{
	if (alphaName_ == "none")
	{
		return apply(AU, geometricOneField(), rho, U);
	}
	else
	{
		const volScalarField& alpha = mesh_.lookupObject<volScalarField>
			(
				IOobject::groupName(alphaName_, U.group())
				);

		return apply(AU, alpha, rho, U);
	}
}


// ************************************************************************* //