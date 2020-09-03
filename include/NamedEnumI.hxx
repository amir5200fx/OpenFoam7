#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Enum, unsigned int nEnum>
tnbLib::NamedEnum<Enum, nEnum>::NamedEnum()
	:
	HashTable<unsigned int>(2 * nEnum)
{
	for (unsigned int enumI = 0; enumI < nEnum; ++enumI)
	{
		if (!names[enumI] || names[enumI][0] == '\0')
		{
			stringList goodNames(enumI);

			for (unsigned int i = 0; i < enumI; ++i)
			{
				goodNames[i] = names[i];
			}

			FatalErrorInFunction
				<< "Illegal enumeration name at position " << enumI << endl
				<< "after entries " << goodNames << ".\n"
				<< "Possibly your NamedEnum<Enum, nEnum>::names array"
				<< " is not of size " << nEnum << endl
				<< abort(FatalError);
		}
		insert(names[enumI], enumI);
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Enum, unsigned int nEnum>
Enum tnbLib::NamedEnum<Enum, nEnum>::read(Istream& is) const
{
	const word name(is);

	HashTable<unsigned int>::const_iterator iter = find(name);

	if (iter == HashTable<unsigned int>::end())
	{
		FatalIOErrorInFunction(is)
			<< name << " is not in enumeration: "
			<< sortedToc() << exit(FatalIOError);
	}

	return Enum(iter());
}


template<class Enum, unsigned int nEnum>
void tnbLib::NamedEnum<Enum, nEnum>::write(const Enum e, Ostream& os) const
{
	os << operator[](e);
}


template<class Enum, unsigned int nEnum>
tnbLib::stringList tnbLib::NamedEnum<Enum, nEnum>::strings()
{
	stringList lst(nEnum);

	label nElem = 0;
	for (unsigned int enumI = 0; enumI < nEnum; ++enumI)
	{
		if (names[enumI] && names[enumI][0])
		{
			lst[nElem++] = names[enumI];
		}
	}

	lst.setSize(nElem);
	return lst;
}


template<class Enum, unsigned int nEnum>
tnbLib::wordList tnbLib::NamedEnum<Enum, nEnum>::words()
{
	wordList lst(nEnum);

	label nElem = 0;
	for (unsigned int enumI = 0; enumI < nEnum; ++enumI)
	{
		if (names[enumI] && names[enumI][0])
		{
			lst[nElem++] = names[enumI];
		}
	}

	lst.setSize(nElem);
	return lst;
}


template<class Enum, unsigned int nEnum>
const char* tnbLib::NamedEnum<Enum, nEnum>::operator[](const Enum e) const
{
	unsigned int ue = unsigned(e);

	if (ue < nEnum)
	{
		return names[ue];
	}
	else
	{
		FatalErrorInFunction
			<< "names array index " << ue << " out of range 0-"
			<< nEnum - 1
			<< exit(FatalError);

		return names[0];
	}
}


// ************************************************************************* //