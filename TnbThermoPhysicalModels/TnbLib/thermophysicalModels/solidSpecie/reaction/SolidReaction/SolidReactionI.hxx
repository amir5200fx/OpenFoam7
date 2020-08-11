#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

	template<class ReactionThermo>
	inline Ostream& operator<<
		(
			Ostream& os,
			const SolidReaction<ReactionThermo>& r
			)
	{
		OStringStream reaction;
		os << r.solidReactionStr(reaction) << token::END_STATEMENT << nl;
		return os;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //