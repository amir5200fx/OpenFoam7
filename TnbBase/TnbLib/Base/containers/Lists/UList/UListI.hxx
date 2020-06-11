#pragma once
#include <error.hxx>
#include <pTraits.hxx>
#include <Swap.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class T>
inline tnbLib::UList<T>::UList()
	:
	size_(0),
	v_(0)
{}


template<class T>
inline tnbLib::UList<T>::UList(T* __restrict v, label size)
	:
	size_(size),
	v_(v)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class T>
inline const tnbLib::UList<T>& tnbLib::UList<T>::null()
{
	return NullObjectRef<UList<T>>();
}


template<class T>
inline tnbLib::label tnbLib::UList<T>::fcIndex(const label i) const
{
	return (i == size() - 1 ? 0 : i + 1);
}


template<class T>
inline tnbLib::label tnbLib::UList<T>::rcIndex(const label i) const
{
	return (i ? i - 1 : size() - 1);
}


template<class T>
inline void tnbLib::UList<T>::checkStart(const label start) const
{
	if (start < 0 || (start && start >= size_))
	{
		FatalErrorInFunction
			<< "start " << start << " out of range 0 ... " << max(size_ - 1, 0)
			<< abort(FatalError);
	}
}


template<class T>
inline void tnbLib::UList<T>::checkSize(const label size) const
{
	if (size<0 || size>size_)
	{
		FatalErrorInFunction
			<< "size " << size << " out of range 0 ... " << size_
			<< abort(FatalError);
	}
}


template<class T>
inline void tnbLib::UList<T>::checkIndex(const label i) const
{
	if (!size_)
	{
		FatalErrorInFunction
			<< "attempt to access element from zero sized list"
			<< abort(FatalError);
	}
	else if (i < 0 || i >= size_)
	{
		FatalErrorInFunction
			<< "index " << i << " out of range 0 ... " << size_ - 1
			<< abort(FatalError);
	}
}


template<class T>
inline T& tnbLib::UList<T>::first()
{
	return this->operator[](0);
}


template<class T>
inline const T& tnbLib::UList<T>::first() const
{
	return this->operator[](0);
}


template<class T>
inline T& tnbLib::UList<T>::last()
{
	return this->operator[](this->size() - 1);
}


template<class T>
inline const T& tnbLib::UList<T>::last() const
{
	return this->operator[](this->size() - 1);
}


template<class T>
inline const T* tnbLib::UList<T>::cdata() const
{
	return v_;
}


template<class T>
inline T* tnbLib::UList<T>::data()
{
	return v_;
}


template<class T>
inline void tnbLib::UList<T>::shallowCopy(const UList<T>& a)
{
	size_ = a.size_;
	v_ = a.v_;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //


template<class T>
inline T& tnbLib::UList<T>::operator[](const label i)
{
#ifdef FULLDEBUG
	checkIndex(i);
#endif
	return v_[i];
}


namespace tnbLib
{
	// Template specialization for bool
	template<>
	inline const bool& tnbLib::UList<bool>::operator[](const label i) const
	{
		// lazy evaluation - return false for out-of-range
		if (i < size_)
		{
			return v_[i];
		}
		else
		{
			return tnbLib::pTraits<bool>::zero;
		}
	}
}


template<class T>
inline const T& tnbLib::UList<T>::operator[](const label i) const
{
#ifdef FULLDEBUG
	checkIndex(i);
#endif
	return v_[i];
}


template<class T>
inline tnbLib::UList<T>::operator const tnbLib::List<T>&() const
{
	return *reinterpret_cast<const List<T>*>(this);
}


// * * * * * * * * * * * * * * STL Member Functions  * * * * * * * * * * * * //

template<class T>
inline typename tnbLib::UList<T>::iterator
tnbLib::UList<T>::begin()
{
	return v_;
}

template<class T>
inline typename tnbLib::UList<T>::const_iterator
tnbLib::UList<T>::begin() const
{
	return v_;
}

template<class T>
inline typename tnbLib::UList<T>::const_iterator
tnbLib::UList<T>::cbegin() const
{
	return v_;
}

template<class T>
inline typename tnbLib::UList<T>::iterator
tnbLib::UList<T>::end()
{
	return &v_[size_];
}

template<class T>
inline typename tnbLib::UList<T>::const_iterator
tnbLib::UList<T>::end() const
{
	return &v_[size_];
}

template<class T>
inline typename tnbLib::UList<T>::const_iterator
tnbLib::UList<T>::cend() const
{
	return &v_[size_];
}

template<class T>
inline typename tnbLib::UList<T>::iterator
tnbLib::UList<T>::rbegin()
{
	return &v_[size_ - 1];
}

template<class T>
inline typename tnbLib::UList<T>::const_iterator
tnbLib::UList<T>::rbegin() const
{
	return &v_[size_ - 1];
}

template<class T>
inline typename tnbLib::UList<T>::const_iterator
tnbLib::UList<T>::crbegin() const
{
	return &v_[size_ - 1];
}

template<class T>
inline typename tnbLib::UList<T>::iterator
tnbLib::UList<T>::rend()
{
	return &v_[-1];
}

template<class T>
inline typename tnbLib::UList<T>::const_iterator
tnbLib::UList<T>::rend() const
{
	return &v_[-1];
}

template<class T>
inline typename tnbLib::UList<T>::const_iterator
tnbLib::UList<T>::crend() const
{
	return &v_[-1];
}

template<class T>
inline tnbLib::label tnbLib::UList<T>::size() const
{
	return size_;
}


template<class T>
inline tnbLib::label tnbLib::UList<T>::max_size() const
{
	return labelMax;
}


template<class T>
inline bool tnbLib::UList<T>::empty() const
{
	return !size_;
}


// * * * * * * * * * * * * * * * Global Functions  * * * * * * * * * * * * * //

template<class T>
inline void tnbLib::reverse(UList<T>& ul, const label n)
{
	for (int i = 0; i < n / 2; i++)
	{
		Swap(ul[i], ul[n - 1 - i]);
	}
}

template<class T>
inline void tnbLib::reverse(UList<T>& ul)
{
	reverse(ul, ul.size());
}


// ************************************************************************* //