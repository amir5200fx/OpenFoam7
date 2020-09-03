#pragma once
#include <IOstreams.hxx> // added by amir

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class T, class BaseType>
bool tnbLib::ListCompactIO<T, BaseType>::overflows() const
{
	label size = 0;
	forAll(*this, i)
	{
		label oldSize = size;
		size += this->operator[](i).size();
		if (size < oldSize)
		{
			return true;
		}
	}
	return false;
}


template<class T, class BaseType>
void tnbLib::ListCompactIO<T, BaseType>::convertToCompact
(
	labelList& start,
	List<BaseType>& elems
) const
{
	start.setSize(this->size() + 1);

	start[0] = 0;
	for (label i = 1; i < start.size(); i++)
	{
		label prev = start[i - 1];
		start[i] = prev + this->operator[](i - 1).size();

		if (start[i] < prev)
		{
			FatalErrorInFunction
				<< "Overall number of elements " << start[i]
				<< " of ListCompactIO of size "
				<< this->size() << " overflows the representation of a label"
				<< endl << "Please recompile with a larger representation"
				<< " for label" << exit(FatalError);
		}
	}

	elems.setSize(start[start.size() - 1]);

	label elemi = 0;
	forAll(*this, i)
	{
		const T& subList = this->operator[](i);

		forAll(subList, j)
		{
			elems[elemi++] = subList[j];
		}
	}
}


template<class T, class BaseType>
void tnbLib::ListCompactIO<T, BaseType>::convertFromCompact
(
	const labelList& start,
	const List<BaseType>& elems
)
{
	this->setSize(start.size() - 1);

	forAll(*this, i)
	{
		T& subList = this->operator[](i);

		label index = start[i];
		subList.setSize(start[i + 1] - index);

		forAll(subList, j)
		{
			subList[j] = elems[index++];
		}
	}
}


// * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * * //

template<class T, class BaseType>
tnbLib::ListCompactIO<T, BaseType>::ListCompactIO()
{}


template<class T, class BaseType>
tnbLib::ListCompactIO<T, BaseType>::ListCompactIO(const UList<T>& l)
	:
	List<T>(l)
{}


template<class T, class BaseType>
tnbLib::ListCompactIO<T, BaseType>::ListCompactIO(Istream& is)
{
	is >> *this;
}


template<class T, class BaseType>
tnbLib::ListCompactIO<T, BaseType>::ListCompactIO(ListCompactIO<T, BaseType>&& l)
	:
	List<T>(move(l))
{}


template<class T, class BaseType>
tnbLib::ListCompactIO<T, BaseType>::ListCompactIO(List<T>&& l)
	:
	List<T>(move(l))
{}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class T, class BaseType>
void tnbLib::ListCompactIO<T, BaseType>::operator=
(
	const ListCompactIO<T, BaseType>& rhs
	)
{
	List<T>::operator=(rhs);
}


template<class T, class BaseType>
void tnbLib::ListCompactIO<T, BaseType>::operator=
(
	ListCompactIO<T, BaseType>&& rhs
	)
{
	List<T>::operator=(move(rhs));
}


template<class T, class BaseType>
void tnbLib::ListCompactIO<T, BaseType>::operator=(const List<T>& rhs)
{
	List<T>::operator=(rhs);
}


template<class T, class BaseType>
void tnbLib::ListCompactIO<T, BaseType>::operator=(List<T>&& rhs)
{
	List<T>::operator=(move(rhs));
}


// * * * * * * * * * * * * * * * Friend Functions  * * * * * * * * * * * * * //

template<class T, class BaseType>
void tnbLib::writeEntry(Ostream& os, const ListCompactIO<T, BaseType>& l)
{
	// Keep ascii writing same.
	if (os.format() == IOstream::ASCII)
	{
		os << static_cast<const List<T>&>(l);
	}
	else
	{
		labelList start;
		List<BaseType> elems;
		l.convertToCompact(start, elems);
		writeEntry(os, start);
		writeEntry(os, elems);
	}
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

template<class T, class BaseType>
tnbLib::Istream& tnbLib::operator>>
(
	tnbLib::Istream& is,
	tnbLib::ListCompactIO<T, BaseType>& L
	)
{
	if (is.format() == IOstream::ASCII)
	{
		is >> static_cast<List<T>&>(L);
	}
	else
	{
		labelList start(is);
		List<BaseType> elems(is);
		L.convertFromCompact(start, elems);
	}

	return is;
}


template<class T, class BaseType>
tnbLib::Ostream& tnbLib::operator<<
(
	tnbLib::Ostream& os,
	const tnbLib::ListCompactIO<T, BaseType>& L
	)
{
	// Keep ascii writing same.
	if (os.format() == IOstream::ASCII)
	{
		os << static_cast<const List<T>&>(L);
	}
	else
	{
		labelList start;
		List<BaseType> elems;
		L.convertToCompact(start, elems);
		os << start << elems;
	}

	return os;
}


// ************************************************************************* //