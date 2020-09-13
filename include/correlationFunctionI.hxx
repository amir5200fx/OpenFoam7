#pragma once
template<class Type>
inline const tnbLib::Field<tnbLib::Field<Type>>&
tnbLib::correlationFunction<Type>::tZeroBuffers() const
{
	return tZeroBuffers_;
}


template<class Type>
inline tnbLib::scalar tnbLib::correlationFunction<Type>::duration() const
{
	return duration_;
}


template<class Type>
inline tnbLib::scalar tnbLib::correlationFunction<Type>::sampleInterval() const
{
	return sampleInterval_;
}


template<class Type>
inline tnbLib::scalar tnbLib::correlationFunction<Type>::averagingInterval() const
{
	return averagingInterval_;
}


template<class Type>
inline tnbLib::label tnbLib::correlationFunction<Type>::sampleSteps() const
{
	return sampleSteps_;
}


template<class Type>
inline tnbLib::label tnbLib::correlationFunction<Type>::measurandFieldSize() const
{
	return tZeroBuffers_[0].size();
}


// ************************************************************************* //