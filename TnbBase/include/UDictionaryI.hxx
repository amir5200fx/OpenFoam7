#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class T>
tnbLib::UDictionary<T>::UDictionary()
{}


template<class T>
tnbLib::UDictionary<T>::UDictionary(const UDictionary& dict)
	:
	DictionaryBase<UIDLList<T>, T>(dict)
{}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// ************************************************************************* //