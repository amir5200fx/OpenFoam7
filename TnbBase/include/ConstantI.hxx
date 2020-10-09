#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
inline Type tnbLib::Function1Types::Constant<Type>::value(const scalar x) const
{
	return (Type)value_;  // modified by amir
}


template<class Type>
inline Type tnbLib::Function1Types::Constant<Type>::integrate
(
	const scalar x1,
	const scalar x2
) const
{
	return (Type)((x2 - x1)*value_);  // modified by amir
}


// ************************************************************************* //