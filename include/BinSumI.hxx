#pragma once

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class IndexType, class List, class CombineOp>
tnbLib::BinSum<IndexType, List, CombineOp>::BinSum
(
	const IndexType min,
	const IndexType max,
	const IndexType delta
)
	:
	List(ceil((max - min) / delta), Zero),
	min_(min),
	max_(max),
	delta_(delta),
	lowSum_(Zero),
	highSum_(Zero)
{}


template<class IndexType, class List, class CombineOp>
tnbLib::BinSum<IndexType, List, CombineOp>::BinSum
(
	const IndexType min,
	const IndexType max,
	const IndexType delta,
	const UList<IndexType>& indexVals,
	const List& vals,
	const CombineOp& cop
)
	:
	List(ceil((max - min) / delta), Zero),
	min_(min),
	max_(max),
	delta_(delta),
	lowSum_(Zero),
	highSum_(Zero)
{
	forAll(indexVals, i)
	{
		add(indexVals[i], vals[i], cop);
	}
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

template<class IndexType, class List, class CombineOp>
void tnbLib::BinSum<IndexType, List, CombineOp>::add
(
	const IndexType& indexVal,
	const typename List::const_reference val,
	const CombineOp& cop
)
{
	if (indexVal < min_)
	{
		cop(lowSum_, val);
	}
	else if (indexVal >= max_)
	{
		cop(highSum_, val);
	}
	else
	{
		label index = (indexVal - min_) / delta_;
		cop(this->operator[](index), val);
	}
}


template<class IndexType, class List, class CombineOp>
void tnbLib::BinSum<IndexType, List, CombineOp>::add
(
	const UList<IndexType>& indexVals,
	const List& vals,
	const CombineOp& cop
)
{
	forAll(indexVals, i)
	{
		add(indexVals[i], vals[i], cop);
	}
}


// ************************************************************************* //