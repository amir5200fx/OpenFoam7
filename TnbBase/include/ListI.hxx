#pragma once
// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class T>
inline void tnbLib::List<T>::alloc()
{
	if (this->size_ > 0)
	{
		this->v_ = new T[this->size_];
	}
}


template<class T>
inline void tnbLib::List<T>::reAlloc(const label s)
{
	if (this->size_ != s)
	{
		clear();
		this->size_ = s;
		alloc();
	}
}


template<class T>
template<class List2>
inline void tnbLib::List<T>::copyList(const List2& lst)
{
	if (this->size_)
	{
		forAll(*this, i)
		{
			this->operator[](i) = lst[i];
		}
	}
}


template<class T>
template<class List2>
inline void tnbLib::List<T>::allocCopyList(const List2& lst)
{
	if (this->size_)
	{
		alloc();
		copyList(lst);
	}
}


template<class T>
template<class InputIterator>
inline tnbLib::List<T>::List
(
	InputIterator first,
	InputIterator last,
	const label s
)
	:
	UList<T>(nullptr, s)
{
	if (this->size_)
	{
		alloc();

		InputIterator iter = first;
		forAll(*this, i)
		{
			this->operator[](i) = *iter++;
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class T>
inline tnbLib::List<T>::List()
{}


template<class T>
inline tnbLib::autoPtr<tnbLib::List<T>> tnbLib::List<T>::clone() const
{
	return autoPtr<List<T>>(new List<T>(*this));
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class T>
inline const tnbLib::List<T>& tnbLib::List<T>::null()
{
	return NullObjectRef<List<T>>();
}


template<class T>
inline void tnbLib::List<T>::clear()
{
	if (this->v_)
	{
		delete[] this->v_;
		this->v_ = 0;
	}

	this->size_ = 0;
}


template<class T>
inline void tnbLib::List<T>::resize(const label newSize)
{
	this->setSize(newSize);
}


template<class T>
inline void tnbLib::List<T>::resize(const label newSize, const T& a)
{
	this->setSize(newSize, a);
}


template<class T>
inline T& tnbLib::List<T>::newElmt(const label i)
{
	if (i >= this->size())
	{
		setSize(2 * this->size());
	}

	return UList<T>::operator[](i);
}


template<class T>
inline void tnbLib::List<T>::size(const label n)
{
	UList<T>::size_ = n;
}


template<class T>
inline tnbLib::label tnbLib::List<T>::size() const
{
	return UList<T>::size_;
}


template<class T>
inline void tnbLib::List<T>::append(const T& t)
{
	setSize(size() + 1, t);
}


template<class T>
inline void tnbLib::List<T>::append(const UList<T>& lst)
{
	if (this == &lst)
	{
		FatalErrorInFunction
			<< "attempted appending to self" << abort(FatalError);
	}

	label nextFree = this->size();
	setSize(nextFree + lst.size());

	forAll(lst, elemI)
	{
		this->operator[](nextFree++) = lst[elemI];
	}
}


template<class T>
inline void tnbLib::List<T>::append(const UIndirectList<T>& lst)
{
	label nextFree = this->size();
	setSize(nextFree + lst.size());

	forAll(lst, elemI)
	{
		this->operator[](nextFree++) = lst[elemI];
	}
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class T>
inline void tnbLib::List<T>::operator=(const T& t)
{
	UList<T>::operator=(t);
}


template<class T>
inline void tnbLib::List<T>::operator=(const zero)
{
	UList<T>::operator=(Zero);
}


// ************************************************************************* //