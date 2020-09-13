#pragma once
#include <flipOp.hxx>  // added by amir

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class Type>
void tnbLib::distributedWeightedFvPatchFieldMapper::map
(
	Field<Type>& f,
	const Field<Type>& mapF
) const
{
	if (singlePatchProc_ == -1)
	{
		// Fetch remote parts of mapF
		const mapDistributeBase& distMap = *distMapPtr_;
		Field<Type> newMapF(mapF);

		// Moved flux "flip" functionality to higher level
		// if (applyFlip)
		// {
		//     distMap.distribute(newMapF);
		// }
		// else
		{
			distMap.distribute(newMapF, noOp());
		}

		f.map(newMapF, addressing(), weights());
	}
	else
	{
		f.map(mapF, addressing(), weights());
	}
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>> tnbLib::distributedWeightedFvPatchFieldMapper::map
(
	const Field<Type>& mapF
) const
{
	tmp<Field<Type>> tf(new Field<Type>(size()));
	map(tf.ref(), mapF);
	return tf;
}


template<class Type>
void tnbLib::distributedWeightedFvPatchFieldMapper::operator()
(
	Field<Type>& f,
	const tmp<Field<Type>>& tmapF
	) const
{
	map(f, tmapF());
	tmapF.clear();
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::distributedWeightedFvPatchFieldMapper::operator()
(
	const tmp<Field<Type>>& tmapF
	) const
{
	tmp<tnbLib::Field<Type>> tf(map(tmapF()));
	tmapF.clear();
	return tf;
}


// ************************************************************************* //