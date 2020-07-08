#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
inline tnbLib::RectangularMatrix<Type>::RectangularMatrix()
	:
	Matrix<RectangularMatrix<Type>, Type>()
{}


template<class Type>
inline tnbLib::RectangularMatrix<Type>::RectangularMatrix
(
	const label m,
	const label n
)
	:
	Matrix<RectangularMatrix<Type>, Type>(m, n)
{}


template<class Type>
template<class MatrixType>
inline tnbLib::RectangularMatrix<Type>::RectangularMatrix
(
	const ConstMatrixBlock<MatrixType>& block
)
	:
	Matrix<RectangularMatrix<Type>, Type>(block)
{}


template<class Type>
template<class MatrixType>
inline tnbLib::RectangularMatrix<Type>::RectangularMatrix
(
	const MatrixBlock<MatrixType>& block
)
	:
	Matrix<RectangularMatrix<Type>, Type>(block)
{}


template<class Type>
inline tnbLib::RectangularMatrix<Type>::RectangularMatrix
(
	const label m,
	const label n,
	const zero
)
	:
	Matrix<RectangularMatrix<Type>, Type>(m, n, Zero)
{}


template<class Type>
inline tnbLib::RectangularMatrix<Type>::RectangularMatrix
(
	const label m,
	const label n,
	const Type& t
)
	:
	Matrix<RectangularMatrix<Type>, Type>(m, n, t)
{}


template<class Type>
inline tnbLib::RectangularMatrix<Type>::RectangularMatrix
(
	const SquareMatrix<Type>& SM
)
	:
	Matrix<RectangularMatrix<Type>, Type>(SM)
{}


template<class Type>
inline tnbLib::RectangularMatrix<Type>::RectangularMatrix(Istream& is)
	:
	Matrix<RectangularMatrix<Type>, Type>(is)
{}


template<class Type>
inline tnbLib::autoPtr<tnbLib::RectangularMatrix<Type>>
tnbLib::RectangularMatrix<Type>::clone() const
{
	return autoPtr<RectangularMatrix<Type>>
		(
			new RectangularMatrix<Type>(*this)
			);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::RectangularMatrix<Type>::operator=(const zero)
{
	Matrix<RectangularMatrix<Type>, Type>::operator=(Zero);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Friend Functions  * * * * * * * * * * * * * //

	template<class Type>
	inline tnbLib::RectangularMatrix<Type> outer
	(
		const Field<Type>& f1,
		const Field<Type>& f2
	)
	{
		RectangularMatrix<Type> f1f2T(f1.size(), f2.size());

		for (label i = 0; i < f1f2T.m(); i++)
		{
			for (label j = 0; j < f1f2T.n(); j++)
			{
				f1f2T(i, j) = f1[i] * f2[j];
			}
		}

		return f1f2T;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //