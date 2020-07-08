#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class T>
inline tnbLib::SubList<T>::SubList
(
	const UList<T>& list,
	const label subSize
)
	:
	UList<T>(list.v_, subSize)
{
#ifdef FULLDEBUG
	list.checkSize(subSize);
#endif
}


template<class T>
inline tnbLib::SubList<T>::SubList
(
	const UList<T>& list,
	const label subSize,
	const label startIndex
)
	:
	UList<T>(&(list.v_[startIndex]), subSize)
{
#ifdef FULLDEBUG

	// Artificially allow the start of a zero-sized subList to be
	// one past the end of the original list.
	if (subSize)
	{
		list.checkStart(startIndex);
		list.checkSize(startIndex + subSize);
	}
	else
	{
		// Start index needs to fall between 0 and size.  One position
		// behind the last element is allowed
		list.checkSize(startIndex);
	}
#endif
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class T>
inline const tnbLib::SubList<T>& tnbLib::SubList<T>::null()
{
	return NullObjectRef<SubList<T>>();
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class T>
inline tnbLib::SubList<T>::operator const tnbLib::List<T>&() const
{
	return *reinterpret_cast<const List<T>*>(this);
}


template<class T>
inline void tnbLib::SubList<T>::operator=(const SubList<T>& sl)
{
	UList<T>::deepCopy(sl);
}


template<class T>
inline void tnbLib::SubList<T>::operator=(const UList<T>& l)
{
	UList<T>::deepCopy(l);
}


template<class T>
inline void tnbLib::SubList<T>::operator=(const T& t)
{
	UList<T>::operator=(t);
}


// ************************************************************************* //