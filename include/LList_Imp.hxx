#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class LListBase, class T>
tnbLib::LList<LListBase, T>::LList(const LList<LListBase, T>& lst)
	:
	LListBase()
{
	for (const T& val : lst)
	{
		this->append(val);
	}
}


template<class LListBase, class T>
tnbLib::LList<LListBase, T>::LList(LList<LListBase, T>&& lst)
	:
	LListBase()
{
	transfer(lst);
}


template<class LListBase, class T>
tnbLib::LList<LListBase, T>::LList(std::initializer_list<T> lst)
	:
	LListBase()
{
	for (const T& val : lst)
	{
		this->append(val);
	}
}


template<class LListBase, class T>
tnbLib::LList<LListBase, T>::~LList()
{
	this->clear();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class LListBase, class T>
void tnbLib::LList<LListBase, T>::clear()
{
	label oldSize = this->size();
	for (label i = 0; i < oldSize; ++i)
	{
		this->removeHead();
	}

	LListBase::clear();
}


template<class LListBase, class T>
void tnbLib::LList<LListBase, T>::transfer(LList<LListBase, T>& lst)
{
	clear();
	LListBase::transfer(lst);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class LListBase, class T>
void tnbLib::LList<LListBase, T>::operator=(const LList<LListBase, T>& lst)
{
	this->clear();

	for (const T& val : lst)
	{
		this->append(val);
	}
}


template<class LListBase, class T>
void tnbLib::LList<LListBase, T>::operator=(LList<LListBase, T>&& lst)
{
	transfer(lst);
}


template<class LListBase, class T>
void tnbLib::LList<LListBase, T>::operator=(std::initializer_list<T> lst)
{
	this->clear();

	for (const T& val : lst)
	{
		this->append(val);
	}
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //