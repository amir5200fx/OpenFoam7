#include <polyTopoChange.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class T>
void tnbLib::polyTopoChange::reorder
(
	const labelList& oldToNew,
	DynamicList<T>& lst
)
{
	// Create copy
	DynamicList<T> oldLst(lst);

	forAll(oldToNew, elemI)
	{
		label newElemI = oldToNew[elemI];

		if (newElemI != -1)
		{
			lst[newElemI] = oldLst[elemI];
		}
	}
}


template<class T>
void tnbLib::polyTopoChange::reorder
(
	const labelList& oldToNew,
	List<DynamicList<T>>& lst
)
{
	// Create copy
	List<DynamicList<T>> oldLst(lst);

	forAll(oldToNew, elemI)
	{
		label newElemI = oldToNew[elemI];

		if (newElemI != -1)
		{
			lst[newElemI].transfer(oldLst[elemI]);
		}
	}
}


template<class T>
void tnbLib::polyTopoChange::renumberKey
(
	const labelList& oldToNew,
	Map<T>& elems
)
{
	Map<T> newElems(elems.size());

	forAllConstIter(typename Map<T>, elems, iter)
	{
		label newElem = oldToNew[iter.key()];

		if (newElem >= 0)
		{
			newElems.insert(newElem, iter());
		}
	}

	elems.transfer(newElems);
}


// ************************************************************************* //