#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type, class DType, class LUType>
tnbLib::DiagonalSolver<Type, DType, LUType>::DiagonalSolver
(
	const word& fieldName,
	const LduMatrix<Type, DType, LUType>& matrix,
	const dictionary& solverDict
)
	:
	LduMatrix<Type, DType, LUType>::solver
	(
		fieldName,
		matrix,
		solverDict
	)
{}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type, class DType, class LUType>
void tnbLib::DiagonalSolver<Type, DType, LUType>::read
(
	const dictionary&
)
{}


template<class Type, class DType, class LUType>
tnbLib::SolverPerformance<Type>
tnbLib::DiagonalSolver<Type, DType, LUType>::solve
(
	Field<Type>& psi
) const
{
	psi = this->matrix_.source() / this->matrix_.diag();

	return SolverPerformance<Type>
		(
			typeName,
			this->fieldName_,
			Zero,
			Zero,
			Zero,
			true,
			false
			);
}


// ************************************************************************* //