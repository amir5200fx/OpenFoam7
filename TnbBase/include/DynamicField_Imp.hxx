#pragma once
// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

template<class T, unsigned SizeInc, unsigned SizeMult, unsigned SizeDiv>
tnbLib::DynamicField<T, SizeInc, SizeMult, SizeDiv>::DynamicField(Istream& is)
	:
	Field<T>(is),
	capacity_(Field<T>::size())
{}


template<class T, unsigned SizeInc, unsigned SizeMult, unsigned SizeDiv>
tnbLib::tmp<tnbLib::DynamicField<T, SizeInc, SizeMult, SizeDiv>>
tnbLib::DynamicField<T, SizeInc, SizeMult, SizeDiv>::clone() const
{
	return tmp<DynamicField<T, SizeInc, SizeMult, SizeDiv>>
		(
			new DynamicField<T, SizeInc, SizeMult, SizeDiv>(*this)
			);
}


// * * * * * * * * * * * * * * * IOstream Operator * * * * * * * * * * * * * //

template<class T, unsigned SizeInc, unsigned SizeMult, unsigned SizeDiv>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const DynamicField<T, SizeInc, SizeMult, SizeDiv>& lst
	)
{
	os << static_cast<const Field<T>&>(lst);
	return os;
}


template<class T, unsigned SizeInc, unsigned SizeMult, unsigned SizeDiv>
tnbLib::Istream& tnbLib::operator>>
(
	Istream& is,
	DynamicField<T, SizeInc, SizeMult, SizeDiv>& lst
	)
{
	is >> static_cast<Field<T>&>(lst);
	lst.capacity_ = lst.Field<T>::size();

	return is;
}


// ************************************************************************* //