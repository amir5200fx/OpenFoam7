#include <hashedWordList.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::hashedWordList::rehash()
{
	indices_.clear();
	forAll(*this, i)
	{
		indices_.insert(List<word>::operator[](i), i);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::hashedWordList::hashedWordList()
	:
	List<word>()
{}


tnbLib::hashedWordList::hashedWordList(const UList<word>& names)
	:
	List<word>(names)
{
	rehash();
}


tnbLib::hashedWordList::hashedWordList(const hashedWordList& names)
	:
	List<word>(static_cast<const UList<word>&>(names))
{
	rehash();
}


tnbLib::hashedWordList::hashedWordList(hashedWordList&& names)
	:
	List<word>(move(names)),
	indices_(move(names.indices_))
{}


tnbLib::hashedWordList::hashedWordList(List<word>&& names)
	:
	List<word>(move(names))
{
	rehash();
}


tnbLib::hashedWordList::hashedWordList
(
	const label nNames,
	const char** names
)
	:
	List<word>(nNames)
{
	forAll(*this, i)
	{
		List<word>::operator[](i) = names[i];
	}

	rehash();
}


tnbLib::hashedWordList::hashedWordList
(
	const char** names
)
{
	// count names
	label nNames = 0;
	for (unsigned i = 0; names[i] && *(names[i]); ++i)
	{
		++nNames;
	}

	List<word>::setSize(nNames);
	forAll(*this, i)
	{
		List<word>::operator[](i) = names[i];
	}

	rehash();
}


tnbLib::hashedWordList::hashedWordList(Istream& is)
{
	is >> *this;
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void tnbLib::hashedWordList::clear()
{
	List<word>::clear();
	indices_.clear();
}


void tnbLib::hashedWordList::append(const word& name)
{
	const label idx = size();
	List<word>::append(name);
	indices_.insert(name, idx);
}


void tnbLib::hashedWordList::transfer(List<word>& lst)
{
	List<word>::transfer(lst);
	rehash();
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

tnbLib::Istream& tnbLib::operator>>(Istream& is, hashedWordList& lst)
{
	is >> static_cast<List<word>&>(lst);
	lst.rehash();

	return is;
}


tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const hashedWordList& lst)
{
	os << static_cast<const List<word>&>(lst);
	return os;
}


// ************************************************************************* //