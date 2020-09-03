#pragma once
#include <ListOps.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class T>
tnbLib::SortableList<T>::SortableList()
{}


template<class T>
tnbLib::SortableList<T>::SortableList(const UList<T>& values)
	:
	List<T>(values)
{
	sort();
}


template<class T>
tnbLib::SortableList<T>::SortableList(List<T>&& values)
	:
	List<T>(move(values))
{
	sort();
}


template<class T>
tnbLib::SortableList<T>::SortableList(const label size)
	:
	List<T>(size)
{}


template<class T>
tnbLib::SortableList<T>::SortableList(const label size, const T& val)
	:
	List<T>(size, val)
{}


template<class T>
tnbLib::SortableList<T>::SortableList(const SortableList<T>& lst)
	:
	List<T>(lst),
	indices_(lst.indices())
{}


template<class T>
tnbLib::SortableList<T>::SortableList(SortableList<T>&& lst)
	:
	List<T>(move(lst)),
	indices_(move(lst.indices()))
{}


template<class T>
tnbLib::SortableList<T>::SortableList(std::initializer_list<T> values)
	:
	List<T>(values)
{
	sort();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //


template<class T>
void tnbLib::SortableList<T>::clear()
{
	List<T>::clear();
	indices_.clear();
}


template<class T>
tnbLib::List<T>& tnbLib::SortableList<T>::shrink()
{
	indices_.clear();
	return static_cast<List<T>&>(*this);
}


template<class T>
void tnbLib::SortableList<T>::sort()
{
	sortedOrder(*this, indices_);

	List<T> lst(this->size());
	forAll(indices_, i)
	{
		lst[i] = this->operator[](indices_[i]);
	}

	List<T>::transfer(lst);
}


template<class T>
void tnbLib::SortableList<T>::reverseSort()
{
	sortedOrder(*this, indices_, typename UList<T>::greater(*this));

	List<T> lst(this->size());
	forAll(indices_, i)
	{
		lst[i] = this->operator[](indices_[i]);
	}

	List<T>::transfer(lst);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class T>
inline void tnbLib::SortableList<T>::operator=(const T& t)
{
	UList<T>::operator=(t);
}


template<class T>
inline void tnbLib::SortableList<T>::operator=(const UList<T>& lst)
{
	List<T>::operator=(lst);
	indices_.clear();
}


template<class T>
inline void tnbLib::SortableList<T>::operator=(const SortableList<T>& lst)
{
	List<T>::operator=(lst);
	indices_ = lst.indices();
}


template<class T>
inline void tnbLib::SortableList<T>::operator=(SortableList<T>&& lst)
{
	List<T>::operator=(move(lst));
	indices_ = move(lst.indices());
}


template<class T>
inline void tnbLib::SortableList<T>::operator=(std::initializer_list<T> lst)
{
	List<T>::operator=(lst);
	sort();
}


// ************************************************************************* //