#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class ReactionThermo>
tnbLib::ChemistryCombustion<ReactionThermo>::ChemistryCombustion
(
	const word& modelType,
	ReactionThermo& thermo,
	const compressibleTurbulenceModel& turb,
	const word& combustionProperties
)
	:
	CombustionModel<ReactionThermo>
	(
		modelType,
		thermo,
		turb,
		combustionProperties
		),
	chemistryPtr_(BasicChemistryModel<ReactionThermo>::New(thermo))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class ReactionThermo>
tnbLib::ChemistryCombustion<ReactionThermo>::
~ChemistryCombustion()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

template<class ReactionThermo>
ReactionThermo&
tnbLib::ChemistryCombustion<ReactionThermo>::thermo()
{
	return chemistryPtr_->thermo();
}


template<class ReactionThermo>
const ReactionThermo&
tnbLib::ChemistryCombustion<ReactionThermo>::thermo() const
{
	return chemistryPtr_->thermo();
}


// ************************************************************************* //