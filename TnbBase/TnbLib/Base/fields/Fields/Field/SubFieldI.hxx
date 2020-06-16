#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
inline tnbLib::SubField<Type>::SubField
(
	const SubList<Type>& list
)
	:
	SubList<Type>(list)
{}


template<class Type>
inline tnbLib::SubField<Type>::SubField
(
	const UList<Type>& list
)
	:
	SubList<Type>(list, list.size())
{}


template<class Type>
inline tnbLib::SubField<Type>::SubField
(
	const UList<Type>& list,
	const label subSize
)
	:
	SubList<Type>(list, subSize)
{}


template<class Type>
inline tnbLib::SubField<Type>::SubField
(
	const UList<Type>& list,
	const label subSize,
	const label startIndex
)
	:
	SubList<Type>(list, subSize, startIndex)
{}


template<class Type>
inline tnbLib::SubField<Type>::SubField
(
	const SubField<Type>& sfield
)
	:
	tmp<SubField<Type>>::refCount(),
	SubList<Type>(sfield)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
inline const tnbLib::SubField<Type>& tnbLib::SubField<Type>::null()
{
	return NullObjectRef<SubField<Type>>();
}


template<class Type>
inline tnbLib::tmp<tnbLib::Field<typename tnbLib::SubField<Type>::cmptType>>
tnbLib::SubField<Type>::component
(
	const direction d
) const
{
	return (reinterpret_cast<const Field<Type>&>(*this)).component(d);
}


template<class Type>
inline tnbLib::tmp<tnbLib::Field<Type>> tnbLib::SubField<Type>::T() const
{
	return (reinterpret_cast<const Field<Type>&>(*this)).T();
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class Type>
inline void tnbLib::SubField<Type>::operator=(const SubField<Type>& rhs)
{
	SubList<Type>::operator=(rhs);
}


template<class Type>
inline void tnbLib::SubField<Type>::operator=(const Field<Type>& rhs)
{
	SubList<Type>::operator=(rhs);
}


template<class Type>
template<class Form, tnbLib::direction Ncmpts>
inline void tnbLib::SubField<Type>::operator=
(
	const VectorSpace<Form, Type, Ncmpts>& rhs
	)
{
	forAll(rhs, i)
	{
		this->operator[](i) = rhs[i];
	}
}


template<class Type>
inline tnbLib::SubField<Type>::operator const tnbLib::Field<Type>&() const
{
	return *reinterpret_cast<const Field<Type>*>(this);
}


// ************************************************************************* //