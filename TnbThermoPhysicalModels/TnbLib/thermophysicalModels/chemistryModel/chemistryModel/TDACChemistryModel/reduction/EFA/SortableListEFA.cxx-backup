#include <SortableListEFA.hxx>

#include <OSspecific.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template <class Type>
tnbLib::SortableListEFA<Type>::SortableListEFA(const List<Type>& values)
	:
	List<Type>(values),
	indices_(values.size())
{
	sort();
}


template <class Type>
tnbLib::SortableListEFA<Type>::SortableListEFA(const label size)
	:
	List<Type>(size),
	indices_(size)
{
	forAll(indices_, i)
	{
		indices_[i] = i;
	}
}


template <class Type>
tnbLib::SortableListEFA<Type>::SortableListEFA(const label size, const Type& val)
	:
	List<Type>(size, val),
	indices_(size)
{
	forAll(indices_, i)
	{
		indices_[i] = i;
	}
}


template <class Type>
tnbLib::SortableListEFA<Type>::SortableListEFA(const SortableListEFA<Type>& lst)
	:
	List<Type>(lst),
	indices_(lst.indices())
{
	forAll(indices_, i)
	{
		indices_[i] = i;
	}

}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template <class Type>
void tnbLib::SortableListEFA<Type>::setSize(const label newSize)
{
	List<Type>::setSize(newSize);
	indices_.setSize(newSize);
}


template <class Type>
void tnbLib::SortableListEFA<Type>::sort()
{
	forAll(indices_, i)
	{
		indices_[i] = i;
	}

	tnbLib::sort(indices_, less(*this));

	List<Type> tmpValues(this->size());

	forAll(indices_, i)
	{
		tmpValues[i] = this->operator[](indices_[i]);
	}

	List<Type>::transfer(tmpValues);
}


template <class Type>
void tnbLib::SortableListEFA<Type>::partialSort(int M, int start)
{
	std::partial_sort
	(
		indices_.begin() + start,
		indices_.begin() + start + M,
		indices_.end(),
		more(*this)
	);
}


template <class Type>
void tnbLib::SortableListEFA<Type>::stableSort()
{
	forAll(indices_, i)
	{
		indices_[i] = i;
	}

	tnbLib::stableSort(indices_, less(*this));

	List<Type> tmpValues(this->size());

	forAll(indices_, i)
	{
		tmpValues[i] = this->operator[](indices_[i]);
	}

	List<Type>::transfer(tmpValues);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template <class Type>
void tnbLib::SortableListEFA<Type>::operator=(const SortableListEFA<Type>& rhs)
{
	List<Type>::operator=(rhs);
	indices_ = rhs.indices();
}


// ************************************************************************* //