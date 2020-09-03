#pragma once
#include <labelList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::scalar tnbLib::detDecomposed
(
	const SquareMatrix<Type>& matrix,
	const label sign
)
{
	Type diagProduct = pTraits<Type>::one;

	for (label i = 0; i < matrix.m(); i++)
	{
		diagProduct *= matrix(i, i);
	}

	return sign * diagProduct;
}


template<class Type>
tnbLib::scalar tnbLib::det(const SquareMatrix<Type>& matrix)
{
	SquareMatrix<Type> matrixTmp = matrix;

	labelList pivotIndices(matrix.m());
	label sign;
	LUDecompose(matrixTmp, pivotIndices, sign);

	return detDecomposed(matrixTmp, sign);
}


template<class Type>
tnbLib::scalar tnbLib::det(SquareMatrix<Type>& matrix)
{
	labelList pivotIndices(matrix.m());
	label sign;
	LUDecompose(matrix, pivotIndices, sign);

	return detDecomposed(matrix, sign);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //