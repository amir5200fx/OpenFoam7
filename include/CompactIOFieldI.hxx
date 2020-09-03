#pragma once
#include <labelList.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class Type, class BaseType>
void tnbLib::CompactIOField<Type, BaseType>::readFromStream(const bool read)
{
	Istream& is = readStream(word::null, read);

	if (read)
	{
		if (headerClassName() == IOField<Type>::typeName)
		{
			is >> static_cast<Field<Type>&>(*this);
			close();
		}
		else if (headerClassName() == typeName)
		{
			is >> *this;
			close();
		}
		else
		{
			FatalIOErrorInFunction
			(
				is
			) << "unexpected class name " << headerClassName()
				<< " expected " << typeName << " or " << IOField<Type>::typeName
				<< endl
				<< "    while reading object " << name()
				<< exit(FatalIOError);
		}
	}
}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

template<class Type, class BaseType>
tnbLib::CompactIOField<Type, BaseType>::CompactIOField(const IOobject& io)
	:
	regIOobject(io)
{
	if
		(
			io.readOpt() == IOobject::MUST_READ
			|| (io.readOpt() == IOobject::READ_IF_PRESENT && headerOk())
			)
	{
		readFromStream();
	}
}


template<class Type, class BaseType>
tnbLib::CompactIOField<Type, BaseType>::CompactIOField
(
	const IOobject& io,
	const bool read
)
	:
	regIOobject(io)
{
	if (io.readOpt() == IOobject::MUST_READ)
	{
		readFromStream(read);
	}
	else if (io.readOpt() == IOobject::READ_IF_PRESENT)
	{
		bool haveFile = headerOk();
		readFromStream(read && haveFile);
	}
}


template<class Type, class BaseType>
tnbLib::CompactIOField<Type, BaseType>::CompactIOField
(
	const IOobject& io,
	const label size
)
	:
	regIOobject(io)
{
	if
		(
			io.readOpt() == IOobject::MUST_READ
			|| (io.readOpt() == IOobject::READ_IF_PRESENT && headerOk())
			)
	{
		readFromStream();
	}
	else
	{
		Field<Type>::setSize(size);
	}
}


template<class Type, class BaseType>
tnbLib::CompactIOField<Type, BaseType>::CompactIOField
(
	const IOobject& io,
	const Field<Type>& field
)
	:
	regIOobject(io)
{
	if
		(
			io.readOpt() == IOobject::MUST_READ
			|| (io.readOpt() == IOobject::READ_IF_PRESENT && headerOk())
			)
	{
		readFromStream();
	}
	else
	{
		Field<Type>::operator=(field);
	}
}


template<class Type, class BaseType>
tnbLib::CompactIOField<Type, BaseType>::CompactIOField
(
	const IOobject& io,
	Field<Type>&& field
)
	:
	regIOobject(io),
	Field<Type>(move(field))
{
	if
		(
			io.readOpt() == IOobject::MUST_READ
			|| (io.readOpt() == IOobject::READ_IF_PRESENT && headerOk())
			)
	{
		readFromStream();
	}
}


template<class Type, class BaseType>
tnbLib::CompactIOField<Type, BaseType>::CompactIOField
(
	CompactIOField<Type, BaseType>&& field
)
	:
	regIOobject(move(field)),
	Field<Type>(move(field))
{}


// * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * * //

template<class Type, class BaseType>
tnbLib::CompactIOField<Type, BaseType>::~CompactIOField()
{}



// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type, class BaseType>
bool tnbLib::CompactIOField<Type, BaseType>::writeObject
(
	IOstream::streamFormat fmt,
	IOstream::versionNumber ver,
	IOstream::compressionType cmp,
	const bool write
) const
{
	if (fmt == IOstream::ASCII)
	{
		// Change type to be non-compact format type
		const word oldTypeName = typeName;

		const_cast<word&>(typeName) = IOField<Type>::typeName;

		bool good = regIOobject::writeObject(fmt, ver, cmp, write);

		// Change type back
		const_cast<word&>(typeName) = oldTypeName;

		return good;
	}
	else
	{
		return regIOobject::writeObject(fmt, ver, cmp, write);
	}
}


template<class Type, class BaseType>
bool tnbLib::CompactIOField<Type, BaseType>::writeData(Ostream& os) const
{
	return (os << *this).good();
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class Type, class BaseType>
void tnbLib::CompactIOField<Type, BaseType>::operator=
(
	const CompactIOField<Type, BaseType>& rhs
	)
{
	Field<Type>::operator=(rhs);
}


template<class Type, class BaseType>
void tnbLib::CompactIOField<Type, BaseType>::operator=
(
	CompactIOField<Type, BaseType>&& rhs
	)
{
	Field<Type>::operator=(move(rhs));
}


template<class Type, class BaseType>
void tnbLib::CompactIOField<Type, BaseType>::operator=(const Field<Type>& rhs)
{
	Field<Type>::operator=(rhs);
}


template<class Type, class BaseType>
void tnbLib::CompactIOField<Type, BaseType>::operator=(Field<Type>&& rhs)
{
	Field<Type>::operator=(move(rhs));
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

template<class Type, class BaseType>
tnbLib::Istream& tnbLib::operator>>
(
	tnbLib::Istream& is,
	tnbLib::CompactIOField<Type, BaseType>& L
	)
{
	// Read compact
	const labelList start(is);
	const Field<BaseType> elems(is);

	// Convert
	L.setSize(start.size() - 1);

	forAll(L, i)
	{
		Type& subField = L[i];

		label index = start[i];
		subField.setSize(start[i + 1] - index);

		forAll(subField, j)
		{
			subField[j] = elems[index++];
		}
	}

	return is;
}


template<class Type, class BaseType>
tnbLib::Ostream& tnbLib::operator<<
(
	tnbLib::Ostream& os,
	const tnbLib::CompactIOField<Type, BaseType>& L
	)
{
	// Keep ascii writing same.
	if (os.format() == IOstream::ASCII)
	{
		os << static_cast<const Field<Type>&>(L);
	}
	else
	{
		// Convert to compact format
		labelList start(L.size() + 1);

		start[0] = 0;
		for (label i = 1; i < start.size(); i++)
		{
			start[i] = start[i - 1] + L[i - 1].size();
		}

		Field<BaseType> elems(start[start.size() - 1]);

		label elemI = 0;
		forAll(L, i)
		{
			const Type& subField = L[i];

			forAll(subField, j)
			{
				elems[elemI++] = subField[j];
			}
		}
		os << start << elems;
	}

	return os;
}


// ************************************************************************* //