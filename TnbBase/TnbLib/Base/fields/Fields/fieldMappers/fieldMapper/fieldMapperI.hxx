#pragma once
// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::fieldMapper::operator()
(
	Field<Type>& f,
	const tmp<Field<Type>>& tmapF
	) const
{
	operator()(f, tmapF());
	tmapF.clear();
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>> tnbLib::fieldMapper::operator()
(
	const tmp<Field<Type>>& tmapF
	) const
{
	tmp<tnbLib::Field<Type>> tf(operator()(tmapF()));
	tmapF.clear();
	return tf;
}


// ************************************************************************* //