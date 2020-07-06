#pragma once
#include <error.hxx>
#include <typeinfo>

// * * * * * * * * * * * * * Private Member Operators  * * * * * * * * * * * //

template<class T>
inline void tnbLib::tmp<T>::operator++()
{
	ptr_->operator++();

	if (ptr_->count() > 1)
	{
		FatalErrorInFunction
			<< "Attempt to create more than 2 tmp's referring to"
			" the same object of type " << typeName()
			<< abort(FatalError);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class T>
inline tnbLib::tmp<T>::tmp(T* tPtr)
	:
	type_(TMP),
	ptr_(tPtr)
{
	if (tPtr && !tPtr->unique())
	{
		FatalErrorInFunction
			<< "Attempted construction of a " << typeName()
			<< " from non-unique pointer"
			<< abort(FatalError);
	}
}


template<class T>
inline tnbLib::tmp<T>::tmp(const T& tRef)
	:
	type_(CONST_REF),
	ptr_(const_cast<T*>(&tRef))
{}


template<class T>
inline tnbLib::tmp<T>::tmp(const tmp<T>& t)
	:
	type_(t.type_),
	ptr_(t.ptr_)
{
	if (isTmp())
	{
		if (ptr_)
		{
			operator++();
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
inline tnbLib::tmp<T>::tmp(const tmp<T>&& t)
	:
	type_(t.type_),
	ptr_(t.ptr_)
{
	if (isTmp())
	{
		t.ptr_ = 0;
	}
}


template<class T>
inline tnbLib::tmp<T>::tmp(const tmp<T>& t, bool allowTransfer)
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
				operator++();
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
inline tnbLib::tmp<T>::~tmp()
{
	clear();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class T>
inline bool tnbLib::tmp<T>::isTmp() const
{
	return type_ == TMP;
}


template<class T>
inline bool tnbLib::tmp<T>::empty() const
{
	return (isTmp() && !ptr_);
}


template<class T>
inline bool tnbLib::tmp<T>::valid() const
{
	return (!isTmp() || (isTmp() && ptr_));
}


template<class T>
inline tnbLib::word tnbLib::tmp<T>::typeName() const
{
	return "tmp<" + word(typeid(T).name()) + '>';
}


template<class T>
inline T& tnbLib::tmp<T>::ref() const
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
inline T* tnbLib::tmp<T>::ptr() const
{
	if (isTmp())
	{
		if (!ptr_)
		{
			FatalErrorInFunction
				<< typeName() << " deallocated"
				<< abort(FatalError);
		}

		if (!ptr_->unique())
		{
			FatalErrorInFunction
				<< "Attempt to acquire pointer to object referred to"
				<< " by multiple temporaries of type " << typeName()
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
inline void tnbLib::tmp<T>::clear() const
{
	if (isTmp() && ptr_)
	{
		if (ptr_->unique())
		{
			delete ptr_;
			ptr_ = 0;
		}
		else
		{
			ptr_->operator--();
			ptr_ = 0;
		}
	}
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

#ifdef NON_CONST_TMP
template<class T>
inline T& tnbLib::tmp<T>::operator()()
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

	// Const-ness is automatically cast-away which is why this operator is
	// deprecated.  Use ref() where non-const access is required.
	return *ptr_;
}
#endif


template<class T>
inline const T& tnbLib::tmp<T>::operator()() const
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
inline tnbLib::tmp<T>::operator const T&() const
{
	return operator()();
}


template<class T>
inline T* tnbLib::tmp<T>::operator->()
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
inline const T* tnbLib::tmp<T>::operator->() const
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
inline void tnbLib::tmp<T>::operator=(T* tPtr)
{
	clear();

	if (!tPtr)
	{
		FatalErrorInFunction
			<< "Attempted copy of a deallocated " << typeName()
			<< abort(FatalError);
	}

	if (tPtr && !tPtr->unique())
	{
		FatalErrorInFunction
			<< "Attempted assignment of a " << typeName()
			<< " to non-unique pointer"
			<< abort(FatalError);
	}

	type_ = TMP;
	ptr_ = tPtr;
}


template<class T>
inline void tnbLib::tmp<T>::operator=(const tmp<T>& t)
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