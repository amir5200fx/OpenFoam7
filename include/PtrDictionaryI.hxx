#pragma once

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class T>
tnbLib::PtrDictionary<T>::PtrDictionary(const label size)
	:
	DictionaryBase<DLPtrList<T>, T>(size)
{}


template<class T>
tnbLib::PtrDictionary<T>::PtrDictionary(const PtrDictionary& dict)
	:
	DictionaryBase<DLPtrList<T>, T>(dict)
{}


template<class T>
tnbLib::PtrDictionary<T>::PtrDictionary(PtrDictionary&& dict)
	:
	DictionaryBase<DLPtrList<T>, T>(move(dict))
{}


template<class T>
template<class INew>
tnbLib::PtrDictionary<T>::PtrDictionary(Istream& is, const INew& iNew)
	:
	DictionaryBase<DLPtrList<T>, T>(is, iNew)
{}


template<class T>
tnbLib::PtrDictionary<T>::PtrDictionary(Istream& is)
	:
	DictionaryBase<DLPtrList<T>, T>(is)
{}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// ************************************************************************* //