#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
inline tnbLib::SquareMatrix<Type>::SquareMatrix()
	:
	Matrix<SquareMatrix<Type>, Type>()
{}


template<class Type>
inline tnbLib::SquareMatrix<Type>::SquareMatrix(const label n)
	:
	Matrix<SquareMatrix<Type>, Type>(n, n)
{}


template<class Type>
template<class MatrixType>
inline tnbLib::SquareMatrix<Type>::SquareMatrix
(
	const ConstMatrixBlock<MatrixType>& block
)
	:
	Matrix<SquareMatrix<Type>, Type>(block)
{}


template<class Type>
template<class MatrixType>
inline tnbLib::SquareMatrix<Type>::SquareMatrix
(
	const MatrixBlock<MatrixType>& block
)
	:
	Matrix<SquareMatrix<Type>, Type>(block)
{}


template<class Type>
inline tnbLib::SquareMatrix<Type>::SquareMatrix
(
	const label n,
	const zero
)
	:
	Matrix<SquareMatrix<Type>, Type>(n, n, Zero)
{}


template<class Type>
inline tnbLib::SquareMatrix<Type>::SquareMatrix
(
	const label m,
	const label n,
	const zero
)
	:
	Matrix<SquareMatrix<Type>, Type>(m, n, Zero)
{
	if (m != n)
	{
		FatalErrorInFunction
			<< "Attempt to construct a square matrix "
			<< m << " x " << n << nl
			<< abort(FatalError);
	}
}


template<class Type>
inline tnbLib::SquareMatrix<Type>::SquareMatrix
(
	const label n,
	const Identity<Type>
)
	:
	Matrix<SquareMatrix<Type>, Type>(n, n, Zero)
{
	for (label i = 0; i < n; i++)
	{
		this->operator()(i, i) = Type(I);
	}
}


template<class Type>
inline tnbLib::SquareMatrix<Type>::SquareMatrix
(
	const label n,
	const Type& t
)
	:
	Matrix<SquareMatrix<Type>, Type>(n, n, t)
{}


template<class Type>
inline tnbLib::SquareMatrix<Type>::SquareMatrix
(
	const RectangularMatrix<Type>& RM
)
	:
	Matrix<SquareMatrix<Type>, Type>(RM)
{
	if (this->m() != this->n())
	{
		FatalErrorInFunction
			<< "Attempt to construct a square matrix from a rectangular matrix "
			<< this->m() << " x " << this->n() << nl
			<< abort(FatalError);
	}
}


template<class Type>
inline tnbLib::SquareMatrix<Type>::SquareMatrix(Istream& is)
	:
	Matrix<SquareMatrix<Type>, Type>(is)
{}


template<class Type>
inline tnbLib::autoPtr<tnbLib::SquareMatrix<Type>>
tnbLib::SquareMatrix<Type>::clone() const
{
	return autoPtr<SquareMatrix<Type>>(new SquareMatrix<Type>(*this));
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
inline void tnbLib::SquareMatrix<Type>::setSize(const label m)
{
	Matrix<SquareMatrix<Type>, Type>::setSize(m, m);
}


template<class Type>
inline void tnbLib::SquareMatrix<Type>::shallowResize(const label m)
{
	Matrix<SquareMatrix<Type>, Type>::shallowResize(m, m);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::SquareMatrix<Type>::operator=(const zero)
{
	Matrix<SquareMatrix<Type>, Type>::operator=(Zero);
}


template<class Type>
void tnbLib::SquareMatrix<Type>::operator=(const Identity<Type>)
{
	Matrix<SquareMatrix<Type>, Type>::operator=(Zero);
	for (label i = 0; i < this->n(); i++)
	{
		this->operator()(i, i) = Type(I);
	}
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Friend Functions  * * * * * * * * * * * * * //

	template<class Type>
	inline tnbLib::SquareMatrix<Type> symmOuter
	(
		const Field<Type>& f1,
		const Field<Type>& f2
	)
	{
		SquareMatrix<Type> f1f2T(f1.size());

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