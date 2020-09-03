#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class T>
tnbLib::Dictionary<T>::Dictionary(const label size)
	:
	DictionaryBase<IDLList<T>, T>(size)
{}


template<class T>
tnbLib::Dictionary<T>::Dictionary(const Dictionary& dict)
	:
	DictionaryBase<IDLList<T>, T>(dict)
{}


template<class T>
tnbLib::Dictionary<T>::Dictionary(Dictionary&& dict)
	:
	DictionaryBase<IDLList<T>, T>(move(dict))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class T>
bool tnbLib::Dictionary<T>::erase(const word& keyword)
{
	T* tPtr = this->remove(keyword);

	if (tPtr)
	{
		delete tPtr;
		return true;
	}
	else
	{
		return false;
	}
}


// ************************************************************************* //