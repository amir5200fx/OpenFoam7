#pragma once
#include <IOstreams.hxx>

// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

template<class T, class Key, class Hash>
inline tnbLib::label
tnbLib::ListHashTable<T, Key, Hash>::hashKeyIndex(const Key& key) const
{
	// size is power of two - this is the modulus
	return Hash()(key) & (keys_.size() - 1);
}


// * * * * * * * * * * * * * * * Member Functions * * * * * * * * * * * * * //

template<class T, class Key, class Hash>
inline tnbLib::label tnbLib::ListHashTable<T, Key, Hash>::size() const
{
	return nElmts_;
}


template<class T, class Key, class Hash>
inline bool tnbLib::ListHashTable<T, Key, Hash>::empty() const
{
	return !nElmts_;
}


template<class T, class Key, class Hash>
inline bool tnbLib::ListHashTable<T, Key, Hash>::insert
(
	const Key& key,
	const T& newEntry
)
{
	return set(key, newEntry, true);
}


template<class T, class Key, class Hash>
inline bool tnbLib::ListHashTable<T, Key, Hash>::set
(
	const Key& key,
	const T& newEntry
)
{
	return set(key, newEntry, false);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class T, class Key, class Hash>
inline T& tnbLib::ListHashTable<T, Key, Hash>::operator[](const Key& key)
{
	iterator iter = find(key);

	if (iter == end())
	{
		FatalErrorInFunction
			<< toc()
			<< exit(FatalError);
	}

	return *iter;
}


template<class T, class Key, class Hash>
inline const T& tnbLib::ListHashTable<T, Key, Hash>::operator[]
(
	const Key& key
	) const
{
	const_iterator iter = find(key);

	if (iter == cend())
	{
		FatalErrorInFunction
			<< toc()
			<< exit(FatalError);
	}

	return *iter;
}


template<class T, class Key, class Hash>
inline T& tnbLib::ListHashTable<T, Key, Hash>::operator()(const Key& key)
{
	iterator iter = find(key);

	if (iter == end())
	{
		insert(key, T());
		return *find(key);
	}
	else
	{
		return *iter;
	}
}


// * * * * * * * * * * * * * * * * STL iterator  * * * * * * * * * * * * * * //

template<class T, class Key, class Hash>
template<class TRef, class TableRef>
inline tnbLib::ListHashTable<T, Key, Hash>::Iterator<TRef, TableRef>::Iterator
(
	TableRef hashTbl,
	label hashIndex,
	label elemIndex
)
	:
	hashTable_(hashTbl),
	hashIndex_(hashIndex),
	elemIndex_(elemIndex)
{}


template<class T, class Key, class Hash>
template<class TRef, class TableRef>
inline tnbLib::ListHashTable<T, Key, Hash>::Iterator<TRef, TableRef>::Iterator
(
	const iterator& iter
)
	:
	hashTable_(iter.hashTable_),
	hashIndex_(iter.hashIndex_),
	elemIndex_(iter.elemIndex_)
{}


template<class T, class Key, class Hash>
template<class TRef, class TableRef>
inline void
tnbLib::ListHashTable<T, Key, Hash>::Iterator<TRef, TableRef>::operator=
(
	const iterator& iter
	)
{
	this->hashIndex_ = iter.hashIndex_;
	this->elemIndex_ = iter.elemIndex_;
}


template<class T, class Key, class Hash>
template<class TRef, class TableRef>
inline bool
tnbLib::ListHashTable<T, Key, Hash>::Iterator<TRef, TableRef>::operator==
(
	const iterator& iter
	) const
{
	return hashIndex_ == iter.hashIndex_ && elemIndex_ == iter.elemIndex_;
}


template<class T, class Key, class Hash>
template<class TRef, class TableRef>
inline bool
tnbLib::ListHashTable<T, Key, Hash>::Iterator<TRef, TableRef>::operator==
(
	const const_iterator& iter
	) const
{
	return hashIndex_ == iter.hashIndex_ && elemIndex_ == iter.elemIndex_;
}


template<class T, class Key, class Hash>
template<class TRef, class TableRef>
inline bool
tnbLib::ListHashTable<T, Key, Hash>::Iterator<TRef, TableRef>::operator!=
(
	const iterator& iter
	) const
{
	return !operator==(iter);
}


template<class T, class Key, class Hash>
template<class TRef, class TableRef>
inline bool
tnbLib::ListHashTable<T, Key, Hash>::Iterator<TRef, TableRef>::operator!=
(
	const const_iterator& iter
	) const
{
	return !operator==(iter);
}


template<class T, class Key, class Hash>
template<class TRef, class TableRef>
inline TRef
tnbLib::ListHashTable<T, Key, Hash>::Iterator<TRef, TableRef>::operator*()
{
	return hashTable_.objects_[hashIndex_][elemIndex_];
}


template<class T, class Key, class Hash>
template<class TRef, class TableRef>
inline TRef
tnbLib::ListHashTable<T, Key, Hash>::Iterator<TRef, TableRef>::operator()()
{
	return operator*();
}


template<class T, class Key, class Hash>
template<class TRef, class TableRef>
inline
typename tnbLib::ListHashTable<T, Key, Hash>::template Iterator
<
	TRef,
	TableRef
>&
tnbLib::ListHashTable<T, Key, Hash>::Iterator
<
	TRef,
	TableRef
>::operator++()
{
	// A negative index is a special value from erase
	// (see notes in HashTable)
	if (hashIndex_ < 0)
	{
		hashIndex_ = -(hashIndex_ + 1) - 1;
	}
	else
	{
		// Try the next element on the local list
		elemIndex_++;

		if (elemIndex_ < hashTable_.objects_[hashIndex_].size())
		{
			return *this;
		}
	}

	// Step to the next table entry
	elemIndex_ = 0;

	while
		(
			++hashIndex_ < hashTable_.objects_.size()
			&& !hashTable_.objects_[hashIndex_].size()
			)
	{
	}


	if (hashIndex_ >= hashTable_.objects_.size())
	{
		// make end iterator
		hashIndex_ = hashTable_.keys_.size();
	}

	return *this;
}


template<class T, class Key, class Hash>
template<class TRef, class TableRef>
inline
typename tnbLib::ListHashTable<T, Key, Hash>::template Iterator
<
	TRef,
	TableRef
>
tnbLib::ListHashTable<T, Key, Hash>::Iterator
<
	TRef,
	TableRef
>::operator++
(
	int
	)
{
	iterator tmp = *this;
	++*this;
	return tmp;
}


template<class T, class Key, class Hash>
template<class TRef, class TableRef>
inline const Key&
tnbLib::ListHashTable<T, Key, Hash>::Iterator<TRef, TableRef>::key() const
{
	return hashTable_.keys_[hashIndex_][elemIndex_];
}


template<class T, class Key, class Hash>
inline typename tnbLib::ListHashTable<T, Key, Hash>::iterator
tnbLib::ListHashTable<T, Key, Hash>::begin()
{
	// Find first non-empty entry
	forAll(keys_, hashIdx)
	{
		if (keys_[hashIdx].size())
		{
			return iterator(*this, hashIdx, 0);
		}
	}

#ifdef FULLDEBUG
	if (debug)
	{
		Info << "ListHashTable is empty\n";
	}
#endif

	return ListHashTable<T, Key, Hash>::endIter_;
}


template<class T, class Key, class Hash>
inline const typename tnbLib::ListHashTable<T, Key, Hash>::iterator&
tnbLib::ListHashTable<T, Key, Hash>::end()
{
	return ListHashTable<T, Key, Hash>::endIter_;
}


template<class T, class Key, class Hash>
inline typename tnbLib::ListHashTable<T, Key, Hash>::const_iterator
tnbLib::ListHashTable<T, Key, Hash>::cbegin() const
{
	// Find first non-empty entry
	forAll(keys_, hashIdx)
	{
		if (keys_[hashIdx].size())
		{
			return const_iterator(*this, hashIdx, 0);
		}
	}

#ifdef FULLDEBUG
	if (debug)
	{
		Info << "ListHashTable is empty\n";
	}
#endif

	return ListHashTable<T, Key, Hash>::endConstIter_;
}


template<class T, class Key, class Hash>
inline const typename tnbLib::ListHashTable<T, Key, Hash>::const_iterator&
tnbLib::ListHashTable<T, Key, Hash>::cend() const
{
	return ListHashTable<T, Key, Hash>::endConstIter_;
}


template<class T, class Key, class Hash>
inline typename tnbLib::ListHashTable<T, Key, Hash>::const_iterator
tnbLib::ListHashTable<T, Key, Hash>::begin() const
{
	return this->cbegin();
}


template<class T, class Key, class Hash>
inline const typename tnbLib::ListHashTable<T, Key, Hash>::const_iterator&
tnbLib::ListHashTable<T, Key, Hash>::end() const
{
	return ListHashTable<T, Key, Hash>::endConstIter_;
}


// ************************************************************************* //