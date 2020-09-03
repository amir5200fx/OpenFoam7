#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Key, class Hash>
tnbLib::HashSet<Key, Hash>::HashSet(const UList<Key>& lst)
	:
	HashTable<nil, Key, Hash>(2 * lst.size())
{
	forAll(lst, elemI)
	{
		this->insert(lst[elemI]);
	}
}


template<class Key, class Hash>
template<unsigned Size>
tnbLib::HashSet<Key, Hash>::HashSet(const FixedList<Key, Size>& lst)
	:
	HashTable<nil, Key, Hash>(2 * lst.size())
{
	forAll(lst, elemI)
	{
		this->insert(lst[elemI]);
	}
}


template<class Key, class Hash>
template<class AnyType, class AnyHash>
tnbLib::HashSet<Key, Hash>::HashSet
(
	const HashTable<AnyType, Key, AnyHash>& h
)
	:
	HashTable<nil, Key, Hash>(h.size())
{
	for
		(
			typename HashTable<AnyType, Key, AnyHash>::const_iterator
			cit = h.cbegin();
			cit != h.cend();
			++cit
			)
	{
		this->insert(cit.key());
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Key, class Hash>
tnbLib::label tnbLib::HashSet<Key, Hash>::insert(const UList<Key>& lst)
{
	label count = 0;
	forAll(lst, elemI)
	{
		if (this->insert(lst[elemI]))
		{
			++count;
		}
	}

	return count;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class Key, class Hash>
inline bool tnbLib::HashSet<Key, Hash>::operator[](const Key& key) const
{
	return this->found(key);
}


template<class Key, class Hash>
void tnbLib::HashSet<Key, Hash>::operator=(const HashSet<Key, Hash>& rhs)
{
	// Check for assignment to self
	if (this == &rhs)
	{
		FatalErrorInFunction
			<< "attempted assignment to self"
			<< abort(FatalError);
	}

	HashTable<nil, Key, Hash>::operator=(rhs);
}


template<class Key, class Hash>
void tnbLib::HashSet<Key, Hash>::operator=(HashSet<Key, Hash>&& rhs)
{
	// Check for assignment to self
	if (this == &rhs)
	{
		FatalErrorInFunction
			<< "attempted assignment to self"
			<< abort(FatalError);
	}

	HashTable<nil, Key, Hash>::operator=(move(rhs));
}


template<class Key, class Hash>
bool tnbLib::HashSet<Key, Hash>::operator==(const HashSet<Key, Hash>& rhs) const
{
	// Are all lhs elements in rhs?
	for (const_iterator iter = this->cbegin(); iter != this->cend(); ++iter)
	{
		if (!rhs.found(iter.key()))
		{
			return false;
		}
	}

	// Are all rhs elements in lhs?
	for (const_iterator iter = rhs.cbegin(); iter != rhs.cend(); ++iter)
	{
		if (!this->found(iter.key()))
		{
			return false;
		}
	}

	return true;
}


template<class Key, class Hash>
bool tnbLib::HashSet<Key, Hash>::operator!=(const HashSet<Key, Hash>& rhs) const
{
	return !(operator==(rhs));
}


template<class Key, class Hash>
void tnbLib::HashSet<Key, Hash>::operator|=(const HashSet<Key, Hash>& rhs)
{
	// Add rhs elements into lhs
	for (const_iterator iter = rhs.cbegin(); iter != rhs.cend(); ++iter)
	{
		this->insert(iter.key());
	}
}


template<class Key, class Hash>
void tnbLib::HashSet<Key, Hash>::operator&=(const HashSet<Key, Hash>& rhs)
{
	// Remove elements not also found in rhs
	for (iterator iter = this->begin(); iter != this->end(); ++iter)
	{
		if (!rhs.found(iter.key()))
		{
			this->erase(iter);
		}
	}
}


template<class Key, class Hash>
void tnbLib::HashSet<Key, Hash>::operator^=(const HashSet<Key, Hash>& rhs)
{
	// Add missed rhs elements, remove duplicate elements
	for (const_iterator iter = rhs.cbegin(); iter != rhs.cend(); ++iter)
	{
		if (this->found(iter.key()))
		{
			this->erase(iter.key());
		}
		else
		{
			this->insert(iter.key());
		}
	}
}


template<class Key, class Hash>
void tnbLib::HashSet<Key, Hash>::operator-=(const HashSet<Key, Hash>& rhs)
{
	// Remove rhs elements from lhs
	for (const_iterator iter = rhs.cbegin(); iter != rhs.cend(); ++iter)
	{
		this->erase(iter.key());
	}
}


/* * * * * * * * * * * * * * * * Global operators  * * * * * * * * * * * * * */

template<class Key, class Hash>
tnbLib::HashSet<Key, Hash>
tnbLib::operator|
(
	const HashSet<Key, Hash>& hash1,
	const HashSet<Key, Hash>& hash2
	)
{
	HashSet<Key, Hash> out(hash1);
	out |= hash2;
	return out;
}


template<class Key, class Hash>
tnbLib::HashSet<Key, Hash>
tnbLib::operator&
(
	const HashSet<Key, Hash>& hash1,
	const HashSet<Key, Hash>& hash2
	)
{
	HashSet<Key, Hash> out(hash1);
	out &= hash2;
	return out;
}


template<class Key, class Hash>
tnbLib::HashSet<Key, Hash>
tnbLib::operator^
(
	const HashSet<Key, Hash>& hash1,
	const HashSet<Key, Hash>& hash2
	)
{
	HashSet<Key, Hash> out(hash1);
	out ^= hash2;
	return out;
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //