#pragma once
#include <OSspecific.hxx>
#include <algorithm>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template <class Type>
tnbLib::SortableListDRGEP<Type>::SortableListDRGEP(const List<Type>& values)
	:
	List<Type>(values),
	indices_(values.size())
{
	sort();
}


template <class Type>
tnbLib::SortableListDRGEP<Type>::SortableListDRGEP(const label size)
	:
	List<Type>(size),
	indices_(size)
{}


template <class Type>
tnbLib::SortableListDRGEP<Type>::SortableListDRGEP
(
	const label size,
	const Type& val
)
	:
	List<Type>(size, val),
	indices_(size)
{}


template <class Type>
tnbLib::SortableListDRGEP<Type>::SortableListDRGEP
(
	const SortableListDRGEP<Type>& lst
)
	:
	List<Type>(lst),
	indices_(lst.indices())
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template <class Type>
void tnbLib::SortableListDRGEP<Type>::setSize(const label newSize)
{
	List<Type>::setSize(newSize);
	indices_.setSize(newSize);
}


template <class Type>
void tnbLib::SortableListDRGEP<Type>::sort()
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
void tnbLib::SortableListDRGEP<Type>::partialSort(int M)
{
	forAll(indices_, i)
	{
		indices_[i] = i;
	}

	std::partial_sort
	(
		indices_.begin(),
		indices_.begin() + M,
		indices_.end(),
		less(*this)
	);
}


template <class Type>
void tnbLib::SortableListDRGEP<Type>::stableSort()
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
void
tnbLib::SortableListDRGEP<Type>::operator=(const SortableListDRGEP<Type>& rhs)
{
	List<Type>::operator=(rhs);
	indices_ = rhs.indices();
}


// ************************************************************************* //