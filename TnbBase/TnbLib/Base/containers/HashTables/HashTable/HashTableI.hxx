#pragma once
#include <error.hxx>
// * * * * * * * * * * * * * Private Member Classes * * * * * * * * * * * * //

template<class T, class Key, class Hash>
inline tnbLib::HashTable<T, Key, Hash>::hashedEntry::hashedEntry
(
	const Key& key,
	hashedEntry* next,
	const T& obj
)
	:
	key_(key),
	next_(next),
	obj_(obj)
{}


// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

template<class T, class Key, class Hash>
inline tnbLib::label
tnbLib::HashTable<T, Key, Hash>::hashKeyIndex(const Key& key) const
{
	// size is power of two - this is the modulus
	return Hash()(key) & (tableSize_ - 1);
}


// * * * * * * * * * * * * * * * Member Functions * * * * * * * * * * * * * //

template<class T, class Key, class Hash>
inline tnbLib::label tnbLib::HashTable<T, Key, Hash>::capacity() const
{
	return tableSize_;
}


template<class T, class Key, class Hash>
inline tnbLib::label tnbLib::HashTable<T, Key, Hash>::size() const
{
	return nElmts_;
}


template<class T, class Key, class Hash>
inline bool tnbLib::HashTable<T, Key, Hash>::empty() const
{
	return !nElmts_;
}


template<class T, class Key, class Hash>
inline bool tnbLib::HashTable<T, Key, Hash>::insert
(
	const Key& key,
	const T& newEntry
)
{
	return this->set(key, newEntry, true);
}


template<class T, class Key, class Hash>
inline bool tnbLib::HashTable<T, Key, Hash>::set
(
	const Key& key,
	const T& newEntry
)
{
	return this->set(key, newEntry, false);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class T, class Key, class Hash>
inline T& tnbLib::HashTable<T, Key, Hash>::operator[](const Key& key)
{
	iterator iter = this->find(key);

	if (iter == this->end())
	{
		FatalErrorInFunction
			<< key << " not found in table.  Valid entries: "
			<< toc()
			<< exit(FatalError);
	}

	return *iter;
}


template<class T, class Key, class Hash>
inline const T& tnbLib::HashTable<T, Key, Hash>::operator[](const Key& key) const
{
	const_iterator iter = this->find(key);

	if (iter == this->cend())
	{
		FatalErrorInFunction
			<< key << " not found in table.  Valid entries: "
			<< toc()
			<< exit(FatalError);
	}

	return *iter;
}


template<class T, class Key, class Hash>
inline T& tnbLib::HashTable<T, Key, Hash>::operator()(const Key& key)
{
	iterator iter = this->find(key);

	if (iter == this->end())
	{
		this->insert(key, T());
		return *find(key);
	}
	else
	{
		return *iter;
	}
}


// * * * * * * * * * * * * * * * iterator base * * * * * * * * * * * * * * * //

template<class T, class Key, class Hash>
inline tnbLib::HashTable<T, Key, Hash>::iteratorBase::iteratorBase()
	:
	hashTable_(0),
	entryPtr_(0),
	hashIndex_(0)
{}


template<class T, class Key, class Hash>
inline tnbLib::HashTable<T, Key, Hash>::iteratorBase::iteratorBase
(
	const HashTable<T, Key, Hash>* hashTbl
)
	:
	hashTable_(const_cast<HashTable<T, Key, Hash>*>(hashTbl)),
	entryPtr_(0),
	hashIndex_(0)
{
	if (hashTable_->nElmts_)
	{
		// find first non-nullptr table entry
		while
			(
				!(entryPtr_ = hashTable_->table_[hashIndex_])
				&& ++hashIndex_ < hashTable_->tableSize_
				)
		{
		}

		if (hashIndex_ >= hashTable_->tableSize_)
		{
			// make into an end iterator
			entryPtr_ = 0;
			hashIndex_ = 0;
		}
	}
}


template<class T, class Key, class Hash>
inline tnbLib::HashTable<T, Key, Hash>::iteratorBase::iteratorBase
(
	const HashTable<T, Key, Hash>* hashTbl,
	const hashedEntry* elmt,
	const label hashIndex
)
	:
	hashTable_(const_cast<HashTable<T, Key, Hash>*>(hashTbl)),
	entryPtr_(const_cast<hashedEntry*>(elmt)),
	hashIndex_(hashIndex)
{}


template<class T, class Key, class Hash>
inline void
tnbLib::HashTable<T, Key, Hash>::iteratorBase::increment()
{
	// A negative index is a special value from erase
	if (hashIndex_ < 0)
	{
		// the markPos='-curPos-1', but we wish to continue at 'curPos-1'
		// thus use '-(markPos+1) -1'
		hashIndex_ = -(hashIndex_ + 1) - 1;
	}
	else if (entryPtr_)
	{
		if (entryPtr_->next_)
		{
			// Move to next element on the SLList
			entryPtr_ = entryPtr_->next_;
			return;
		}
	}
	// else
	// {
	//     // if we reach here (entryPtr_ is nullptr) it is already at the end()
	//     // we should probably stop
	// }


	// Step to the next table entry
	while
		(
			++hashIndex_ < hashTable_->tableSize_
			&& !(entryPtr_ = hashTable_->table_[hashIndex_])
			)
	{
	}

	if (hashIndex_ >= hashTable_->tableSize_)
	{
		// make into an end iterator
		entryPtr_ = 0;
		hashIndex_ = 0;
	}
}


template<class T, class Key, class Hash>
inline
const Key& tnbLib::HashTable<T, Key, Hash>::iteratorBase::key() const
{
	return entryPtr_->key_;
}


template<class T, class Key, class Hash>
inline T&
tnbLib::HashTable<T, Key, Hash>::iteratorBase::object()
{
	return entryPtr_->obj_;
}


template<class T, class Key, class Hash>
inline const T&
tnbLib::HashTable<T, Key, Hash>::iteratorBase::cobject() const
{
	return entryPtr_->obj_;
}


template<class T, class Key, class Hash>
inline bool tnbLib::HashTable<T, Key, Hash>::iteratorBase::operator==
(
	const iteratorBase& iter
	) const
{
	return entryPtr_ == iter.entryPtr_;
}


template<class T, class Key, class Hash>
inline bool tnbLib::HashTable<T, Key, Hash>::iteratorBase::operator!=
(
	const iteratorBase& iter
	) const
{
	return entryPtr_ != iter.entryPtr_;
}


template<class T, class Key, class Hash>
inline bool tnbLib::HashTable<T, Key, Hash>::iteratorBase::operator==
(
	const iteratorEnd&
	) const
{
	return !entryPtr_;
}


template<class T, class Key, class Hash>
inline bool tnbLib::HashTable<T, Key, Hash>::iteratorBase::operator!=
(
	const iteratorEnd&
	) const
{
	return entryPtr_;
}


// * * * * * * * * * * * * * * * * STL iterator  * * * * * * * * * * * * * * //

template<class T, class Key, class Hash>
inline tnbLib::HashTable<T, Key, Hash>::iterator::iterator()
	:
	iteratorBase()
{}


template<class T, class Key, class Hash>
inline tnbLib::HashTable<T, Key, Hash>::iterator::iterator
(
	const iteratorEnd&
)
	:
	iteratorBase()
{}


template<class T, class Key, class Hash>
inline tnbLib::HashTable<T, Key, Hash>::iterator::iterator
(
	HashTable<T, Key, Hash>* hashTbl
)
	:
	iteratorBase(hashTbl)
{}


template<class T, class Key, class Hash>
inline tnbLib::HashTable<T, Key, Hash>::iterator::iterator
(
	HashTable<T, Key, Hash>* hashTbl,
	hashedEntry* elmt,
	const label hashIndex
)
	:
	iteratorBase(hashTbl, elmt, hashIndex)
{}


template<class T, class Key, class Hash>
inline T&
tnbLib::HashTable<T, Key, Hash>::iterator::operator*()
{
	return this->object();
}


template<class T, class Key, class Hash>
inline T&
tnbLib::HashTable<T, Key, Hash>::iterator::operator()()
{
	return this->object();
}


template<class T, class Key, class Hash>
inline const T&
tnbLib::HashTable<T, Key, Hash>::iterator::operator*() const
{
	return this->cobject();
}


template<class T, class Key, class Hash>
inline const T&
tnbLib::HashTable<T, Key, Hash>::iterator::operator()() const
{
	return this->cobject();
}


template<class T, class Key, class Hash>
inline
typename tnbLib::HashTable<T, Key, Hash>::iterator&
tnbLib::HashTable<T, Key, Hash>::iterator::operator++()
{
	this->increment();
	return *this;
}


template<class T, class Key, class Hash>
inline typename tnbLib::HashTable<T, Key, Hash>::iterator
tnbLib::HashTable<T, Key, Hash>::iterator::operator++(int)
{
	iterator old = *this;
	this->increment();
	return old;
}


template<class T, class Key, class Hash>
inline typename tnbLib::HashTable<T, Key, Hash>::iterator
tnbLib::HashTable<T, Key, Hash>::begin()
{
	return iterator(this);
}


// * * * * * * * * * * * * * * * STL const_iterator * * * * * * * * * * * * * //

template<class T, class Key, class Hash>
inline tnbLib::HashTable<T, Key, Hash>::const_iterator::const_iterator()
	:
	iteratorBase()
{}


template<class T, class Key, class Hash>
inline tnbLib::HashTable<T, Key, Hash>::const_iterator::const_iterator
(
	const HashTable<T, Key, Hash>::iterator& iter
)
	:
	iteratorBase(iter)
{}


template<class T, class Key, class Hash>
inline tnbLib::HashTable<T, Key, Hash>::const_iterator::const_iterator
(
	const iteratorEnd&
)
	:
	iteratorBase()
{}


template<class T, class Key, class Hash>
inline tnbLib::HashTable<T, Key, Hash>::const_iterator::const_iterator
(
	const HashTable<T, Key, Hash>* hashTbl
)
	:
	iteratorBase(hashTbl)
{}


template<class T, class Key, class Hash>
inline tnbLib::HashTable<T, Key, Hash>::const_iterator::const_iterator
(
	const HashTable<T, Key, Hash>* hashTbl,
	const hashedEntry* elmt,
	const label hashIndex
)
	:
	iteratorBase(hashTbl, elmt, hashIndex)
{}


template<class T, class Key, class Hash>
inline const T&
tnbLib::HashTable<T, Key, Hash>::const_iterator::operator*() const
{
	return this->cobject();
}


template<class T, class Key, class Hash>
inline const T&
tnbLib::HashTable<T, Key, Hash>::const_iterator::operator()() const
{
	return this->cobject();
}


template<class T, class Key, class Hash>
inline
typename tnbLib::HashTable<T, Key, Hash>::const_iterator&
tnbLib::HashTable<T, Key, Hash>::const_iterator::operator++()
{
	this->increment();
	return *this;
}


template<class T, class Key, class Hash>
inline typename tnbLib::HashTable<T, Key, Hash>::const_iterator
tnbLib::HashTable<T, Key, Hash>::const_iterator::operator++(int)
{
	const_iterator old = *this;
	this->increment();
	return old;
}


template<class T, class Key, class Hash>
inline typename tnbLib::HashTable<T, Key, Hash>::const_iterator
tnbLib::HashTable<T, Key, Hash>::cbegin() const
{
	return const_iterator(this);
}


template<class T, class Key, class Hash>
inline typename tnbLib::HashTable<T, Key, Hash>::const_iterator
tnbLib::HashTable<T, Key, Hash>::begin() const
{
	return this->cbegin();
}


// ************************************************************************* //