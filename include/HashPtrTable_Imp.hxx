#pragma once
#include <error.hxx>
#include <OSstream.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class T, class Key, class Hash>
tnbLib::HashPtrTable<T, Key, Hash>::HashPtrTable(const label size)
	:
	HashTable<T*, Key, Hash>(size)
{}


template<class T, class Key, class Hash>
tnbLib::HashPtrTable<T, Key, Hash>::HashPtrTable
(
	const HashPtrTable<T, Key, Hash>& ht
)
	:
	HashTable<T*, Key, Hash>()
{
	for (const_iterator iter = ht.begin(); iter != ht.end(); ++iter)
	{
		this->insert(iter.key(), new T(**iter));
	}
}


template<class T, class Key, class Hash>
tnbLib::HashPtrTable<T, Key, Hash>::HashPtrTable
(
	HashPtrTable<T, Key, Hash>&& ht
)
	:
	HashTable<T*, Key, Hash>(move(ht))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class T, class Key, class Hash>
tnbLib::HashPtrTable<T, Key, Hash>::~HashPtrTable()
{
	clear();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class T, class Key, class Hash>
T* tnbLib::HashPtrTable<T, Key, Hash>::remove(iterator& it)
{
	T* elemPtr = *it;
	HashTable<T*, Key, Hash>::erase(it);
	return elemPtr;
}


template<class T, class Key, class Hash>
bool tnbLib::HashPtrTable<T, Key, Hash>::erase(iterator& it)
{
	T* elemPtr = *it;

	if (HashTable<T*, Key, Hash>::erase(it))
	{
		if (elemPtr)
		{
			delete elemPtr;
		}

		return true;
	}
	else
	{
		return false;
	}
}


template<class T, class Key, class Hash>
void tnbLib::HashPtrTable<T, Key, Hash>::clear()
{
	for
		(
			iterator iter = this->begin();
			iter != this->end();
			++iter
			)
	{
		delete *iter;
	}

	HashTable<T*, Key, Hash>::clear();
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class T, class Key, class Hash>
void tnbLib::HashPtrTable<T, Key, Hash>::operator=
(
	const HashPtrTable<T, Key, Hash>& rhs
	)
{
	// Check for assignment to self
	if (this == &rhs)
	{
		FatalErrorInFunction
			<< "attempted assignment to self"
			<< abort(FatalError);
	}

	this->clear();

	for (const_iterator iter = rhs.begin(); iter != rhs.end(); ++iter)
	{
		this->insert(iter.key(), new T(**iter));
	}
}


template<class T, class Key, class Hash>
void tnbLib::HashPtrTable<T, Key, Hash>::operator=
(
	HashPtrTable<T, Key, Hash>&& rhs
	)
{
	// Check for assignment to self
	if (this == &rhs)
	{
		FatalErrorInFunction
			<< "attempted assignment to self"
			<< abort(FatalError);
	}

	HashTable<T*, Key, Hash>::operator=(move(rhs));
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //