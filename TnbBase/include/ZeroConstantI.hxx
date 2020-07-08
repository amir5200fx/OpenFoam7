#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
inline Type tnbLib::Function1Types::ZeroConstant<Type>::value
(
	const scalar x
) const
{
	return pTraits<Type>::zero;
}


template<class Type>
inline Type tnbLib::Function1Types::ZeroConstant<Type>::integrate
(
	const scalar x1,
	const scalar x2
) const
{
	return pTraits<Type>::zero;
}


// ************************************************************************* //