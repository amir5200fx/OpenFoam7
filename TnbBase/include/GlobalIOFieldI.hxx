#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::GlobalIOField<Type>::GlobalIOField(const IOobject& io)
	:
	regIOobject(io)
{
	// Check for MUST_READ_IF_MODIFIED
	warnNoRereading<GlobalIOField<Type>>();

	readHeaderOk(IOstream::BINARY, typeName);
}


template<class Type>
tnbLib::GlobalIOField<Type>::GlobalIOField(const IOobject& io, const label size)
	:
	regIOobject(io)
{
	// Check for MUST_READ_IF_MODIFIED
	warnNoRereading<GlobalIOField<Type>>();

	if (!readHeaderOk(IOstream::BINARY, typeName))
	{
		Field<Type>::setSize(size);
	}
}


template<class Type>
tnbLib::GlobalIOField<Type>::GlobalIOField
(
	const IOobject& io,
	const Field<Type>& f
)
	:
	regIOobject(io)
{
	// Check for MUST_READ_IF_MODIFIED
	warnNoRereading<GlobalIOField<Type>>();

	if (!readHeaderOk(IOstream::BINARY, typeName))
	{
		Field<Type>::operator=(f);
	}
}


template<class Type>
tnbLib::GlobalIOField<Type>::GlobalIOField
(
	const IOobject& io,
	Field<Type>&& f
)
	:
	regIOobject(io),
	Field<Type>(move(f))

{
	// Check for MUST_READ_IF_MODIFIED
	warnNoRereading<GlobalIOField<Type>>();

	readHeaderOk(IOstream::BINARY, typeName);
}


template<class Type>
tnbLib::GlobalIOField<Type>::GlobalIOField
(
	const GlobalIOField<Type>& field
)
	:
	regIOobject(field),
	Field<Type>(field)
{}


template<class Type>
tnbLib::GlobalIOField<Type>::GlobalIOField
(
	GlobalIOField<Type>&& field
)
	:
	regIOobject(move(field)),
	Field<Type>(move(field))
{}


// * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::GlobalIOField<Type>::~GlobalIOField()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
bool tnbLib::GlobalIOField<Type>::readData(Istream& is)
{
	is >> *this;
	return is.good();
}


template<class Type>
bool tnbLib::GlobalIOField<Type>::writeData(Ostream& os) const
{
	return (os << static_cast<const Field<Type>&>(*this)).good();
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::GlobalIOField<Type>::operator=(const GlobalIOField<Type>& rhs)
{
	Field<Type>::operator=(rhs);
}


template<class Type>
void tnbLib::GlobalIOField<Type>::operator=(GlobalIOField<Type>&& rhs)
{
	Field<Type>::operator=(move(rhs));
}


template<class Type>
void tnbLib::GlobalIOField<Type>::operator=(const Field<Type>& rhs)
{
	Field<Type>::operator=(rhs);
}


template<class Type>
void tnbLib::GlobalIOField<Type>::operator=(Field<Type>&& rhs)
{
	Field<Type>::operator=(move(rhs));
}


// ************************************************************************* //