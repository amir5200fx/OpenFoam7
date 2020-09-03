#pragma once
#include <primitiveEntry.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class T>
T tnbLib::dictionary::lookupType
(
	const word& keyword,
	bool recursive,
	bool patternMatch
) const
{
	const entry* entryPtr = lookupEntryPtr(keyword, recursive, patternMatch);

	if (entryPtr == nullptr)
	{
		FatalIOErrorInFunction
		(
			*this
		) << "keyword " << keyword << " is undefined in dictionary "
			<< name()
			<< exit(FatalIOError);
	}

	return pTraits<T>(entryPtr->stream());
}


template<class T>
T tnbLib::dictionary::lookupOrDefault
(
	const word& keyword,
	const T& deflt,
	bool recursive,
	bool patternMatch
) const
{
	const entry* entryPtr = lookupEntryPtr(keyword, recursive, patternMatch);

	if (entryPtr)
	{
		return pTraits<T>(entryPtr->stream());
	}
	else
	{
		if (writeOptionalEntries)
		{
			IOInfoInFunction(*this)
				<< "Optional entry '" << keyword << "' is not present,"
				<< " returning the default value '" << deflt << "'"
				<< endl;
		}

		return deflt;
	}
}


template<class T>
T tnbLib::dictionary::lookupOrAddDefault
(
	const word& keyword,
	const T& deflt,
	bool recursive,
	bool patternMatch
)
{
	const entry* entryPtr = lookupEntryPtr(keyword, recursive, patternMatch);

	if (entryPtr)
	{
		return pTraits<T>(entryPtr->stream());
	}
	else
	{
		if (writeOptionalEntries)
		{
			IOInfoInFunction(*this)
				<< "Optional entry '" << keyword << "' is not present,"
				<< " adding and returning the default value '" << deflt << "'"
				<< endl;
		}

		add(new primitiveEntry(keyword, deflt));
		return deflt;
	}
}


template<class T>
bool tnbLib::dictionary::readIfPresent
(
	const word& keyword,
	T& val,
	bool recursive,
	bool patternMatch
) const
{
	const entry* entryPtr = lookupEntryPtr(keyword, recursive, patternMatch);

	if (entryPtr)
	{
		entryPtr->stream() >> val;
		return true;
	}
	else
	{
		if (writeOptionalEntries)
		{
			IOInfoInFunction(*this)
				<< "Optional entry '" << keyword << "' is not present,"
				<< " the default value '" << val << "' will be used."
				<< endl;
		}

		return false;
	}
}


template<class T>
void tnbLib::dictionary::add(const keyType& k, const T& t, bool overwrite)
{
	add(new primitiveEntry(k, t), overwrite);
}


template<class T>
void tnbLib::dictionary::set(const keyType& k, const T& t)
{
	set(new primitiveEntry(k, t));
}


// * * * * * * * * * * * * * * * IOstream Functions  * * * * * * * * * * * * //

template<class EntryType>
void tnbLib::writeEntry
(
	Ostream& os,
	const word& entryName,
	const EntryType& value
)
{
	os.writeKeyword(entryName);
	writeEntry(os, value);
	os << token::END_STATEMENT << endl;
}


template<class EntryType>
void tnbLib::writeEntryIfDifferent
(
	Ostream& os,
	const word& entryName,
	const EntryType& value1,
	const EntryType& value2
)
{
	if (value1 != value2)
	{
		writeEntry(os, entryName, value2);
	}
}


// ************************************************************************* //