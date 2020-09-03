#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class T>
tnbLib::PtrListDictionary<T>::PtrListDictionary(const label size)
	:
	DictionaryBase<PtrList<T>, T>(2 * size)
{
	PtrList<T>::setSize(size);
}


template<class T>
tnbLib::PtrListDictionary<T>::PtrListDictionary(const PtrListDictionary& dict)
	:
	DictionaryBase<PtrList<T>, T>(dict)
{}


template<class T>
tnbLib::PtrListDictionary<T>::PtrListDictionary(PtrListDictionary&& dict)
	:
	DictionaryBase<PtrList<T>, T>(move(dict))
{}


template<class T>
template<class INew>
tnbLib::PtrListDictionary<T>::PtrListDictionary(Istream& is, const INew& iNew)
	:
	DictionaryBase<PtrList<T>, T>(is, iNew)
{}


template<class T>
tnbLib::PtrListDictionary<T>::PtrListDictionary(Istream& is)
	:
	DictionaryBase<PtrList<T>, T>(is)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class T>
inline tnbLib::autoPtr<T> tnbLib::PtrListDictionary<T>::set
(
	const label i,
	const word& key,
	T* ptr
)
{
	if (!DictionaryBase<PtrList<T>, T>::hashedTs_.insert(key, ptr))
	{
		FatalErrorInFunction
			<< "Cannot insert with key '" << key << "' into hash-table"
			<< abort(FatalError);
	}
	return PtrList<T>::set(i, ptr);
}


template<class T>
inline tnbLib::autoPtr<T> tnbLib::PtrListDictionary<T>::set
(
	const label i,
	const word& key,
	autoPtr<T>& aptr
)
{
	T* ptr = aptr.ptr();
	if (!DictionaryBase<PtrList<T>, T>::hashedTs_.insert(key, ptr))
	{
		FatalErrorInFunction
			<< "Cannot insert with key '" << key << "' into hash-table"
			<< abort(FatalError);
	}
	return PtrList<T>::set(i, ptr);
}


template<class T>
inline tnbLib::autoPtr<T> tnbLib::PtrListDictionary<T>::set
(
	const label i,
	const word& key,
	tmp<T>& t
)
{
	T* ptr = t.ptr();
	if (!DictionaryBase<PtrList<T>, T>::hashedTs_.insert(key, ptr))
	{
		FatalErrorInFunction
			<< "Cannot insert with key '" << key << "' into hash-table"
			<< abort(FatalError);
	}
	return PtrList<T>::set(i, ptr);
}


// ************************************************************************* //