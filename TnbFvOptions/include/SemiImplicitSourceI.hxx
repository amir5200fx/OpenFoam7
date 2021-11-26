#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
inline const typename tnbLib::fv::SemiImplicitSource<Type>::volumeModeType&
tnbLib::fv::SemiImplicitSource<Type>::volumeMode() const
{
	return volumeMode_;
}


template<class Type>
inline const tnbLib::List<tnbLib::Tuple2<Type, tnbLib::scalar>>&
tnbLib::fv::SemiImplicitSource<Type>::injectionRate() const
{
	return injectionRate_;
}


template<class Type>
inline typename tnbLib::fv::SemiImplicitSource<Type>::volumeModeType&
tnbLib::fv::SemiImplicitSource<Type>::volumeMode()
{
	return volumeMode_;
}


template<class Type>
inline tnbLib::List<tnbLib::Tuple2<Type,
	tnbLib::scalar>>&tnbLib::fv::SemiImplicitSource<Type>::injectionRate()
{
	return injectionRate_;
}


// ************************************************************************* //