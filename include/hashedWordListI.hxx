#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline bool tnbLib::hashedWordList::found(const word& name) const
{
	return indices_.found(name);
}


inline bool tnbLib::hashedWordList::contains(const word& name) const
{
	return indices_.found(name);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

inline void tnbLib::hashedWordList::operator=(const UList<word>& lst)
{
	List<word>::operator=(lst);
	rehash();
}


inline void tnbLib::hashedWordList::operator=(const hashedWordList& lst)
{
	operator=(static_cast<const UList<word>&>(lst));
}


inline const tnbLib::word& tnbLib::hashedWordList::operator[]
(
	const label index
	) const
{
	return List<word>::operator[](index);
}


// could return -1 instead of bombing out
inline tnbLib::label tnbLib::hashedWordList::operator[](const word& name) const
{
	return indices_[name];
}


// ************************************************************************* //