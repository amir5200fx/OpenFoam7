#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
inline const Type& tnbLib::Distribution<Type>::binWidth() const
{
	return binWidth_;
}


template<class Type>
inline const
tnbLib::List<tnbLib::label>& tnbLib::Distribution<Type>::listStarts() const
{
	return listStarts_;
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


// ************************************************************************* //
