#pragma once
template<class Type>
inline tnbLib::label
tnbLib::interpolationLookUpTable<Type>::findFieldIndex
(
	const word& fieldName
) const
{
	return fieldIndices_[fieldName];
}


template<class Type>
inline const tnbLib::List<tnbLib::dictionary>&
tnbLib::interpolationLookUpTable<Type>::output() const
{
	return output_;
}


template<class Type>
inline const tnbLib::List<tnbLib::dictionary>&
tnbLib::interpolationLookUpTable<Type>::entries() const
{
	return entries_;
}


template<class Type>
inline const tnbLib::List<tnbLib::scalar>&
tnbLib::interpolationLookUpTable<Type>::min() const
{
	return min_;
}


template<class Type>
inline const tnbLib::List<tnbLib::label>&
tnbLib::interpolationLookUpTable<Type>::dim() const
{
	return dim_;
}


template<class Type>
inline const tnbLib::List<tnbLib::scalar>&
tnbLib::interpolationLookUpTable<Type>::delta() const
{
	return delta_;
}


template<class Type>
inline const tnbLib::List<tnbLib::scalar>&
tnbLib::interpolationLookUpTable<Type>::max() const
{
	return max_;
}


template<class Type>
inline tnbLib::word tnbLib::interpolationLookUpTable<Type>::tableName() const
{
	return fileName_.name();
}


// ************************************************************************* //