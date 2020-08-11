#pragma once
#include <volFields.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CompType, class SolidThermo>
inline tnbLib::PtrList<tnbLib::DimensionedField<tnbLib::scalar, tnbLib::volMesh>>&
tnbLib::solidChemistryModel<CompType, SolidThermo>::RRs()
{
	return RRs_;
}

template<class CompType, class SolidThermo>
inline const tnbLib::PtrList<tnbLib::Reaction<SolidThermo>>&
tnbLib::solidChemistryModel<CompType, SolidThermo>::reactions() const
{
	return reactions_;
}


template<class CompType, class SolidThermo>
inline tnbLib::label
tnbLib::solidChemistryModel<CompType, SolidThermo>::
nReaction() const
{
	return nReaction_;
}


template<class CompType, class SolidThermo>
inline const tnbLib::DimensionedField<tnbLib::scalar, tnbLib::volMesh>&
tnbLib::solidChemistryModel<CompType, SolidThermo>::RRs
(
	const label i
) const
{
	return RRs_[i];
}


template<class CompType, class SolidThermo>
inline tnbLib::tmp<tnbLib::DimensionedField<tnbLib::scalar, tnbLib::volMesh>>
tnbLib::solidChemistryModel<CompType, SolidThermo>::RRs() const
{
	tmp<volScalarField::Internal> tRRs
	(
		volScalarField::Internal::New
		(
			"RRs",
			this->mesh(),
			dimensionedScalar(dimMass / dimVolume / dimTime, 0)
		)
	);

	if (this->chemistry_)
	{
		volScalarField::Internal& RRs = tRRs.ref();
		for (label i = 0; i < nSolids_; i++)
		{
			RRs += RRs_[i];
		}
	}
	return tRRs;
}


// ************************************************************************* //
