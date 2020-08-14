#pragma once
#include <volFields.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CompType, class SolidThermo, class GasThermo>
inline tnbLib::PtrList<tnbLib::DimensionedField<tnbLib::scalar, tnbLib::volMesh>>&
tnbLib::pyrolysisChemistryModel<CompType, SolidThermo, GasThermo>::RRg()
{
	return RRg_;
}


template<class CompType, class SolidThermo, class GasThermo>
inline const tnbLib::PtrList<GasThermo>&
tnbLib::pyrolysisChemistryModel<CompType, SolidThermo, GasThermo>::
gasThermo() const
{
	return gasThermo_;
}


template<class CompType, class SolidThermo, class GasThermo>
inline const tnbLib::speciesTable&
tnbLib::pyrolysisChemistryModel<CompType, SolidThermo, GasThermo>::
gasTable() const
{
	return pyrolisisGases_;
}


template<class CompType, class SolidThermo, class GasThermo>
inline tnbLib::label
tnbLib::pyrolysisChemistryModel<CompType, SolidThermo, GasThermo>::
nSpecie() const
{
	return nSpecie_;
}


template<class CompType, class SolidThermo, class GasThermo>
inline const tnbLib::DimensionedField<tnbLib::scalar, tnbLib::volMesh>&
tnbLib::pyrolysisChemistryModel<CompType, SolidThermo, GasThermo>::RRg
(
	const label i
) const
{
	return RRg_[i];
}


template<class CompType, class SolidThermo, class GasThermo>
inline tnbLib::tmp<tnbLib::DimensionedField<tnbLib::scalar, tnbLib::volMesh>>
tnbLib::pyrolysisChemistryModel<CompType, SolidThermo, GasThermo>::
RRg() const
{
	tmp<volScalarField::Internal> tRRg
	(
		volScalarField::Internal::New
		(
			"RRg",
			this->mesh(),
			dimensionedScalar(dimMass / dimVolume / dimTime, 0)
		)
	);

	if (this->chemistry_)
	{
		volScalarField::Internal& RRg = tRRg.ref();
		for (label i = 0; i < nGases_; i++)
		{
			RRg += RRg_[i];
		}
	}

	return tRRg;
}


// ************************************************************************* //