#pragma once
#include <UList.hxx>
#include <SLList.hxx>
#include <contiguous.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class T, unsigned Size>
inline tnbLib::FixedList<T, Size>::FixedList()
{}


template<class T, unsigned Size>
inline tnbLib::FixedList<T, Size>::FixedList(const T& t)
{
	for (unsigned i = 0; i < Size; i++)
	{
		v_[i] = t;
	}
}


template<class T, unsigned Size>
inline tnbLib::FixedList<T, Size>::FixedList(const T v[Size])
{
	for (unsigned i = 0; i < Size; i++)
	{
		v_[i] = v[i];
	}
}


template<class T, unsigned Size>
template<class InputIterator>
tnbLib::FixedList<T, Size>::FixedList
(
	InputIterator first,
	InputIterator last
)
{
	checkSize(std::distance(first, last));

	InputIterator iter = first;
	for (unsigned i = 0; i < Size; i++)
	{
		v_[i] = *iter++;
	}
}


template<class T, unsigned Size>
inline tnbLib::FixedList<T, Size>::FixedList(std::initializer_list<T> lst)
	:
	FixedList<T, Size>(lst.begin(), lst.end())
{}


template<class T, unsigned Size>
inline tnbLib::FixedList<T, Size>::FixedList(const UList<T>& lst)
{
	checkSize(lst.size());

	for (unsigned i = 0; i < Size; i++)
	{
		v_[i] = lst[i];
	}
}


template<class T, unsigned Size>
inline tnbLib::FixedList<T, Size>::FixedList(const SLList<T>& lst)
{
	checkSize(lst.size());

	typename SLList<T>::const_iterator iter = lst.begin();
	for (unsigned i = 0; i < Size; i++)
	{
		v_[i] = *iter++;
	}
}


template<class T, unsigned Size>
inline tnbLib::autoPtr<tnbLib::FixedList<T, Size>>
tnbLib::FixedList<T, Size>::clone() const
{
	return autoPtr<FixedList<T, Size>>(new FixedList<T, Size>(*this));
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class T, unsigned Size>
inline const tnbLib::FixedList<T, Size>& tnbLib::FixedList<T, Size>::null()
{
	return NullObjectRef<FixedList<T, Size>>();
}


template<class T, unsigned Size>
inline tnbLib::label tnbLib::FixedList<T, Size>::fcIndex(const label i) const
{
	return (i == Size - 1 ? 0 : i + 1);
}


template<class T, unsigned Size>
inline tnbLib::label tnbLib::FixedList<T, Size>::rcIndex(const label i) const
{
	return (i ? i - 1 : Size - 1);
}


template<class T, unsigned Size>
inline void tnbLib::FixedList<T, Size>::checkStart(const label start) const
{
	if (start < 0 || (start && unsigned(start) >= Size))
	{
		FatalErrorInFunction
			<< "start " << start << " out of range 0 ... " << (Size - 1)
			<< abort(FatalError);
	}
}


template<class T, unsigned Size>
inline void tnbLib::FixedList<T, Size>::checkSize(const label size) const
{
	if (unsigned(size) != Size)
	{
		FatalErrorInFunction
			<< "size " << size << " != " << Size
			<< abort(FatalError);
	}
}


template<class T, unsigned Size>
inline void tnbLib::FixedList<T, Size>::checkIndex(const label i) const
{
	if (i < 0 || unsigned(i) >= Size)
	{
		FatalErrorInFunction
			<< "index " << i << " out of range 0 ... " << (Size - 1)
			<< abort(FatalError);
	}
}


template<class T, unsigned Size>
inline void tnbLib::FixedList<T, Size>::resize(const label s)
{
#ifdef FULLDEBUG
	checkSize(s);
#endif
}

template<class T, unsigned Size>
inline void tnbLib::FixedList<T, Size>::setSize(const label s)
{
#ifdef FULLDEBUG
	checkSize(s);
#endif
}

template<class T, unsigned Size>
inline void tnbLib::FixedList<T, Size>::transfer(const FixedList<T, Size>& lst)
{
	for (unsigned i = 0; i < Size; i++)
	{
		v_[i] = lst[i];
	}
}


template<class T, unsigned Size>
inline const T*
tnbLib::FixedList<T, Size>::cdata() const
{
	return v_;
}


template<class T, unsigned Size>
inline T*
tnbLib::FixedList<T, Size>::data()
{
	return v_;
}


template<class T, unsigned Size>
inline T& tnbLib::FixedList<T, Size>::first()
{
	return v_[0];
}


template<class T, unsigned Size>
inline const T& tnbLib::FixedList<T, Size>::first() const
{
	return v_[0];
}


template<class T, unsigned Size>
inline T& tnbLib::FixedList<T, Size>::last()
{
	return v_[Size - 1];
}


template<class T, unsigned Size>
inline const T& tnbLib::FixedList<T, Size>::last() const
{
	return v_[Size - 1];
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class T, unsigned Size>
inline T& tnbLib::FixedList<T, Size>::operator[](const label i)
{
#ifdef FULLDEBUG
	checkIndex(i);
#endif
	return v_[i];
}


template<class T, unsigned Size>
inline const T& tnbLib::FixedList<T, Size>::operator[](const label i) const
{
#ifdef FULLDEBUG
	checkIndex(i);
#endif
	return v_[i];
}


template<class T, unsigned Size>
inline void tnbLib::FixedList<T, Size>::operator=(const T lst[Size])
{
	for (unsigned i = 0; i < Size; i++)
	{
		v_[i] = lst[i];
	}
}

template<class T, unsigned Size>
inline void tnbLib::FixedList<T, Size>::operator=(const UList<T>& lst)
{
	checkSize(lst.size());

	for (unsigned i = 0; i < Size; i++)
	{
		v_[i] = lst[i];
	}
}

template<class T, unsigned Size>
inline void tnbLib::FixedList<T, Size>::operator=(const SLList<T>& lst)
{
	checkSize(lst.size());

	typename SLList<T>::const_iterator iter = lst.begin();
	for (unsigned i = 0; i < Size; i++)
	{
		v_[i] = *iter++;
	}
}

template<class T, unsigned Size>
inline void tnbLib::FixedList<T, Size>::operator=(std::initializer_list<T> lst)
{
	checkSize(lst.size());

	typename std::initializer_list<T>::iterator iter = lst.begin();
	for (unsigned i = 0; i < Size; i++)
	{
		v_[i] = *iter++;
	}
}

template<class T, unsigned Size>
inline void tnbLib::FixedList<T, Size>::operator=(const T& t)
{
	for (unsigned i = 0; i < Size; i++)
	{
		v_[i] = t;
	}
}


// * * * * * * * * * * * * * * STL Member Functions  * * * * * * * * * * * * //

template<class T, unsigned Size>
inline typename tnbLib::FixedList<T, Size>::iterator
tnbLib::FixedList<T, Size>::begin()
{
	return v_;
}


template<class T, unsigned Size>
inline typename tnbLib::FixedList<T, Size>::const_iterator
tnbLib::FixedList<T, Size>::begin() const
{
	return v_;
}


template<class T, unsigned Size>
inline typename tnbLib::FixedList<T, Size>::const_iterator
tnbLib::FixedList<T, Size>::cbegin() const
{
	return v_;
}


template<class T, unsigned Size>
inline typename tnbLib::FixedList<T, Size>::iterator
tnbLib::FixedList<T, Size>::end()
{
	return &v_[Size];
}


template<class T, unsigned Size>
inline typename tnbLib::FixedList<T, Size>::const_iterator
tnbLib::FixedList<T, Size>::end() const
{
	return &v_[Size];
}


template<class T, unsigned Size>
inline typename tnbLib::FixedList<T, Size>::const_iterator
tnbLib::FixedList<T, Size>::cend() const
{
	return &v_[Size];
}


template<class T, unsigned Size>
inline typename tnbLib::FixedList<T, Size>::iterator
tnbLib::FixedList<T, Size>::rbegin()
{
	return &v_[Size - 1];
}


template<class T, unsigned Size>
inline typename tnbLib::FixedList<T, Size>::const_iterator
tnbLib::FixedList<T, Size>::rbegin() const
{
	return &v_[Size - 1];
}


template<class T, unsigned Size>
inline typename tnbLib::FixedList<T, Size>::const_iterator
tnbLib::FixedList<T, Size>::crbegin() const
{
	return &v_[Size - 1];
}


template<class T, unsigned Size>
inline typename tnbLib::FixedList<T, Size>::iterator
tnbLib::FixedList<T, Size>::rend()
{
	return &v_[-1];
}


template<class T, unsigned Size>
inline typename tnbLib::FixedList<T, Size>::const_iterator
tnbLib::FixedList<T, Size>::rend() const
{
	return &v_[-1];
}


template<class T, unsigned Size>
inline typename tnbLib::FixedList<T, Size>::const_iterator
tnbLib::FixedList<T, Size>::crend() const
{
	return &v_[-1];
}


template<class T, unsigned Size>
inline tnbLib::label tnbLib::FixedList<T, Size>::size() const
{
	return Size;
}


template<class T, unsigned Size>
inline tnbLib::label tnbLib::FixedList<T, Size>::max_size() const
{
	return Size;
}


template<class T, unsigned Size>
inline bool tnbLib::FixedList<T, Size>::empty() const
{
	return false;
}


template<class T, unsigned Size>
template<class HashT>
inline unsigned tnbLib::FixedList<T, Size>::Hash<HashT>::operator()
(
	const FixedList<T, Size>& lst,
	unsigned seed
	) const
{
	if (contiguous<T>())
	{
		// Hash directly
		return Hasher(lst.v_, sizeof(lst.v_), seed);
	}
	else
	{
		// Hash incrementally
		unsigned val = seed;

		for (unsigned i = 0; i < Size; i++)
		{
			val = HashT()(lst[i], val);
		}

		return val;
	}
}


// ************************************************************************* //