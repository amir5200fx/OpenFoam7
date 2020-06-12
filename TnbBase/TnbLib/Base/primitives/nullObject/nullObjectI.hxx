#pragma once
template<class T>
inline const T& tnbLib::NullObjectRef()
{
	return *reinterpret_cast<const T*>(nullObjectPtr);
}

template<class T>
inline T&& tnbLib::NullObjectMove()
{
	return move(const_cast<T&>(*reinterpret_cast<const T*>(nullObjectPtr)));
}

template<class T>
inline const T* tnbLib::NullObjectPtr()
{
	return reinterpret_cast<const T*>(nullObjectPtr);
}


template<class T>
inline bool tnbLib::isNull(const T& t)
{
	return &t == NullObjectPtr<T>();
}

template<class T>
inline bool tnbLib::notNull(const T& t)
{
	return &t != NullObjectPtr<T>();
}


template<class T>
inline bool tnbLib::isNull(const T* t)
{
	return t == NullObjectPtr<T>();
}

template<class T>
inline bool tnbLib::notNull(const T* t)
{
	return t != NullObjectPtr<T>();
}


// ************************************************************************* //