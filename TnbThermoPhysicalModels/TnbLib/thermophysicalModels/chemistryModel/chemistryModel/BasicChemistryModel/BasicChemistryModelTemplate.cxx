#include <BasicChemistryModelTemplate.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class ReactionThermo>
tnbLib::BasicChemistryModel<ReactionThermo>::BasicChemistryModel
(
	ReactionThermo& thermo
)
	:
	basicChemistryModel(thermo),
	thermo_(thermo)
{}


// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

template<class ReactionThermo>
tnbLib::autoPtr<tnbLib::BasicChemistryModel<ReactionThermo>>
tnbLib::BasicChemistryModel<ReactionThermo>::New(ReactionThermo& thermo)
{
	return basicChemistryModel::New<BasicChemistryModel<ReactionThermo>>
		(
			thermo
			);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class ReactionThermo>
tnbLib::BasicChemistryModel<ReactionThermo>::~BasicChemistryModel()
{}


// ************************************************************************* //