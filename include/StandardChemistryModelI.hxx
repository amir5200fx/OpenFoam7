#pragma once
#include <volFields.hxx>
#include <zeroGradientFvPatchFields.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class ReactionThermo, class ThermoType>
inline tnbLib::label
tnbLib::StandardChemistryModel<ReactionThermo, ThermoType>::nEqns() const
{
	// nEqns = number of species + temperature + pressure
	return nSpecie_ + 2;
}


template<class ReactionThermo, class ThermoType>
inline tnbLib::PtrList<tnbLib::DimensionedField<tnbLib::scalar, tnbLib::volMesh>>&
tnbLib::StandardChemistryModel<ReactionThermo, ThermoType>::RR()
{
	return RR_;
}


template<class ReactionThermo, class ThermoType>
inline const tnbLib::PtrList<tnbLib::Reaction<ThermoType>>&
tnbLib::StandardChemistryModel<ReactionThermo, ThermoType>::reactions() const
{
	return reactions_;
}


template<class ReactionThermo, class ThermoType>
inline const tnbLib::PtrList<ThermoType>&
tnbLib::StandardChemistryModel<ReactionThermo, ThermoType>::specieThermo() const
{
	return specieThermo_;
}


template<class ReactionThermo, class ThermoType>
inline tnbLib::label
tnbLib::StandardChemistryModel<ReactionThermo, ThermoType>::nSpecie() const
{
	return nSpecie_;
}


template<class ReactionThermo, class ThermoType>
inline tnbLib::label
tnbLib::StandardChemistryModel<ReactionThermo, ThermoType>::nReaction() const
{
	return nReaction_;
}


template<class ReactionThermo, class ThermoType>
inline tnbLib::scalar
tnbLib::StandardChemistryModel<ReactionThermo, ThermoType>::Treact() const
{
	return Treact_;
}


template<class ReactionThermo, class ThermoType>
inline tnbLib::scalar&
tnbLib::StandardChemistryModel<ReactionThermo, ThermoType>::Treact()
{
	return Treact_;
}


template<class ReactionThermo, class ThermoType>
inline const tnbLib::DimensionedField<tnbLib::scalar, tnbLib::volMesh>&
tnbLib::StandardChemistryModel<ReactionThermo, ThermoType>::RR
(
	const label i
) const
{
	return RR_[i];
}

template<class ReactionThermo, class ThermoType>
tnbLib::DimensionedField<tnbLib::scalar, tnbLib::volMesh>&
tnbLib::StandardChemistryModel<ReactionThermo, ThermoType>::RR
(
	const label i
)
{
	return RR_[i];
}


// ************************************************************************* //