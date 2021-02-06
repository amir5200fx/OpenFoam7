#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class ReactionThermo>
tnbLib::CombustionModel<ReactionThermo>::CombustionModel
(
	const word& modelType,
	ReactionThermo& thermo,
	const compressibleTurbulenceModel& turb,
	const word& combustionProperties
)
	:
	combustionModel(modelType, thermo, turb, combustionProperties)
{}


// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

template<class ReactionThermo>
tnbLib::autoPtr<tnbLib::CombustionModel<ReactionThermo>>
tnbLib::CombustionModel<ReactionThermo>::New
(
	ReactionThermo& thermo,
	const compressibleTurbulenceModel& turb,
	const word& combustionProperties
)
{
	return
		combustionModel::New<CombustionModel<ReactionThermo>>
		(
			thermo,
			turb,
			combustionProperties
			);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class ReactionThermo>
tnbLib::CombustionModel<ReactionThermo>::~CombustionModel()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

template<class ReactionThermo>
bool tnbLib::CombustionModel<ReactionThermo>::read()
{
	if (combustionModel::read())
	{
		return true;
	}
	else
	{
		return false;
	}
}


// ************************************************************************* //