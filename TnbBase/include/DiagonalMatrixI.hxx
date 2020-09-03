#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type>
inline tnbLib::DiagonalMatrix<Type>::DiagonalMatrix()
	:
	List<Type>()
{}


template<class Type>
template<class Form>
tnbLib::DiagonalMatrix<Type>::DiagonalMatrix(const Matrix<Form, Type>& a)
	:
	List<Type>(min(a.m(), a.n()))
{
	forAll(*this, i)
	{
		this->operator[](i) = a(i, i);
	}
}


template<class Type>
tnbLib::DiagonalMatrix<Type>::DiagonalMatrix(const label size)
	:
	List<Type>(size)
{}


template<class Type>
tnbLib::DiagonalMatrix<Type>::DiagonalMatrix(const label size, const Type& val)
	:
	List<Type>(size, val)
{}


template<class Type>
tnbLib::DiagonalMatrix<Type>& tnbLib::DiagonalMatrix<Type>::invert()
{
	forAll(*this, i)
	{
		Type x = this->operator[](i);
		if (mag(x) < vSmall)
		{
			this->operator[](i) = Type(0);
		}
		else
		{
			this->operator[](i) = Type(1) / x;
		}
	}

	return this;
}


template<class Type>
tnbLib::DiagonalMatrix<Type> tnbLib::inv(const DiagonalMatrix<Type>& A)
{
	DiagonalMatrix<Type> Ainv = A;

	forAll(A, i)
	{
		Type x = A[i];
		if (mag(x) < vSmall)
		{
			Ainv[i] = Type(0);
		}
		else
		{
			Ainv[i] = Type(1) / x;
		}
	}

	return Ainv;
}


// ************************************************************************* //