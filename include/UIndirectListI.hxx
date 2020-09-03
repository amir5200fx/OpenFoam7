#pragma once
#include <List.hxx>  // added by amir
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class T>
inline tnbLib::UIndirectList<T>::UIndirectList
(
	const UList<T>& completeList,
	const labelUList& addr
)
	:
	completeList_(const_cast<UList<T>&>(completeList)),
	addressing_(addr)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class T>
inline tnbLib::label tnbLib::UIndirectList<T>::size() const
{
	return addressing_.size();
}


template<class T>
inline bool tnbLib::UIndirectList<T>::empty() const
{
	return addressing_.empty();
}


template<class T>
inline T& tnbLib::UIndirectList<T>::first()
{
	return completeList_[addressing_.first()];
}


template<class T>
inline const T& tnbLib::UIndirectList<T>::first() const
{
	return completeList_[addressing_.first()];
}


template<class T>
inline T& tnbLib::UIndirectList<T>::last()
{
	return completeList_[addressing_.last()];
}


template<class T>
inline const T& tnbLib::UIndirectList<T>::last() const
{
	return completeList_[addressing_.last()];
}


template<class T>
inline const tnbLib::UList<T>& tnbLib::UIndirectList<T>::completeList() const
{
	return completeList_;
}


template<class T>
inline const tnbLib::List<tnbLib::label>& tnbLib::UIndirectList<T>::addressing() const
{
	return addressing_;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class T>
inline tnbLib::List<T> tnbLib::UIndirectList<T>::operator()() const
{
	List<T> result(size());

	forAll(*this, i)
	{
		result[i] = operator[](i);
	}

	return result;
}


template<class T>
inline T& tnbLib::UIndirectList<T>::operator[](const label i)
{
	return completeList_[addressing_[i]];
}


template<class T>
inline const T& tnbLib::UIndirectList<T>::operator[](const label i) const
{
	return completeList_[addressing_[i]];
}


template<class T>
inline void tnbLib::UIndirectList<T>::operator=(const UList<T>& ae)
{
	if (addressing_.size() != ae.size())
	{
		FatalErrorInFunction
			<< "Addressing and list of addressed elements "
			"have different sizes: "
			<< addressing_.size() << " " << ae.size()
			<< abort(FatalError);
	}

	forAll(addressing_, i)
	{
		completeList_[addressing_[i]] = ae[i];
	}
}


template<class T>
inline void tnbLib::UIndirectList<T>::operator=(const UIndirectList<T>& ae)
{
	if (addressing_.size() != ae.size())
	{
		FatalErrorInFunction
			<< "Addressing and list of addressed elements "
			"have different sizes: "
			<< addressing_.size() << " " << ae.size()
			<< abort(FatalError);
	}

	forAll(addressing_, i)
	{
		completeList_[addressing_[i]] = ae[i];
	}
}


template<class T>
inline void tnbLib::UIndirectList<T>::operator=(const T& t)
{
	forAll(addressing_, i)
	{
		completeList_[addressing_[i]] = t;
	}
}


// ************************************************************************* //