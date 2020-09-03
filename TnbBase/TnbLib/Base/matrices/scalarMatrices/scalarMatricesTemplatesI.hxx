#pragma once
#include <Swap.hxx>
#include <ListOps.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::solve
(
	scalarSquareMatrix& tmpMatrix,
	List<Type>& sourceSol
)
{
	label m = tmpMatrix.m();

	// Elimination
	for (label i = 0; i < m; i++)
	{
		label iMax = i;
		scalar largestCoeff = mag(tmpMatrix(iMax, i));

		// Swap elements around to find a good pivot
		for (label j = i + 1; j < m; j++)
		{
			if (mag(tmpMatrix(j, i)) > largestCoeff)
			{
				iMax = j;
				largestCoeff = mag(tmpMatrix(iMax, i));
			}
		}

		if (i != iMax)
		{
			for (label k = i; k < m; k++)
			{
				Swap(tmpMatrix(i, k), tmpMatrix(iMax, k));
			}
			Swap(sourceSol[i], sourceSol[iMax]);
		}

		// Check that the system of equations isn't singular
		if (mag(tmpMatrix(i, i)) < 1e-20)
		{
			FatalErrorInFunction
				<< "Singular Matrix"
				<< exit(FatalError);
		}

		// Reduce to upper triangular form
		for (label j = i + 1; j < m; j++)
		{
			sourceSol[j] -= sourceSol[i] * (tmpMatrix(j, i) / tmpMatrix(i, i));

			for (label k = m - 1; k >= i; k--)
			{
				tmpMatrix(j, k) -=
					tmpMatrix(i, k)*tmpMatrix(j, i) / tmpMatrix(i, i);
			}
		}
	}

	// Back-substitution
	for (label j = m - 1; j >= 0; j--)
	{
		Type ntempvec = Zero;

		for (label k = j + 1; k < m; k++)
		{
			ntempvec += tmpMatrix(j, k)*sourceSol[k];
		}

		sourceSol[j] = (sourceSol[j] - ntempvec) / tmpMatrix(j, j);
	}
}


template<class Type>
void tnbLib::solve
(
	List<Type>& psi,
	const scalarSquareMatrix& matrix,
	const List<Type>& source
)
{
	scalarSquareMatrix tmpMatrix = matrix;
	psi = source;
	solve(tmpMatrix, psi);
}


template<class Type>
void tnbLib::LUBacksubstitute
(
	const scalarSquareMatrix& luMatrix,
	const labelList& pivotIndices,
	List<Type>& sourceSol
)
{
	label m = luMatrix.m();

	label ii = 0;

	for (label i = 0; i < m; i++)
	{
		label ip = pivotIndices[i];
		Type sum = sourceSol[ip];
		sourceSol[ip] = sourceSol[i];
		const scalar* __restrict luMatrixi = luMatrix[i];

		if (ii != 0)
		{
			for (label j = ii - 1; j < i; j++)
			{
				sum -= luMatrixi[j] * sourceSol[j];
			}
		}
		else if (sum != pTraits<Type>::zero)
		{
			ii = i + 1;
		}

		sourceSol[i] = sum;
	}

	for (label i = m - 1; i >= 0; i--)
	{
		Type sum = sourceSol[i];
		const scalar* __restrict luMatrixi = luMatrix[i];

		for (label j = i + 1; j < m; j++)
		{
			sum -= luMatrixi[j] * sourceSol[j];
		}

		sourceSol[i] = sum / luMatrixi[i];
	}
}


template<class Type>
void tnbLib::LUBacksubstitute
(
	const scalarSymmetricSquareMatrix& luMatrix,
	List<Type>& sourceSol
)
{
	label m = luMatrix.m();

	label ii = 0;

	for (label i = 0; i < m; i++)
	{
		Type sum = sourceSol[i];
		const scalar* __restrict luMatrixi = luMatrix[i];

		if (ii != 0)
		{
			for (label j = ii - 1; j < i; j++)
			{
				sum -= luMatrixi[j] * sourceSol[j];
			}
		}
		else if (sum != pTraits<Type>::zero)
		{
			ii = i + 1;
		}

		sourceSol[i] = sum / luMatrixi[i];
	}

	for (label i = m - 1; i >= 0; i--)
	{
		Type sum = sourceSol[i];
		const scalar* __restrict luMatrixi = luMatrix[i];

		for (label j = i + 1; j < m; j++)
		{
			sum -= luMatrixi[j] * sourceSol[j];
		}

		sourceSol[i] = sum / luMatrixi[i];
	}
}


template<class Type>
void tnbLib::LUsolve
(
	scalarSquareMatrix& matrix,
	List<Type>& sourceSol
)
{
	labelList pivotIndices(matrix.m());
	LUDecompose(matrix, pivotIndices);
	LUBacksubstitute(matrix, pivotIndices, sourceSol);
}


template<class Type>
void tnbLib::LUsolve
(
	scalarSymmetricSquareMatrix& matrix,
	List<Type>& sourceSol
)
{
	LUDecompose(matrix);
	LUBacksubstitute(matrix, sourceSol);
}


template<class Form, class Type>
void tnbLib::multiply
(
	Matrix<Form, Type>& ans,         // value changed in return
	const Matrix<Form, Type>& A,
	const Matrix<Form, Type>& B
)
{
	if (A.n() != B.m())
	{
		FatalErrorInFunction
			<< "A and B must have identical inner dimensions but A.n = "
			<< A.n() << " and B.m = " << B.m()
			<< abort(FatalError);
	}

	ans = Matrix<Form, Type>(A.m(), B.n(), scalar(0));

	for (label i = 0; i < A.m(); i++)
	{
		for (label j = 0; j < B.n(); j++)
		{
			for (label l = 0; l < B.m(); l++)
			{
				ans(i, j) += A(i, l)*B(l, j);
			}
		}
	}
}


// ************************************************************************* //