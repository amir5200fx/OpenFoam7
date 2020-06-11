#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
inline tnbLib::SymmetricSquareMatrix<Type>::SymmetricSquareMatrix()
	:
	Matrix<SymmetricSquareMatrix<Type>, Type>()
{}


template<class Type>
inline tnbLib::SymmetricSquareMatrix<Type>::SymmetricSquareMatrix(const label n)
	:
	Matrix<SymmetricSquareMatrix<Type>, Type>(n, n)
{}


template<class Type>
inline tnbLib::SymmetricSquareMatrix<Type>::SymmetricSquareMatrix
(
	const label n,
	const zero
)
	:
	Matrix<SymmetricSquareMatrix<Type>, Type>(n, n, Zero)
{}


template<class Type>
inline tnbLib::SymmetricSquareMatrix<Type>::SymmetricSquareMatrix
(
	const label n,
	const Identity<Type>
)
	:
	Matrix<SymmetricSquareMatrix<Type>, Type>(n, n, Zero)
{
	for (label i = 0; i < n; i++)
	{
		this->operator()(i, i) = pTraits<Type>::one;
	}
}


template<class Type>
inline tnbLib::SymmetricSquareMatrix<Type>::SymmetricSquareMatrix
(
	const label n,
	const Type& t
)
	:
	Matrix<SymmetricSquareMatrix<Type>, Type>(n, n, t)
{}


template<class Type>
inline tnbLib::SymmetricSquareMatrix<Type>::SymmetricSquareMatrix(Istream& is)
	:
	Matrix<SymmetricSquareMatrix<Type>, Type>(is)
{}


template<class Type>
inline tnbLib::autoPtr<tnbLib::SymmetricSquareMatrix<Type>>
tnbLib::SymmetricSquareMatrix<Type>::clone() const
{
	return autoPtr<SymmetricSquareMatrix<Type>>
		(
			new SymmetricSquareMatrix<Type>(*this)
			);
}


// ************************************************************************* //