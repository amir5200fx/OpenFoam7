#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class ReactionThermo>
tnbLib::ThermoCombustion<ReactionThermo>::ThermoCombustion
(
	const word& modelType,
	ReactionThermo& thermo,
	const compressibleTurbulenceModel& turb
)
	:
	CombustionModel<ReactionThermo>
	(
		modelType,
		thermo,
		turb,
		combustionModel::combustionPropertiesName
		),
	thermo_(thermo)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class ReactionThermo>
tnbLib::ThermoCombustion<ReactionThermo>::~ThermoCombustion()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

template<class ReactionThermo>
ReactionThermo&
tnbLib::ThermoCombustion<ReactionThermo>::thermo()
{
	return thermo_;
}


template<class ReactionThermo>
const ReactionThermo&
tnbLib::ThermoCombustion<ReactionThermo>::thermo() const
{
	return thermo_;
}


// ************************************************************************* //