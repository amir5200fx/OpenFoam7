#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class T>
tnbLib::UPtrDictionary<T>::UPtrDictionary(const label size)
	:
	DictionaryBase<DLList<T*>, T>(size)
{}


template<class T>
tnbLib::UPtrDictionary<T>::UPtrDictionary(const UPtrDictionary& dict)
	:
	DictionaryBase<DLList<T*>, T>(dict)
{}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// ************************************************************************* //