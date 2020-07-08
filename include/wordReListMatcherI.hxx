#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline tnbLib::wordReListMatcher::wordReListMatcher
(
	const UList<wordRe>& lst
)
	:
	reList_(lst)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline tnbLib::label tnbLib::wordReListMatcher::size() const
{
	return reList_.size();
}


inline bool tnbLib::wordReListMatcher::empty() const
{
	return reList_.empty();
}


inline const tnbLib::UList<tnbLib::wordRe>&
tnbLib::wordReListMatcher::operator()() const
{
	return reList_;
}


inline bool tnbLib::wordReListMatcher::match
(
	const string& str,
	bool literalMatch
) const
{
	const label nElem = reList_.size();
	for (label elemI = 0; elemI < nElem; ++elemI)
	{
		if (reList_[elemI].match(str, literalMatch))
		{
			return true;
		}
	}

	return false;
}


// ************************************************************************* //