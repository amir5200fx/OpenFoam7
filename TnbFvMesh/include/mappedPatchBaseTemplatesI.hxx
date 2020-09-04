#pragma once
#include <flipOp.hxx> // added by amir

template<class Type>
void tnbLib::mappedPatchBase::distribute(List<Type>& lst) const
{
	switch (mode_)
	{
	case NEARESTPATCHFACEAMI:
	{
		lst = AMI().interpolateToSource(Field<Type>(move(lst)));
		break;
	}
	default:
	{
		map().distribute(lst);
	}
	}
}


template<class Type, class CombineOp>
void tnbLib::mappedPatchBase::distribute
(
	List<Type>& lst,
	const CombineOp& cop
) const
{
	switch (mode_)
	{
	case NEARESTPATCHFACEAMI:
	{
		lst = AMI().interpolateToSource
		(
			Field<Type>(move(lst)),
			cop
		);
		break;
	}
	default:
	{
		mapDistributeBase::distribute
		(
			Pstream::defaultCommsType,
			map().schedule(),
			map().constructSize(),
			map().subMap(),
			false,
			map().constructMap(),
			false,
			lst,
			cop,
			flipOp(),
			Type(Zero)
		);
	}
	}
}


template<class Type>
void tnbLib::mappedPatchBase::reverseDistribute(List<Type>& lst) const
{
	switch (mode_)
	{
	case NEARESTPATCHFACEAMI:
	{
		lst = AMI().interpolateToTarget(Field<Type>(move(lst)));
		break;
	}
	default:
	{
		map().reverseDistribute(sampleSize(), lst);
		break;
	}
	}
}


template<class Type, class CombineOp>
void tnbLib::mappedPatchBase::reverseDistribute
(
	List<Type>& lst,
	const CombineOp& cop
) const
{
	switch (mode_)
	{
	case NEARESTPATCHFACEAMI:
	{
		lst = AMI().interpolateToTarget
		(
			Field<Type>(move(lst)),
			cop
		);
		break;
	}
	default:
	{
		label cSize = sampleSize();
		mapDistributeBase::distribute
		(
			Pstream::defaultCommsType,
			map().schedule(),
			cSize,
			map().constructMap(),
			false,
			map().subMap(),
			false,
			lst,
			cop,
			flipOp(),
			Type(Zero)
		);
		break;
	}
	}
}


// ************************************************************************* //