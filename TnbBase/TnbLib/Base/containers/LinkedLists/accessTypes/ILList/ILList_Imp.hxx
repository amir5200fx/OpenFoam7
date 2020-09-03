#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class LListBase, class T>
tnbLib::ILList<LListBase, T>::ILList(const ILList<LListBase, T>& lst)
{
	for
		(
			typename UILList<LListBase, T>::const_iterator iter = lst.begin();
			iter != lst.end();
			++iter
			)
	{
		this->append(iter().clone().ptr());
	}
}


template<class LListBase, class T>
tnbLib::ILList<LListBase, T>::ILList(ILList<LListBase, T>&& lst)
{
	transfer(lst);
}


template<class LListBase, class T>
template<class CloneArg>
tnbLib::ILList<LListBase, T>::ILList
(
	const ILList<LListBase, T>& lst,
	const CloneArg& cloneArg
)
	:
	UILList<LListBase, T>()
{
	for
		(
			typename UILList<LListBase, T>::const_iterator iter = lst.begin();
			iter != lst.end();
			++iter
			)
	{
		this->append(iter().clone(cloneArg).ptr());
	}
}


// * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * * //

template<class LListBase, class T>
tnbLib::ILList<LListBase, T>::~ILList()
{
	this->clear();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class LListBase, class T>
bool tnbLib::ILList<LListBase, T>::eraseHead()
{
	T* tPtr;
	if ((tPtr = this->removeHead()))
	{
		delete tPtr;
		return true;
	}
	else
	{
		return false;
	}
}

template<class LListBase, class T>
bool tnbLib::ILList<LListBase, T>::erase(T* p)
{
	T* tPtr;
	if ((tPtr = remove(p)))
	{
		delete tPtr;
		return true;
	}
	else
	{
		return false;
	}
}


template<class LListBase, class T>
void tnbLib::ILList<LListBase, T>::clear()
{
	label oldSize = this->size();
	for (label i = 0; i < oldSize; ++i)
	{
		eraseHead();
	}

	LListBase::clear();
}


template<class LListBase, class T>
void tnbLib::ILList<LListBase, T>::transfer(ILList<LListBase, T>& lst)
{
	clear();
	LListBase::transfer(lst);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class LListBase, class T>
void tnbLib::ILList<LListBase, T>::operator=(const ILList<LListBase, T>& lst)
{
	this->clear();

	for
		(
			typename UILList<LListBase, T>::const_iterator iter = lst.begin();
			iter != lst.end();
			++iter
			)
	{
		this->append(iter().clone().ptr());
	}
}


template<class LListBase, class T>
void tnbLib::ILList<LListBase, T>::operator=(ILList<LListBase, T>&& lst)
{
	transfer(lst);
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //