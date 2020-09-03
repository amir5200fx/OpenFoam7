#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type, class DType, class LUType>
tnbLib::NoPreconditioner<Type, DType, LUType>::NoPreconditioner
(
	const typename LduMatrix<Type, DType, LUType>::solver& sol,
	const dictionary&
)
	:
	LduMatrix<Type, DType, LUType>::preconditioner(sol)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type, class DType, class LUType>
void tnbLib::NoPreconditioner<Type, DType, LUType>::read(const dictionary&)
{}


template<class Type, class DType, class LUType>
void tnbLib::NoPreconditioner<Type, DType, LUType>::precondition
(
	Field<Type>& wA,
	const Field<Type>& rA
) const
{
	wA = rA;
}


// ************************************************************************* //