#pragma once
#include <ListLoopM.hxx>

// * * * * * * * * * * * * * * STL Member Functions  * * * * * * * * * * * * //

template<class T, unsigned Size>
void tnbLib::FixedList<T, Size>::swap(FixedList<T, Size>& a)
{
	List_ACCESS(T, (*this), vp);
	List_ACCESS(T, a, ap);
	T tmp;
	List_FOR_ALL((*this), i)
		tmp = List_CELEM((*this), vp, i);
	List_ELEM((*this), vp, i) = List_CELEM(a, ap, i);
	List_ELEM(a, ap, i) = tmp;
	List_END_FOR_ALL
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class T, unsigned Size>
bool tnbLib::FixedList<T, Size>::operator==(const FixedList<T, Size>& a) const
{
	bool equal = true;

	List_CONST_ACCESS(T, (*this), vp);
	List_CONST_ACCESS(T, (a), ap);

	List_FOR_ALL((*this), i)
		equal = equal && (List_ELEM((*this), vp, i) == List_ELEM((a), ap, i));
	List_END_FOR_ALL

		return equal;
}


template<class T, unsigned Size>
bool tnbLib::FixedList<T, Size>::operator!=(const FixedList<T, Size>& a) const
{
	return !operator==(a);
}


template<class T, unsigned Size>
bool tnbLib::FixedList<T, Size>::operator<(const FixedList<T, Size>& a) const
{
	for
		(
			const_iterator vi = cbegin(), ai = a.cbegin();
			vi < cend() && ai < a.cend();
			vi++, ai++
			)
	{
		if (*vi < *ai)
		{
			return true;
		}
		else if (*vi > *ai)
		{
			return false;
		}
	}

	if (Size < a.Size)
	{
		return true;
	}
	else
	{
		return false;
	}
}


template<class T, unsigned Size>
bool tnbLib::FixedList<T, Size>::operator>(const FixedList<T, Size>& a) const
{
	return a.operator<(*this);
}


template<class T, unsigned Size>
bool tnbLib::FixedList<T, Size>::operator<=(const FixedList<T, Size>& a) const
{
	return !operator>(a);
}


template<class T, unsigned Size>
bool tnbLib::FixedList<T, Size>::operator>=(const FixedList<T, Size>& a) const
{
	return !operator<(a);
}


// * * * * * * * * * * * * * * * *  IOStream operators * * * * * * * * * * * //