#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::LLTMatrix<Type>::LLTMatrix()
{}


template<class Type>
tnbLib::LLTMatrix<Type>::LLTMatrix(const SquareMatrix<Type>& M)
{
	decompose(M);
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

template<class Type>
void tnbLib::LLTMatrix<Type>::decompose(const SquareMatrix<Type>& M)
{
	SquareMatrix<Type>& LLT = *this;

	// Initialize the LLT decomposition matrix to M
	LLT = M;

	const label m = LLT.m();

	for (label i = 0; i < m; i++)
	{
		for (label j = 0; j < m; j++)
		{
			if (j > i)
			{
				LLT(i, j) = Zero;
				continue;
			}

			Type sum = LLT(i, j);

			for (label k = 0; k < j; k++)
			{
				sum -= LLT(i, k)*LLT(j, k);
			}

			if (i > j)
			{
				LLT(i, j) = sum / LLT(j, j);
			}
			else if (sum > 0)
			{
				LLT(i, i) = sqrt(sum);
			}
			else
			{
				FatalErrorInFunction
					<< "Cholesky decomposition failed, "
					"matrix is not symmetric positive definite"
					<< abort(FatalError);
			}
		}
	}
}


template<class Type>
void tnbLib::LLTMatrix<Type>::solve
(
	Field<Type>& x,
	const Field<Type>& source
) const
{
	// If x and source are different initialize x = source
	if (&x != &source)
	{
		x = source;
	}

	const SquareMatrix<Type>& LLT = *this;
	const label m = LLT.m();

	for (label i = 0; i < m; i++)
	{
		Type sum = source[i];

		for (label j = 0; j < i; j++)
		{
			sum = sum - LLT(i, j)*x[j];
		}

		x[i] = sum / LLT(i, i);
	}

	for (int i = m - 1; i >= 0; i--)
	{
		Type sum = x[i];

		for (label j = i + 1; j < m; j++)
		{
			sum = sum - LLT(j, i)*x[j];
		}

		x[i] = sum / LLT(i, i);
	}

}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>> tnbLib::LLTMatrix<Type>::solve
(
	const Field<Type>& source
) const
{
	tmp<Field<Type>> tx(new Field<Type>(this->m()));
	Field<Type>& x = tx.ref();

	solve(x, source);

	return tx;
}


// ************************************************************************* //