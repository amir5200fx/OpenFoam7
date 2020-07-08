#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
inline Type tnbLib::Function1Types::OneConstant<Type>::value(const scalar x) const
{
	return pTraits<Type>::one;
}


template<class Type>
inline Type tnbLib::Function1Types::OneConstant<Type>::integrate
(
	const scalar x1,
	const scalar x2
) const
{
	return (x2 - x1)*pTraits<Type>::one;
}


// ************************************************************************* //