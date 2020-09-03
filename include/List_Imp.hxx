#pragma once
#include <ListLoopM.hxx>
#include <FixedList.hxx>
//#include <PtrList.hxx>
#include <SLList.hxx>
#include <IndirectList.hxx>
#include <UIndirectList.hxx>
#include <BiIndirectList.hxx>
#include <contiguous.hxx>

// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

template<class T>
tnbLib::List<T>::List(const label s)
	:
	UList<T>(nullptr, s)
{
	if (this->size_ < 0)
	{
		FatalErrorInFunction
			<< "bad size " << this->size_
			<< abort(FatalError);
	}

	alloc();
}


template<class T>
tnbLib::List<T>::List(const label s, const T& a)
	:
	UList<T>(nullptr, s)
{
	if (this->size_ < 0)
	{
		FatalErrorInFunction
			<< "bad size " << this->size_
			<< abort(FatalError);
	}

	alloc();

	if (this->size_)
	{
		List_ACCESS(T, (*this), vp);
		List_FOR_ALL((*this), i)
			List_ELEM((*this), vp, i) = a;
		List_END_FOR_ALL
	}
}


template<class T>
tnbLib::List<T>::List(const label s, const zero)
	:
	UList<T>(nullptr, s)
{
	if (this->size_ < 0)
	{
		FatalErrorInFunction
			<< "bad size " << this->size_
			<< abort(FatalError);
	}

	alloc();

	if (this->size_)
	{
		List_ACCESS(T, (*this), vp);
		List_FOR_ALL((*this), i)
			List_ELEM((*this), vp, i) = Zero;
		List_END_FOR_ALL
	}
}


template<class T>
tnbLib::List<T>::List(const List<T>& a)
	:
	UList<T>(nullptr, a.size_)
{
	if (this->size_)
	{
		alloc();

#ifdef USEMEMCPY
		if (contiguous<T>())
		{
			memcpy(this->v_, a.v_, this->byteSize());
		}
		else
#endif
		{
			List_ACCESS(T, (*this), vp);
			List_CONST_ACCESS(T, a, ap);
			List_FOR_ALL((*this), i)
				List_ELEM((*this), vp, i) = List_ELEM(a, ap, i);
			List_END_FOR_ALL
		}
	}
}


template<class T>
template<class T2>
tnbLib::List<T>::List(const List<T2>& a)
	:
	UList<T>(nullptr, a.size())
{
	if (this->size_)
	{
		alloc();

		List_ACCESS(T, (*this), vp);
		List_CONST_ACCESS(T2, a, ap);
		List_FOR_ALL((*this), i)
			List_ELEM((*this), vp, i) = T(List_ELEM(a, ap, i));
		List_END_FOR_ALL
	}
}


template<class T>
tnbLib::List<T>::List(List<T>&& lst)
{
	transfer(lst);
}


template<class T>
tnbLib::List<T>::List(List<T>& a, bool reuse)
	:
	UList<T>(nullptr, a.size_)
{
	if (reuse)
	{
		this->v_ = a.v_;
		a.v_ = 0;
		a.size_ = 0;
	}
	else if (this->size_)
	{
		alloc();

#ifdef USEMEMCPY
		if (contiguous<T>())
		{
			memcpy(this->v_, a.v_, this->byteSize());
		}
		else
#endif
		{
			List_ACCESS(T, (*this), vp);
			List_CONST_ACCESS(T, a, ap);
			List_FOR_ALL((*this), i)
				List_ELEM((*this), vp, i) = List_ELEM(a, ap, i);
			List_END_FOR_ALL
		}
	}
}


template<class T>
tnbLib::List<T>::List(const UList<T>& a, const labelUList& map)
	:
	UList<T>(nullptr, map.size())
{
	if (this->size_)
	{
		// Note:cannot use List_ELEM since third argument has to be index.

		alloc();

		forAll(*this, i)
		{
			this->operator[](i) = a[map[i]];
		}
	}
}


template<class T>
template<class InputIterator>
tnbLib::List<T>::List(InputIterator first, InputIterator last)
	:
	List<T>(first, last, std::distance(first, last))
{}


template<class T>
template<unsigned Size>
tnbLib::List<T>::List(const FixedList<T, Size>& lst)
	:
	UList<T>(nullptr, Size)
{
	allocCopyList(lst);
}


//template<class T>
//tnbLib::List<T>::List(const PtrList<T>& lst)
//	:
//	UList<T>(nullptr, lst.size())
//{
//	allocCopyList(lst);
//}


template<class T>
tnbLib::List<T>::List(const SLList<T>& lst)
	:
	List<T>(lst.first(), lst.last(), lst.size())
{}


template<class T>
tnbLib::List<T>::List(const UIndirectList<T>& lst)
	:
	UList<T>(nullptr, lst.size())
{
	allocCopyList(lst);
}


template<class T>
tnbLib::List<T>::List(const BiIndirectList<T>& lst)
	:
	UList<T>(nullptr, lst.size())
{
	allocCopyList(lst);
}


template<class T>
tnbLib::List<T>::List(std::initializer_list<T> lst)
	:
	List<T>(lst.begin(), lst.end())
{}


// * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * * //

template<class T>
tnbLib::List<T>::~List()
{
	if (this->v_)
	{
		delete[] this->v_;
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class T>
void tnbLib::List<T>::setSize(const label newSize)
{
	if (newSize < 0)
	{
		FatalErrorInFunction
			<< "bad size " << newSize
			<< abort(FatalError);
	}

	if (newSize != this->size_)
	{
		if (newSize > 0)
		{
			T* nv = new T[label(newSize)];

			if (this->size_)
			{
				label i = min(this->size_, newSize);

#ifdef USEMEMCPY
				if (contiguous<T>())
				{
					memcpy(nv, this->v_, i * sizeof(T));
				}
				else
#endif
				{
					T* vv = &this->v_[i];
					T* av = &nv[i];
					while (i--) *--av = *--vv;
				}
			}

			clear();
			this->size_ = newSize;
			this->v_ = nv;
		}
		else
		{
			clear();
		}
	}
}


template<class T>
void tnbLib::List<T>::setSize(const label newSize, const T& a)
{
	label oldSize = label(this->size_);
	this->setSize(newSize);

	if (newSize > oldSize)
	{
		label i = newSize - oldSize;
		T* vv = &this->v_[newSize];
		while (i--) *--vv = a;
	}
}


template<class T>
void tnbLib::List<T>::transfer(List<T>& a)
{
	clear();
	this->size_ = a.size_;
	this->v_ = a.v_;

	a.size_ = 0;
	a.v_ = 0;
}


template<class T>
template<unsigned SizeInc, unsigned SizeMult, unsigned SizeDiv>
void tnbLib::List<T>::transfer(DynamicList<T, SizeInc, SizeMult, SizeDiv>& a)
{
	// Shrink the allocated space to the number of elements used
	a.shrink();
	transfer(static_cast<List<T>&>(a));
	a.clearStorage();
}


template<class T>
void tnbLib::List<T>::transfer(SortableList<T>& a)
{
	// Shrink away the sort indices
	a.shrink();
	transfer(static_cast<List<T>&>(a));
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class T>
void tnbLib::List<T>::operator=(const UList<T>& a)
{
	reAlloc(a.size_);

	if (this->size_)
	{
#ifdef USEMEMCPY
		if (contiguous<T>())
		{
			memcpy(this->v_, a.v_, this->byteSize());
		}
		else
#endif
		{
			List_ACCESS(T, (*this), vp);
			List_CONST_ACCESS(T, a, ap);
			List_FOR_ALL((*this), i)
				List_ELEM((*this), vp, i) = List_ELEM(a, ap, i);
			List_END_FOR_ALL
		}
	}
}


template<class T>
void tnbLib::List<T>::operator=(const List<T>& a)
{
	if (this == &a)
	{
		FatalErrorInFunction
			<< "attempted assignment to self"
			<< abort(FatalError);
	}

	operator=(static_cast<const UList<T>&>(a));
}


template<class T>
void tnbLib::List<T>::operator=(List<T>&& a)
{
	if (this == &a)
	{
		FatalErrorInFunction
			<< "attempted assignment to self"
			<< abort(FatalError);
	}

	transfer(a);
}


template<class T>
void tnbLib::List<T>::operator=(const SLList<T>& lst)
{
	reAlloc(lst.size());

	if (this->size_)
	{
		label i = 0;
		for
			(
				typename SLList<T>::const_iterator iter = lst.begin();
				iter != lst.end();
				++iter
				)
		{
			this->operator[](i++) = iter();
		}
	}
}


template<class T>
void tnbLib::List<T>::operator=(const UIndirectList<T>& lst)
{
	reAlloc(lst.size());
	copyList(lst);
}


template<class T>
void tnbLib::List<T>::operator=(const BiIndirectList<T>& lst)
{
	reAlloc(lst.size());
	copyList(lst);
}


template<class T>
void tnbLib::List<T>::operator=(std::initializer_list<T> lst)
{
	reAlloc(lst.size());

	typename std::initializer_list<T>::iterator iter = lst.begin();
	forAll(*this, i)
	{
		this->operator[](i) = *iter++;
	}
}


// * * * * * * * * * * * * * * * *  IOStream operators * * * * * * * * * * * //