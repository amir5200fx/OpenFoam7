#pragma once
#include <autoPtr.hxx>
#include <tmp.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class T>
inline void tnbLib::PtrList<T>::resize(const label newSize)
{
	this->setSize(newSize);
}


template<class T>
inline void tnbLib::PtrList<T>::append(T* ptr)
{
	label sz = this->size();
	this->setSize(sz + 1);
	this->ptrs_[sz] = ptr;
}


template<class T>
inline void tnbLib::PtrList<T>::append(const autoPtr<T>& aptr)
{
	return append(const_cast<autoPtr<T>&>(aptr).ptr());
}


template<class T>
inline void tnbLib::PtrList<T>::append
(
	const tmp<T>& t
)
{
	return append(const_cast<tmp<T>&>(t).ptr());
}


template<class T>
inline bool tnbLib::PtrList<T>::set(const label i) const
{
	return this->ptrs_[i] != nullptr;
}


template<class T>
inline tnbLib::autoPtr<T> tnbLib::PtrList<T>::set(const label i, T* ptr)
{
	autoPtr<T> old(this->ptrs_[i]);
	this->ptrs_[i] = ptr;
	return old;
}


template<class T>
inline tnbLib::autoPtr<T> tnbLib::PtrList<T>::set
(
	const label i,
	const autoPtr<T>& aptr
)
{
	return set(i, const_cast<autoPtr<T>&>(aptr).ptr());
}


template<class T>
inline tnbLib::autoPtr<T> tnbLib::PtrList<T>::set
(
	const label i,
	const tmp<T>& t
)
{
	return set(i, const_cast<tmp<T>&>(t).ptr());
}


// ************************************************************************* //