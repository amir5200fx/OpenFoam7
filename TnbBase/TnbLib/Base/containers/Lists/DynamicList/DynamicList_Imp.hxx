#pragma once
// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //


template<class T, unsigned SizeInc, unsigned SizeMult, unsigned SizeDiv>
tnbLib::DynamicList<T, SizeInc, SizeMult, SizeDiv>::DynamicList(Istream& is)
	:
	List<T>(is),
	capacity_(List<T>::size())
{}


template<class T, unsigned SizeInc, unsigned SizeMult, unsigned SizeDiv>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const DynamicList<T, SizeInc, SizeMult, SizeDiv>& lst
	)
{
	os << static_cast<const List<T>&>(lst);
	return os;
}


template<class T, unsigned SizeInc, unsigned SizeMult, unsigned SizeDiv>
tnbLib::Istream& tnbLib::operator>>
(
	Istream& is,
	DynamicList<T, SizeInc, SizeMult, SizeDiv>& lst
	)
{
	is >> static_cast<List<T>&>(lst);
	lst.capacity_ = lst.List<T>::size();

	return is;
}


// ************************************************************************* //