#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::GlobalIOList<Type>::GlobalIOList(const IOobject& io)
	:
	regIOobject(io)
{
	// Check for MUST_READ_IF_MODIFIED
	warnNoRereading<GlobalIOList<Type>>();

	readHeaderOk(IOstream::BINARY, typeName);
}


template<class Type>
tnbLib::GlobalIOList<Type>::GlobalIOList(const IOobject& io, const label size)
	:
	regIOobject(io)
{
	// Check for MUST_READ_IF_MODIFIED
	warnNoRereading<GlobalIOList<Type>>();

	if (!readHeaderOk(IOstream::BINARY, typeName))
	{
		List<Type>::setSize(size);
	}
}


template<class Type>
tnbLib::GlobalIOList<Type>::GlobalIOList(const IOobject& io, const List<Type>& f)
	:
	regIOobject(io)
{
	// Check for MUST_READ_IF_MODIFIED
	warnNoRereading<GlobalIOList<Type>>();

	if (!readHeaderOk(IOstream::BINARY, typeName))
	{
		List<Type>::operator=(f);
	}
}


template<class Type>
tnbLib::GlobalIOList<Type>::GlobalIOList
(
	const IOobject& io,
	List<Type>&& f
)
	:
	regIOobject(io),
	List<Type>(move(f))

{
	// Check for MUST_READ_IF_MODIFIED
	warnNoRereading<GlobalIOList<Type>>();

	readHeaderOk(IOstream::BINARY, typeName);
}


template<class Type>
tnbLib::GlobalIOList<Type>::GlobalIOList
(
	const GlobalIOList<Type>& field
)
	:
	regIOobject(field),
	List<Type>(field)
{}


template<class Type>
tnbLib::GlobalIOList<Type>::GlobalIOList
(
	GlobalIOList<Type>&& field
)
	:
	regIOobject(move(field)),
	List<Type>(move(field))
{}


// * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::GlobalIOList<Type>::~GlobalIOList()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
bool tnbLib::GlobalIOList<Type>::readData(Istream& is)
{
	is >> *this;
	return is.good();
}


template<class Type>
bool tnbLib::GlobalIOList<Type>::writeData(Ostream& os) const
{
	return (os << *this).good();
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::GlobalIOList<Type>::operator=(const GlobalIOList<Type>& rhs)
{
	List<Type>::operator=(rhs);
}


template<class Type>
void tnbLib::GlobalIOList<Type>::operator=(GlobalIOList<Type>&& rhs)
{
	List<Type>::operator=(move(rhs));
}


template<class Type>
void tnbLib::GlobalIOList<Type>::operator=(const List<Type>& rhs)
{
	List<Type>::operator=(rhs);
}


template<class Type>
void tnbLib::GlobalIOList<Type>::operator=(List<Type>&& rhs)
{
	List<Type>::operator=(move(rhs));
}


// ************************************************************************* //