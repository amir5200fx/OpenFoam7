#pragma once
// * * * * * * * * * * * * * * * Global Functions  * * * * * * * * * * * * * //

template<class ListType>
ListType tnbLib::renumber
(
	const labelUList& oldToNew,
	const ListType& lst
)
{
	// Create copy
	ListType newLst(lst.size());

	// ensure consistent addressable size (eg, DynamicList)
	newLst.setSize(lst.size());

	forAll(lst, elemI)
	{
		if (lst[elemI] >= 0)
		{
			newLst[elemI] = oldToNew[lst[elemI]];
		}
	}

	return newLst;
}


template<class ListType>
void tnbLib::inplaceRenumber
(
	const labelUList& oldToNew,
	ListType& lst
)
{
	forAll(lst, elemI)
	{
		if (lst[elemI] >= 0)
		{
			lst[elemI] = oldToNew[lst[elemI]];
		}
	}
}


template<class ListType>
ListType tnbLib::reorder
(
	const labelUList& oldToNew,
	const ListType& lst
)
{
	// Create copy
	ListType newLst(lst.size());

	// ensure consistent addressable size (eg, DynamicList)
	newLst.setSize(lst.size());

	forAll(lst, elemI)
	{
		if (oldToNew[elemI] >= 0)
		{
			newLst[oldToNew[elemI]] = lst[elemI];
		}
		else
		{
			newLst[elemI] = lst[elemI];
		}
	}
	return newLst;
}


template<class ListType>
void tnbLib::inplaceReorder
(
	const labelUList& oldToNew,
	ListType& lst
)
{
	// Create copy
	ListType newLst(lst.size());

	// ensure consistent addressable size (eg, DynamicList)
	newLst.setSize(lst.size());

	forAll(lst, elemI)
	{
		if (oldToNew[elemI] >= 0)
		{
			newLst[oldToNew[elemI]] = lst[elemI];
		}
		else
		{
			newLst[elemI] = lst[elemI];
		}
	}

	lst.transfer(newLst);
}


template<class Container>
void tnbLib::inplaceMapValue
(
	const labelUList& oldToNew,
	Container& lst
)
{
	for
		(
			typename Container::iterator iter = lst.begin();
			iter != lst.end();
			++iter
			)
	{
		if (*iter >= 0)
		{
			*iter = oldToNew[*iter];
		}
	}
}


template<class Container>
void tnbLib::inplaceMapKey
(
	const labelUList& oldToNew,
	Container& lst
)
{
	Container newLst(lst.size());

	for
		(
			typename Container::iterator iter = lst.begin();
			iter != lst.end();
			++iter
			)
	{
		if (iter.key() >= 0)
		{
			newLst.insert(oldToNew[iter.key()], iter());
		}
	}

	lst.transfer(newLst);
}


template<class T>
void tnbLib::sortedOrder
(
	const UList<T>& lst,
	labelList& order
)
{
	sortedOrder(lst, order, typename UList<T>::less(lst));
}


template<class T, class Cmp>
void tnbLib::sortedOrder
(
	const UList<T>& lst,
	labelList& order,
	const Cmp& cmp
)
{
	// list lengths must be identical
	if (order.size() != lst.size())
	{
		// avoid copying any elements, they are overwritten anyhow
		order.clear();
		order.setSize(lst.size());
	}

	forAll(order, elemI)
	{
		order[elemI] = elemI;
	}
	tnbLib::stableSort(order, cmp);
}


template<class T>
void tnbLib::duplicateOrder
(
	const UList<T>& lst,
	labelList& order
)
{
	duplicateOrder(lst, order, typename UList<T>::less(lst));
}


template<class T, class Cmp>
void tnbLib::duplicateOrder
(
	const UList<T>& lst,
	labelList& order,
	const Cmp& cmp
)
{
	if (lst.size() < 2)
	{
		order.clear();
		return;
	}

	sortedOrder(lst, order, cmp);

	label n = 0;
	for (label i = 0; i < order.size() - 1; ++i)
	{
		if (lst[order[i]] == lst[order[i + 1]])
		{
			order[n++] = order[i];
		}
	}
	order.setSize(n);
}


template<class T>
void tnbLib::uniqueOrder
(
	const UList<T>& lst,
	labelList& order
)
{
	uniqueOrder(lst, order, typename UList<T>::less(lst));
}


template<class T, class Cmp>
void tnbLib::uniqueOrder
(
	const UList<T>& lst,
	labelList& order,
	const Cmp& cmp
)
{
	sortedOrder(lst, order, cmp);

	if (order.size() > 1)
	{
		label n = 0;
		for (label i = 0; i < order.size() - 1; ++i)
		{
			if (lst[order[i]] != lst[order[i + 1]])
			{
				order[n++] = order[i];
			}
		}
		order[n++] = order[order.size() - 1];
		order.setSize(n);
	}
}


template<class T, class ListType>
ListType tnbLib::subset
(
	const UList<T>& select,
	const T& value,
	const ListType& lst
)
{
	// select must at least cover the list range
	if (select.size() < lst.size())
	{
		FatalErrorInFunction
			<< "select is of size " << select.size()
			<< "; but it must index a list of size " << lst.size()
			<< abort(FatalError);
	}

	ListType newLst(lst.size());

	// ensure consistent addressable size (eg, DynamicList)
	newLst.setSize(lst.size());

	label nElem = 0;
	forAll(lst, elemI)
	{
		if (select[elemI] == value)
		{
			newLst[nElem++] = lst[elemI];
		}
	}
	newLst.setSize(nElem);

	return newLst;
}


template<class T, class ListType>
void tnbLib::inplaceSubset
(
	const UList<T>& select,
	const T& value,
	ListType& lst
)
{
	// select must at least cover the list range
	if (select.size() < lst.size())
	{
		FatalErrorInFunction
			<< "select is of size " << select.size()
			<< "; but it must index a list of size " << lst.size()
			<< abort(FatalError);
	}

	label nElem = 0;
	forAll(lst, elemI)
	{
		if (select[elemI] == value)
		{
			if (nElem != elemI)
			{
				lst[nElem] = lst[elemI];
			}
			++nElem;
		}
	}

	lst.setSize(nElem);
}


template<class BoolListType, class ListType>
ListType tnbLib::subset
(
	const BoolListType& select,
	const ListType& lst
)
{
	// select can have a different size
	// eg, when it is a PackedBoolList or a labelHashSet

	ListType newLst(lst.size());

	// ensure consistent addressable size (eg, DynamicList)
	newLst.setSize(lst.size());

	label nElem = 0;
	forAll(lst, elemI)
	{
		if (select[elemI])
		{
			newLst[nElem++] = lst[elemI];
		}
	}
	newLst.setSize(nElem);

	return newLst;
}


template<class BoolListType, class ListType>
void tnbLib::inplaceSubset
(
	const BoolListType& select,
	ListType& lst
)
{
	// select can have a different size
	// eg, when it is a PackedBoolList or a labelHashSet

	label nElem = 0;
	forAll(lst, elemI)
	{
		if (select[elemI])
		{
			if (nElem != elemI)
			{
				lst[nElem] = lst[elemI];
			}
			++nElem;
		}
	}

	lst.setSize(nElem);
}


template<class InList, class OutList>
void tnbLib::invertManyToMany
(
	const label nEdges,
	const UList<InList>& pointEdges,
	List<OutList>& edges
)
{
	// Number of points per edge
	labelList nPointsPerEdge(nEdges, 0);

	forAll(pointEdges, pointi)
	{
		const InList& pEdges = pointEdges[pointi];

		forAll(pEdges, j)
		{
			nPointsPerEdge[pEdges[j]]++;
		}
	}

	// Size edges
	edges.setSize(nEdges);

	forAll(nPointsPerEdge, edgeI)
	{
		edges[edgeI].setSize(nPointsPerEdge[edgeI]);
	}
	nPointsPerEdge = 0;

	// Fill edges
	forAll(pointEdges, pointi)
	{
		const InList& pEdges = pointEdges[pointi];

		forAll(pEdges, j)
		{
			label edgeI = pEdges[j];

			edges[edgeI][nPointsPerEdge[edgeI]++] = pointi;
		}
	}
}


template<class ListType>
tnbLib::label tnbLib::findIndex
(
	const ListType& l,
	typename ListType::const_reference t,
	const label start
)
{
	label index = -1;

	for (label i = start; i < l.size(); i++)
	{
		if (l[i] == t)
		{
			index = i;
			break;
		}
	}

	return index;
}


template<class ListType>
tnbLib::labelList tnbLib::findIndices
(
	const ListType& l,
	typename ListType::const_reference t,
	const label start
)
{
	// Count occurrences
	label n = 0;

	for (label i = start; i < l.size(); i++)
	{
		if (l[i] == t)
		{
			n++;
		}
	}

	// Create and fill
	labelList indices(n);
	n = 0;

	for (label i = start; i < l.size(); i++)
	{
		if (l[i] == t)
		{
			indices[n++] = i;
		}
	}

	return indices;
}


template<class ListType>
void tnbLib::setValues
(
	ListType& l,
	const labelUList& indices,
	typename ListType::const_reference t
)
{
	forAll(indices, i)
	{
		l[indices[i]] = t;
	}
}


template<class ListType>
ListType tnbLib::createWithValues
(
	const label sz,
	const typename ListType::const_reference initValue,
	const labelUList& indices,
	typename ListType::const_reference setValue
)
{
	ListType l(sz, initValue);
	setValues(l, indices, setValue);
	return l;
}


template<class ListType>
tnbLib::label tnbLib::findMax(const ListType& l, const label start)
{
	if (start >= l.size())
	{
		return -1;
	}

	label index = start;

	for (label i = start + 1; i < l.size(); i++)
	{
		if (l[i] > l[index])
		{
			index = i;
		}
	}

	return index;
}


template<class ListType>
tnbLib::label tnbLib::findMin(const ListType& l, const label start)
{
	if (start >= l.size())
	{
		return -1;
	}

	label index = start;

	for (label i = start + 1; i < l.size(); i++)
	{
		if (l[i] < l[index])
		{
			index = i;
		}
	}

	return index;
}


template<class ListType>
tnbLib::label tnbLib::findSortedIndex
(
	const ListType& l,
	typename ListType::const_reference t,
	const label start
)
{
	if (start >= l.size())
	{
		return -1;
	}

	label low = start;
	label high = l.size() - 1;

	while (low <= high)
	{
		label mid = (low + high) / 2;

		if (t < l[mid])
		{
			high = mid - 1;
		}
		else if (t > l[mid])
		{
			low = mid + 1;
		}
		else
		{
			return mid;
		}
	}

	return -1;
}


template<class ListType, class BinaryOp>
tnbLib::label tnbLib::findLower
(
	const ListType& l,
	typename ListType::const_reference t,
	const label start,
	const BinaryOp& bop
)
{
	if (start >= l.size())
	{
		return -1;
	}

	label low = start;
	label high = l.size() - 1;

	while ((high - low) > 1)
	{
		label mid = (low + high) / 2;

		if (bop(l[mid], t))
		{
			low = mid;
		}
		else
		{
			high = mid;
		}
	}

	if (bop(l[high], t))
	{
		return high;
	}
	else
	{
		if (bop(l[low], t))
		{
			return low;
		}
		else
		{
			return -1;
		}
	}
}


template<class ListType>
tnbLib::label tnbLib::findLower
(
	const ListType& l,
	typename ListType::const_reference t,
	const label start
)
{
	return findLower(l, t, start, lessOp<typename ListType::value_type>());
}


template<class Container, class T, int mRows>
tnbLib::List<Container> tnbLib::initList(const T elems[mRows])
{
	List<Container> lst(mRows);

	forAll(lst, rowI)
	{
		lst[rowI] = Container(elems[rowI]);
	}
	return lst;
}


template<class Container, class T, int mRows, int nColumns>
tnbLib::List<Container> tnbLib::initListList(const T elems[mRows][nColumns])
{
	List<Container> lst(mRows);

	Container cols(nColumns);
	forAll(lst, rowI)
	{
		forAll(cols, colI)
		{
			cols[colI] = elems[rowI][colI];
		}
		lst[rowI] = cols;
	}
	return lst;
}


template<class T>
void tnbLib::ListAppendEqOp<T>::operator()(List<T>& x, const List<T>& y) const
{
	if (y.size())
	{
		if (x.size())
		{
			label sz = x.size();
			x.setSize(sz + y.size());
			forAll(y, i)
			{
				x[sz++] = y[i];
			}
		}
		else
		{
			x = y;
		}
	}
}


template<class ListType>
ListType tnbLib::reverseList(const ListType& list)
{
	const label listSize = list.size();
	const label lastIndex = listSize - 1;

	ListType tmpList(listSize);

	forAll(tmpList, elemI)
	{
		tmpList[elemI] = list[lastIndex - elemI];
	}

	return tmpList;
}


template<class ListType>
void tnbLib::inplaceReverseList(ListType& list)
{
	const label listSize = list.size();
	const label lastIndex = listSize - 1;
	const label nIterations = listSize >> 1;

	label elemI = 0;
	while (elemI < nIterations)
	{
		Swap(list[elemI], list[lastIndex - elemI]);

		elemI++;
	}
}


template<class ListType>
ListType tnbLib::rotateList(const ListType& list, const label n)
{
	const label listSize = list.size();

	ListType tmpList(listSize);

	forAll(tmpList, elemI)
	{
		label index = (elemI - n) % listSize;

		if (index < 0)
		{
			index += listSize;
		}

		tmpList[elemI] = list[index];
	}

	return tmpList;
}


template<template<typename> class ListType, class DataType>
void tnbLib::inplaceRotateList(ListType<DataType>& list, label n)
{
	const label listSize = list.size();

	n = (listSize - n) % listSize;

	if (n < 0)
	{
		n += listSize;
	}

	SubList<DataType> firstHalf(list, n, 0);
	SubList<DataType> secondHalf(list, listSize - n, n);

	inplaceReverseList(firstHalf);
	inplaceReverseList(secondHalf);

	inplaceReverseList(list);
}


// ************************************************************************* //