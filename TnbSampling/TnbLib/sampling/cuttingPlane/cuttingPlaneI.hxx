#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::tmp<tnbLib::Field<Type>> tnbLib::cuttingPlane::sample
(
	const Field<Type>& fld
) const
{
	return tmp<Field<Type>>(new Field<Type>(fld, cutCells()));
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>> tnbLib::cuttingPlane::sample
(
	const tmp<Field<Type>>& tfld
) const
{
	tmp<Field<Type>> tsf = sample(tfld());
	tfld.clear();
	return tsf;
}

// ************************************************************************* //