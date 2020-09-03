#pragma once
#include <Pstream.hxx>
#include <PstreamBuffers.hxx>
#include <PstreamCombineReduceOps.hxx>
#include <transformField.hxx>
#include <globalIndexAndTransform.hxx>
#include <flipOp.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class T>
void tnbLib::mapDistribute::applyDummyTransforms(List<T>& field) const
{
	forAll(transformElements_, trafoI)
	{
		const labelList& elems = transformElements_[trafoI];

		label n = transformStart_[trafoI];

		forAll(elems, i)
		{
			field[n++] = field[elems[i]];
		}
	}
}


template<class T>
void tnbLib::mapDistribute::applyDummyInverseTransforms(List<T>& field) const
{
	forAll(transformElements_, trafoI)
	{
		const labelList& elems = transformElements_[trafoI];
		label n = transformStart_[trafoI];

		forAll(elems, i)
		{
			field[elems[i]] = field[n++];
		}
	}
}


template<class T, class TransformOp>   //, class CombineOp>
void tnbLib::mapDistribute::applyTransforms
(
	const globalIndexAndTransform& globalTransforms,
	List<T>& field,
	const TransformOp& top
) const
{
	const List<vectorTensorTransform>& totalTransform =
		globalTransforms.transformPermutations();

	forAll(totalTransform, trafoI)
	{
		const vectorTensorTransform& vt = totalTransform[trafoI];
		const labelList& elems = transformElements_[trafoI];
		label n = transformStart_[trafoI];

		// Could be optimised to avoid memory allocations
		List<T> transformFld(UIndirectList<T>(field, elems));
		top(vt, true, transformFld);

		forAll(transformFld, i)
		{
			// cop(field[n++], transformFld[i]);
			field[n++] = transformFld[i];
		}
	}
}


template<class T, class TransformOp>   //, class CombineOp>
void tnbLib::mapDistribute::applyInverseTransforms
(
	const globalIndexAndTransform& globalTransforms,
	List<T>& field,
	const TransformOp& top
) const
{
	const List<vectorTensorTransform>& totalTransform =
		globalTransforms.transformPermutations();

	forAll(totalTransform, trafoI)
	{
		const vectorTensorTransform& vt = totalTransform[trafoI];
		const labelList& elems = transformElements_[trafoI];
		label n = transformStart_[trafoI];

		// Could be optimised to avoid memory allocations
		List<T> transformFld(SubList<T>(field, elems.size(), n));
		top(vt, false, transformFld);

		forAll(transformFld, i)
		{
			// cop(field[elems[i]], transformFld[i]);
			field[elems[i]] = transformFld[i];
		}
	}
}


template<class T, class negateOp>
void tnbLib::mapDistribute::distribute
(
	List<T>& fld,
	const negateOp& negOp,
	const bool dummyTransform,
	const int tag
) const
{
	mapDistributeBase::distribute(fld, negOp, tag);

	//- Fill in transformed slots with copies
	if (dummyTransform)
	{
		applyDummyTransforms(fld);
	}
}


template<class T>
void tnbLib::mapDistribute::distribute
(
	List<T>& fld,
	const bool dummyTransform,
	const int tag
) const
{
	distribute(fld, flipOp(), dummyTransform, tag);
}


template<class T>
void tnbLib::mapDistribute::distribute
(
	DynamicList<T>& fld,
	const bool dummyTransform,
	const int tag
) const
{
	fld.shrink();

	List<T>& fldList = static_cast<List<T>&>(fld);

	distribute(fldList, dummyTransform, tag);

	fld.setCapacity(fldList.size());
}


template<class T>
void tnbLib::mapDistribute::reverseDistribute
(
	const label constructSize,
	List<T>& fld,
	const bool dummyTransform,
	const int tag
) const
{
	if (dummyTransform)
	{
		applyDummyInverseTransforms(fld);
	}

	mapDistributeBase::reverseDistribute(constructSize, fld, tag);
}


template<class T>
void tnbLib::mapDistribute::reverseDistribute
(
	const label constructSize,
	const T& nullValue,
	List<T>& fld,
	const bool dummyTransform,
	const int tag
) const
{
	if (dummyTransform)
	{
		applyDummyInverseTransforms(fld);
	}

	mapDistributeBase::reverseDistribute(constructSize, nullValue, fld, tag);
}


template<class T, class TransformOp>
void tnbLib::mapDistribute::distribute
(
	const globalIndexAndTransform& git,
	List<T>& fld,
	const TransformOp& top,
	const int tag
) const
{
	// Distribute. Leave out dummy transforms since we're doing them ourselves
	distribute(fld, false, tag);
	// Do transforms
	applyTransforms(git, fld, top);
}


template<class T, class TransformOp>
void tnbLib::mapDistribute::reverseDistribute
(
	const globalIndexAndTransform& git,
	const label constructSize,
	List<T>& fld,
	const TransformOp& top,
	const int tag
) const
{
	// Fill slots with reverse-transformed data. Note that it also copies
	// back into the non-remote part of fld even though these values are not
	// used.
	applyInverseTransforms(git, fld, top);

	// And send back (the remote slots). Disable dummy transformations.
	reverseDistribute(constructSize, fld, false, tag);
}


template<class T, class TransformOp>
void tnbLib::mapDistribute::reverseDistribute
(
	const globalIndexAndTransform& git,
	const label constructSize,
	const T& nullValue,
	List<T>& fld,
	const TransformOp& top,
	const int tag
) const
{
	// Fill slots with reverse-transformed data Note that it also copies
	// back into the non-remote part of fld even though these values are not
	// used.
	applyInverseTransforms(git, fld, top);   //, eqOp<T>());

	// And send back (the remote slots) Disable dummy transformations.
	reverseDistribute(constructSize, nullValue, fld, false, tag);
}


// ************************************************************************* //