#pragma once

template<class Type>
void tnbLib::pairPatchAgglomeration::restrictField
(
	Field<Type>& cf,
	const Field<Type>& ff,
	const label fineLevelIndex
) const
{
	const labelList& fineToCoarse = restrictAddressing_[fineLevelIndex];

	if (ff.size() != fineToCoarse.size())
	{
		FatalErrorInFunction
			<< "field does not correspond to level " << fineLevelIndex
			<< " sizes: field = " << ff.size()
			<< " level = " << fineToCoarse.size()
			<< abort(FatalError);
	}

	cf = Zero;

	forAll(ff, i)
	{
		cf[fineToCoarse[i]] += ff[i];
	}
}


template<class Type>
void tnbLib::pairPatchAgglomeration::prolongField
(
	Field<Type>& ff,
	const Field<Type>& cf,
	const label coarseLevelIndex
) const
{
	const labelList& fineToCoarse = restrictAddressing_[coarseLevelIndex];

	forAll(fineToCoarse, i)
	{
		ff[i] = cf[fineToCoarse[i]];
	}
}