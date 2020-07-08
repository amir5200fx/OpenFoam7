#pragma once
template<class Type>
tnbLib::scalar tnbLib::uniformInterpolationTable<Type>::x0() const
{
	return x0_;
}


template<class Type>
tnbLib::scalar tnbLib::uniformInterpolationTable<Type>::dx() const
{
	return dx_;
}


template<class Type>
const tnbLib::Switch& tnbLib::uniformInterpolationTable<Type>::log10() const
{
	return log10_;
}


template<class Type>
const tnbLib::Switch& tnbLib::uniformInterpolationTable<Type>::bound() const
{
	return bound_;
}


template<class Type>
tnbLib::scalar& tnbLib::uniformInterpolationTable<Type>::x0()
{
	return x0_;
}


template<class Type>
tnbLib::scalar& tnbLib::uniformInterpolationTable<Type>::dx()
{
	return dx_;
}


template<class Type>
tnbLib::Switch& tnbLib::uniformInterpolationTable<Type>::log10()
{
	return log10_;
}


template<class Type>
tnbLib::Switch& tnbLib::uniformInterpolationTable<Type>::bound()
{
	return bound_;
}


template<class Type>
tnbLib::scalar tnbLib::uniformInterpolationTable<Type>::xMin() const
{
	return x0_;
}


template<class Type>
tnbLib::scalar tnbLib::uniformInterpolationTable<Type>::xMax() const
{
	return x0_ + dx_ * (size() - 1);
}


// ************************************************************************* //