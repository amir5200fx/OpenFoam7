#pragma once
#include <IOstreams.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //


template<class LabelListType>
tnbLib::label tnbLib::PackedBoolList::setIndices(const LabelListType& indices)
{
	// no better information, just guess something about the size
	reserve(indices.size());

	label cnt = 0;
	forAll(indices, elemI)
	{
		if (set(indices[elemI]))
		{
			++cnt;
		}
	}

	return cnt;
}


template<class LabelListType>
tnbLib::label tnbLib::PackedBoolList::unsetIndices(const LabelListType& indices)
{
	label cnt = 0;
	forAll(indices, elemI)
	{
		if (unset(indices[elemI]))
		{
			++cnt;
		}
	}

	return cnt;
}


template<class LabelListType>
tnbLib::label tnbLib::PackedBoolList::subsetIndices(const LabelListType& indices)
{
	// handle trivial case
	if (empty() || indices.empty())
	{
		clear();
		return 0;
	}

	// normal case
	PackedBoolList anded;
	anded.reserve(size());

	label cnt = 0;
	forAll(indices, elemI)
	{
		const label& index = indices[elemI];
		if (operator[](index))
		{
			anded.set(index);
			++cnt;
		}
	}

	transfer(anded);
	return cnt;
}


