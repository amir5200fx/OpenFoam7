#pragma once
#include <error.hxx>
#include <typeinfo>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class T>
inline tnbLib::UautoPtr<T>::UautoPtr(T* p)
	:
	ptr_(p)
{}


template<class T>
inline tnbLib::UautoPtr<T>::UautoPtr(const UautoPtr<T>& ap)
	:
	ptr_(ap.ptr_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class T>
inline bool tnbLib::UautoPtr<T>::empty() const
{
	return !ptr_;
}


template<class T>
inline bool tnbLib::UautoPtr<T>::valid() const
{
	return ptr_;
}


template<class T>
inline T* tnbLib::UautoPtr<T>::ptr()
{
	return ptr_;
}


template<class T>
inline void tnbLib::UautoPtr<T>::set(T* p)
{
	if (ptr_)
	{
		FatalErrorInFunction
			<< "object of type " << typeid(T).name()
			<< " already allocated"
			<< abort(FatalError);
	}

	ptr_ = p;
}


template<class T>
inline void tnbLib::UautoPtr<T>::reset(T* p)
{
	ptr_ = p;
}


template<class T>
inline void tnbLib::UautoPtr<T>::clear()
{
	reset(nullptr);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class T>
inline T& tnbLib::UautoPtr<T>::operator()()
{
	if (!ptr_)
	{
		FatalErrorInFunction
			<< "object of type " << typeid(T).name()
			<< " is not allocated"
			<< abort(FatalError);
	}

	return *ptr_;
}


template<class T>
inline const T& tnbLib::UautoPtr<T>::operator()() const
{
	if (!ptr_)
	{
		FatalErrorInFunction
			<< "object of type " << typeid(T).name()
			<< " is not allocated"
			<< abort(FatalError);
	}

	return *ptr_;
}


template<class T>
inline T& tnbLib::UautoPtr<T>::operator*()
{
	if (!ptr_)
	{
		FatalErrorInFunction
			<< "object of type " << typeid(T).name()
			<< " is not allocated"
			<< abort(FatalError);
	}

	return *ptr_;
}


template<class T>
inline const T& tnbLib::UautoPtr<T>::operator*() const
{
	if (!ptr_)
	{
		FatalErrorInFunction
			<< "object of type " << typeid(T).name()
			<< " is not allocated"
			<< abort(FatalError);
	}

	return *ptr_;
}


template<class T>
inline tnbLib::UautoPtr<T>::operator const T&() const
{
	return operator()();
}


template<class T>
inline T* tnbLib::UautoPtr<T>::operator->()
{
	if (!ptr_)
	{
		FatalErrorInFunction
			<< "object of type " << typeid(T).name()
			<< " is not allocated"
			<< abort(FatalError);
	}

	return ptr_;
}


template<class T>
inline const T* tnbLib::UautoPtr<T>::operator->() const
{
	return const_cast<UautoPtr<T>&>(*this).operator->();
}


template<class T>
inline void tnbLib::UautoPtr<T>::operator=(T* p)
{
	reset(p);
}


template<class T>
inline void tnbLib::UautoPtr<T>::operator=(const UautoPtr<T>& ap)
{
	if (this != &ap)
	{
		reset(const_cast<UautoPtr<T>&>(ap).ptr());
	}
}


// ************************************************************************* //