#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

namespace tnbLib
{

	template<class ReactionThermo>
	inline ReactionThermo& BasicChemistryModel<ReactionThermo>::thermo()
	{
		return thermo_;
	}


	template<class ReactionThermo>
	inline const ReactionThermo&
		BasicChemistryModel<ReactionThermo>::thermo() const
	{
		return thermo_;
	}
}


// ************************************************************************* //