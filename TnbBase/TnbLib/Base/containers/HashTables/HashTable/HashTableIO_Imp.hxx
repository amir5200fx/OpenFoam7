#pragma once
#include <Istream.hxx>
#include <Ostream.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class T, class Key, class Hash>
tnbLib::HashTable<T, Key, Hash>::HashTable(Istream& is, const label size)
	:
	HashTableCore(),
	nElmts_(0),
	tableSize_(HashTableCore::canonicalSize(size)),
	table_(nullptr)
{
	if (tableSize_)
	{
		table_ = new hashedEntry*[tableSize_];

		for (label hashIdx = 0; hashIdx < tableSize_; hashIdx++)
		{
			table_[hashIdx] = 0;
		}
	}

	operator>>(is, *this);
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

template<class T, class Key, class Hash>
tnbLib::Ostream&
tnbLib::HashTable<T, Key, Hash>::printInfo(Ostream& os) const
{
	label used = 0;
	label maxChain = 0;
	unsigned avgChain = 0;

	for (label hashIdx = 0; hashIdx < tableSize_; ++hashIdx)
	{
		label count = 0;
		for (hashedEntry* ep = table_[hashIdx]; ep; ep = ep->next_)
		{
			++count;
		}

		if (count)
		{
			++used;
			avgChain += count;

			if (maxChain < count)
			{
				maxChain = count;
			}
		}
	}

	os << "HashTable<T,Key,Hash>"
		<< " elements:" << size() << " slots:" << used << "/" << tableSize_
		<< " chaining(avg/max):" << (used ? (float(avgChain) / used) : 0)
		<< "/" << maxChain << endl;

	return os;
}


// * * * * * * * * * * * * * * * IOstream Functions  * * * * * * * * * * * * //

template<class T, class Key, class Hash>
void tnbLib::writeEntry(Ostream& os, const HashTable<T, Key, Hash>& ht)
{
	os << ht;
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

template<class T, class Key, class Hash>
tnbLib::Istream& tnbLib::operator>>
(
	Istream& is,
	HashTable<T, Key, Hash>& L
	)
{
	is.fatalCheck("operator>>(Istream&, HashTable<T, Key, Hash>&)");

	// Anull list
	L.clear();

	is.fatalCheck("operator>>(Istream&, HashTable<T, Key, Hash>&)");

	token firstToken(is);

	is.fatalCheck
	(
		"operator>>(Istream&, HashTable<T, Key, Hash>&) : "
		"reading first token"
	);

	if (firstToken.isLabel())
	{
		label s = firstToken.labelToken();

		// Read beginning of contents
		char delimiter = is.readBeginList("HashTable<T, Key, Hash>");

		if (s)
		{
			if (2 * s > L.tableSize_)
			{
				L.resize(2 * s);
			}

			if (delimiter == token::BEGIN_LIST)
			{
				for (label i = 0; i < s; i++)
				{
					Key key;
					is >> key;
					L.insert(key, pTraits<T>(is));

					is.fatalCheck
					(
						"operator>>(Istream&, HashTable<T, Key, Hash>&) : "
						"reading entry"
					);
				}
			}
			else
			{
				FatalIOErrorInFunction
				(
					is
				) << "incorrect first token, '(', found " << firstToken.info()
					<< exit(FatalIOError);
			}
		}

		// Read end of contents
		is.readEndList("HashTable");
	}
	else if (firstToken.isPunctuation())
	{
		if (firstToken.pToken() != token::BEGIN_LIST)
		{
			FatalIOErrorInFunction
			(
				is
			) << "incorrect first token, '(', found " << firstToken.info()
				<< exit(FatalIOError);
		}

		token lastToken(is);
		while
			(
				!(
					lastToken.isPunctuation()
					&& lastToken.pToken() == token::END_LIST
					)
				)
		{
			is.putBack(lastToken);

			Key key;
			is >> key;

			T element;
			is >> element;

			L.insert(key, element);

			is.fatalCheck
			(
				"operator>>(Istream&, HashTable<T, Key, Hash>&) : "
				"reading entry"
			);

			is >> lastToken;
		}
	}
	else
	{
		FatalIOErrorInFunction
		(
			is
		) << "incorrect first token, expected <int> or '(', found "
			<< firstToken.info()
			<< exit(FatalIOError);
	}

	is.fatalCheck("operator>>(Istream&, HashTable<T, Key, Hash>&)");

	return is;
}


template<class T, class Key, class Hash>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const HashTable<T, Key, Hash>& L
	)
{
	// Write size and start delimiter
	os << nl << L.size() << nl << token::BEGIN_LIST << nl;

	// Write contents
	for
		(
			typename HashTable<T, Key, Hash>::const_iterator iter = L.cbegin();
			iter != L.cend();
			++iter
			)
	{
		os << iter.key() << token::SPACE << iter() << nl;
	}

	// Write end delimiter
	os << token::END_LIST;

	// Check state of IOstream
	os.check("Ostream& operator<<(Ostream&, const HashTable&)");

	return os;
}


// ************************************************************************* //