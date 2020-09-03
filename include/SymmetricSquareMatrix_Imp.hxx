#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::SymmetricSquareMatrix<Type> tnbLib::invDecomposed
(
	const SymmetricSquareMatrix<Type>& matrix
)
{
	const label n = matrix.n();

	SymmetricSquareMatrix<Type> inv(n, Zero);

	for (label i = 0; i < n; i++)
	{
		inv(i, i) = 1.0 / matrix(i, i);

		for (label j = 0; j < i; j++)
		{
			Type sum = Zero;

			for (label k = j; k < i; k++)
			{
				sum -= matrix(i, k)*inv(k, j);
			}

			inv(i, j) = sum / matrix(i, i);
		}
	}

	SymmetricSquareMatrix<Type> result(n, Zero);

	for (label k = 0; k < n; k++)
	{
		for (label i = 0; i <= k; i++)
		{
			for (label j = 0; j <= k; j++)
			{
				result(i, j) += inv(k, i)*inv(k, j);
			}
		}
	}

	return result;
}


template<class Type>
tnbLib::SymmetricSquareMatrix<Type> tnbLib::inv
(
	const SymmetricSquareMatrix<Type>& matrix
)
{
	SymmetricSquareMatrix<Type> matrixTmp(matrix);
	LUDecompose(matrixTmp);

	return invDecomposed(matrixTmp);
}


template<class Type>
Type tnbLib::detDecomposed(const SymmetricSquareMatrix<Type>& matrix)
{
	Type diagProduct = pTraits<Type>::one;

	for (label i = 0; i < matrix.m(); i++)
	{
		diagProduct *= matrix(i, i);
	}

	return sqr(diagProduct);
}


template<class Type>
Type tnbLib::det(const SymmetricSquareMatrix<Type>& matrix)
{
	SymmetricSquareMatrix<Type> matrixTmp(matrix);
	LUDecompose(matrixTmp);

	return detDecomposed(matrixTmp);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //