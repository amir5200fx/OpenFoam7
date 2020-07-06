#pragma once
#include <error.hxx>
#include <typeinfo>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class T>
inline tnbLib::tmpNrc<T>::tmpNrc(T* tPtr)
	:
	type_(TMP),
	ptr_(tPtr)
{}


template<class T>
inline tnbLib::tmpNrc<T>::tmpNrc(const T& tRef)
	:
	type_(CONST_REF),
	ptr_(const_cast<T*>(&tRef))
{}


template<class T>
inline tnbLib::tmpNrc<T>::tmpNrc(const tmpNrc<T>& t)
	:
	type_(t.type_),
	ptr_(t.ptr_)
{
	if (isTmp())
	{
		if (ptr_)
		{
			t.type_ = CONST_REF;
		}
		else
		{
			FatalErrorInFunction
				<< "Attempted copy of a deallocated " << typeName()
				<< abort(FatalError);
		}
	}
}


template<class T>
inline tnbLib::tmpNrc<T>::tmpNrc(const tmpNrc<T>& t, bool allowTransfer)
	:
	type_(t.type_),
	ptr_(t.ptr_)
{
	if (isTmp())
	{
		if (ptr_)
		{
			if (allowTransfer)
			{
				t.ptr_ = 0;
			}
			else
			{
				t.type_ = CONST_REF;
			}
		}
		else
		{
			FatalErrorInFunction
				<< "Attempted copy of a deallocated " << typeName()
				<< abort(FatalError);
		}
	}
}


template<class T>
inline tnbLib::tmpNrc<T>::~tmpNrc()
{
	clear();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class T>
inline bool tnbLib::tmpNrc<T>::isTmp() const
{
	return type_ == TMP;
}


template<class T>
inline bool tnbLib::tmpNrc<T>::empty() const
{
	return (isTmp() && !ptr_);
}


template<class T>
inline bool tnbLib::tmpNrc<T>::valid() const
{
	return (!isTmp() || (isTmp() && ptr_));
}


template<class T>
inline tnbLib::word tnbLib::tmpNrc<T>::typeName() const
{
	return "tmpNrc<" + word(typeid(T).name()) + '>';
}


template<class T>
inline T& tnbLib::tmpNrc<T>::ref()
{
	if (isTmp())
	{
		if (!ptr_)
		{
			FatalErrorInFunction
				<< typeName() << " deallocated"
				<< abort(FatalError);
		}
	}
	else
	{
		FatalErrorInFunction
			<< "Attempt to acquire non-const reference to const object"
			<< " from a " << typeName()
			<< abort(FatalError);
	}

	return *ptr_;
}


template<class T>
inline T* tnbLib::tmpNrc<T>::ptr() const
{
	if (isTmp())
	{
		if (!ptr_)
		{
			FatalErrorInFunction
				<< typeName() << " deallocated"
				<< abort(FatalError);
		}

		T* ptr = ptr_;
		ptr_ = 0;

		return ptr;
	}
	else
	{
		return ptr_->clone().ptr();
	}
}


template<class T>
inline void tnbLib::tmpNrc<T>::clear() const
{
	if (isTmp() && ptr_)
	{
		delete ptr_;
		ptr_ = 0;
	}
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class T>
inline const T& tnbLib::tmpNrc<T>::operator()() const
{
	if (isTmp())
	{
		if (!ptr_)
		{
			FatalErrorInFunction
				<< typeName() << " deallocated"
				<< abort(FatalError);
		}
	}

	// Return const reference
	return *ptr_;
}


template<class T>
inline tnbLib::tmpNrc<T>::operator const T&() const
{
	return operator()();
}


template<class T>
inline T* tnbLib::tmpNrc<T>::operator->()
{
	if (isTmp())
	{
		if (!ptr_)
		{
			FatalErrorInFunction
				<< typeName() << " deallocated"
				<< abort(FatalError);
		}
	}
	else
	{
		FatalErrorInFunction
			<< "Attempt to cast const object to non-const for a " << typeName()
			<< abort(FatalError);
	}

	return ptr_;
}


template<class T>
inline const T* tnbLib::tmpNrc<T>::operator->() const
{
	if (isTmp() && !ptr_)
	{
		FatalErrorInFunction
			<< typeName() << " deallocated"
			<< abort(FatalError);
	}

	return ptr_;
}


template<class T>
inline void tnbLib::tmpNrc<T>::operator=(T* tPtr)
{
	clear();

	if (!tPtr)
	{
		FatalErrorInFunction
			<< "Attempted copy of a deallocated " << typeName()
			<< abort(FatalError);
	}

	type_ = TMP;
	ptr_ = tPtr;
}


template<class T>
inline void tnbLib::tmpNrc<T>::operator=(const tmpNrc<T>& t)
{
	clear();

	if (t.isTmp())
	{
		type_ = TMP;

		if (!t.ptr_)
		{
			FatalErrorInFunction
				<< "Attempted assignment to a deallocated " << typeName()
				<< abort(FatalError);
		}

		ptr_ = t.ptr_;
		t.ptr_ = 0;
	}
	else
	{
		FatalErrorInFunction
			<< "Attempted assignment to a const reference to an object"
			<< " of type " << typeid(T).name()
			<< abort(FatalError);
	}
}


// ************************************************************************* //