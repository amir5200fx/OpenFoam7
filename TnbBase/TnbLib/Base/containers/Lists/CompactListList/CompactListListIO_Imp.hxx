#pragma once
#include <Istream.hxx>

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

template<class T, class Container>
tnbLib::CompactListList<T, Container>::CompactListList(Istream& is)
{
	operator>>(is, *this);
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

template<class T, class Container>
tnbLib::Istream& tnbLib::operator>>(Istream& is, CompactListList<T, Container>& lst)
{
	is >> lst.offsets_ >> lst.m_;
	// Note: empty list gets output as two empty lists
	if (lst.offsets_.size() == 0)
	{
		lst.size_ = 0;
	}
	else
	{
		lst.size_ = lst.offsets_.size() - 1;
	}
	return is;
}


template<class T, class Container>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const CompactListList<T, Container>& lst
	)
{
	os << lst.offsets_ << lst.m_;
	return os;
}


// ************************************************************************* //