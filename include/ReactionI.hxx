#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	template<class ReactionThermo>
	inline const word& Reaction<ReactionThermo>::name() const
	{
		return name_;
	}


	template<class ReactionThermo>
	inline scalar Reaction<ReactionThermo>::Tlow() const
	{
		return Tlow_;
	}


	template<class ReactionThermo>
	inline scalar Reaction<ReactionThermo>::Thigh() const
	{
		return Thigh_;
	}


	template<class ReactionThermo>
	inline const List<specieCoeffs>& Reaction<ReactionThermo>::lhs() const
	{
		return lhs_;
	}


	template<class ReactionThermo>
	inline const List<specieCoeffs>& Reaction<ReactionThermo>::rhs() const
	{
		return rhs_;
	}


	// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

	template<class ReactionThermo>
	inline Ostream& operator<<(Ostream& os, const Reaction<ReactionThermo>& r)
	{
		r.write(os);
		return os;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //