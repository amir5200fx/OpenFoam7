#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Matcher, class StringType>
tnbLib::labelList tnbLib::findMatchingStrings
(
	const Matcher& matcher,
	const UList<StringType>& lst,
	const bool invert
)
{
	labelList indices(lst.size());

	label nElem = 0;
	forAll(lst, elemI)
	{
		if (matcher.match(lst[elemI]) ? !invert : invert)
		{
			indices[nElem++] = elemI;
		}
	}
	indices.setSize(nElem);

	return indices;
}


template<class Matcher, class StringListType>
StringListType tnbLib::subsetMatchingStrings
(
	const Matcher& matcher,
	const StringListType& lst,
	const bool invert
)
{
	// Create copy
	StringListType newLst(lst.size());

	// ensure consistent addressable size (eg, DynamicList)
	newLst.setSize(lst.size());

	label nElem = 0;
	forAll(lst, elemI)
	{
		if (matcher.match(lst[elemI]) ? !invert : invert)
		{
			newLst[nElem++] = lst[elemI];
		}
	}
	newLst.setSize(nElem);

	return newLst;
}


template<class Matcher, class StringListType>
void tnbLib::inplaceSubsetMatchingStrings
(
	const Matcher& matcher,
	StringListType& lst,
	const bool invert
)
{
	label nElem = 0;
	forAll(lst, elemI)
	{
		if (matcher.match(lst[elemI]) ? !invert : invert)
		{
			lst[nElem++] = lst[elemI];
		}
	}
	lst.setSize(nElem);
}


// ************************************************************************* //