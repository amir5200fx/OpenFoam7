#pragma once
#include <ListLoopM.hxx>
#include <contiguous.hxx>

#include <algorithm>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class T>
void tnbLib::UList<T>::deepCopy(const UList<T>& a)
{
	if (a.size_ != this->size_)
	{
		FatalErrorInFunction
			<< "ULists have different sizes: "
			<< this->size_ << " " << a.size_
			<< abort(FatalError);
	}

	if (this->size_)
	{
#ifdef USEMEMCPY
		if (contiguous<T>())
		{
			memcpy(this->v_, a.v_, this->byteSize());
		}
		else
#endif
		{
			List_ACCESS(T, (*this), vp);
			List_CONST_ACCESS(T, a, ap);
			List_FOR_ALL((*this), i)
				List_ELEM((*this), vp, i) = List_ELEM(a, ap, i);
			List_END_FOR_ALL
		}
	}
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class T>
void tnbLib::UList<T>::operator=(const T& t)
{
	List_ACCESS(T, (*this), vp);
	List_FOR_ALL((*this), i)
		List_ELEM((*this), vp, i) = t;
	List_END_FOR_ALL
}


template<class T>
void tnbLib::UList<T>::operator=(const zero)
{
	List_ACCESS(T, (*this), vp);
	List_FOR_ALL((*this), i)
		List_ELEM((*this), vp, i) = Zero;
	List_END_FOR_ALL
}


// * * * * * * * * * * * * * * STL Member Functions  * * * * * * * * * * * * //

template<class T>
void tnbLib::UList<T>::swap(UList<T>& a)
{
	Swap(size_, a.size_);
	Swap(v_, a.v_);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class T>
std::streamsize tnbLib::UList<T>::byteSize() const
{
	if (!contiguous<T>())
	{
		FatalErrorInFunction
			<< "Cannot return the binary size of a list of "
			"non-primitive elements"
			<< abort(FatalError);
	}

	return this->size_ * sizeof(T);
}


template<class T>
void tnbLib::sort(UList<T>& a)
{
	std::sort(a.begin(), a.end());
}


template<class T, class Cmp>
void tnbLib::sort(UList<T>& a, const Cmp& cmp)
{
	std::sort(a.begin(), a.end(), cmp);
}


template<class T>
void tnbLib::stableSort(UList<T>& a)
{
	std::stable_sort(a.begin(), a.end());
}


template<class T, class Cmp>
void tnbLib::stableSort(UList<T>& a, const Cmp& cmp)
{
	std::stable_sort(a.begin(), a.end(), cmp);
}


template<class T>
void tnbLib::shuffle(UList<T>& a)
{
	std::random_shuffle(a.begin(), a.end());
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class T>
bool tnbLib::UList<T>::operator==(const UList<T>& a) const
{
	if (this->size_ != a.size_)
	{
		return false;
	}

	bool equal = true;

	List_CONST_ACCESS(T, (*this), vp);
	List_CONST_ACCESS(T, (a), ap);

	List_FOR_ALL((*this), i)
		equal = equal && (List_ELEM((*this), vp, i) == List_ELEM((a), ap, i));
	List_END_FOR_ALL

		return equal;
}


template<class T>
bool tnbLib::UList<T>::operator!=(const UList<T>& a) const
{
	return !operator==(a);
}


template<class T>
bool tnbLib::UList<T>::operator<(const UList<T>& a) const
{
	for
		(
			const_iterator vi = begin(), ai = a.begin();
			vi < end() && ai < a.end();
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

	if (this->size_ < a.size_)
	{
		return true;
	}
	else
	{
		return false;
	}
}


template<class T>
bool tnbLib::UList<T>::operator>(const UList<T>& a) const
{
	return a.operator<(*this);
}


template<class T>
bool tnbLib::UList<T>::operator<=(const UList<T>& a) const
{
	return !operator>(a);
}


template<class T>
bool tnbLib::UList<T>::operator>=(const UList<T>& a) const
{
	return !operator<(a);
}


// * * * * * * * * * * * * * * * *  IOStream operators * * * * * * * * * * * //