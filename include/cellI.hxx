#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline tnbLib::cell::cell()
{}


inline tnbLib::cell::cell(label s)
	:
	labelList(s, -1)
{}


inline tnbLib::cell::cell(const labelUList& lst)
	:
	labelList(lst)
{}


inline tnbLib::cell::cell(labelList&& lst)
	:
	labelList(move(lst))
{}


inline tnbLib::cell::cell(Istream& is)
	:
	labelList(is)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline tnbLib::label tnbLib::cell::nFaces() const
{
	return size();
}


inline bool tnbLib::operator!=(const cell& a, const cell& b)
{
	return (!(a == b));
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

inline void tnbLib::cell::operator=(labelList&& l)
{
	labelList::operator=(move(l));
}


// ************************************************************************* //