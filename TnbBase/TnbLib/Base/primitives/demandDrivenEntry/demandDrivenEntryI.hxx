#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type>
inline void tnbLib::demandDrivenEntry<Type>::initialise() const
{
	if (!stored_)
	{
		dict_.lookup(keyword_) >> value_;
		stored_ = true;
	}
}


template<class Type>
inline const Type& tnbLib::demandDrivenEntry<Type>::value() const
{
	initialise();

	return value_;
}


template<class Type>
inline void tnbLib::demandDrivenEntry<Type>::setValue(const Type& value)
{
	//    dict_.set<Type>(keyword_, value);
	value_ = value;
	stored_ = true;
}


template<class Type>
inline void tnbLib::demandDrivenEntry<Type>::reset()
{
	stored_ = false;
}


// ************************************************************************* //