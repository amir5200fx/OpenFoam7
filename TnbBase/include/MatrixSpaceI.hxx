#pragma once
#include <type_traits>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Form, class Cmpt, tnbLib::direction Mrows, tnbLib::direction Ncols>
inline tnbLib::MatrixSpace<Form, Cmpt, Mrows, Ncols>::MatrixSpace()
{}


template<class Form, class Cmpt, tnbLib::direction Mrows, tnbLib::direction Ncols>
inline tnbLib::MatrixSpace<Form, Cmpt, Mrows, Ncols>::MatrixSpace
(
	const tnbLib::zero
)
	:
	MatrixSpace::vsType(Zero)
{}


template<class Form, class Cmpt, tnbLib::direction Mrows, tnbLib::direction Ncols>
template<class Form2, class Cmpt2>
inline tnbLib::MatrixSpace<Form, Cmpt, Mrows, Ncols>::MatrixSpace
(
	const VectorSpace<Form2, Cmpt2, Mrows*Ncols>& vs
)
	:
	MatrixSpace::vsType(vs)
{}


template<class Form, class Cmpt, tnbLib::direction Mrows, tnbLib::direction Ncols>
template
<
	template<class, tnbLib::direction, tnbLib::direction> class Block2,
	tnbLib::direction BRowStart,
	tnbLib::direction BColStart
>
inline tnbLib::MatrixSpace<Form, Cmpt, Mrows, Ncols>::MatrixSpace
(
	const Block2<Form, BRowStart, BColStart>& block
)
{
	for (direction i = 0; i < Mrows; ++i)
	{
		for (direction j = 0; j < Ncols; ++j)
		{
			operator()(i, j) = block(i, j);
		}
	}
}


template<class Form, class Cmpt, tnbLib::direction Mrows, tnbLib::direction Ncols>
inline tnbLib::MatrixSpace<Form, Cmpt, Mrows, Ncols>::MatrixSpace(Istream& is)
	:
	MatrixSpace::vsType(is)
{}


template<class Form, class Cmpt, tnbLib::direction Mrows, tnbLib::direction Ncols>
template<class SubTensor, tnbLib::direction BRowStart, tnbLib::direction BColStart>
inline tnbLib::MatrixSpace<Form, Cmpt, Mrows, Ncols>::
ConstBlock<SubTensor, BRowStart, BColStart>::
ConstBlock(const msType& matrix)
	:
	matrix_(matrix)
{
	static_assert
		(
			msType::mRows >= BRowStart + mRows,
			"Rows in block > rows in matrix"
			);
	static_assert
		(
			msType::nCols >= BColStart + nCols,
			"Columns in block > columns in matrix"
			);
}


template<class Form, class Cmpt, tnbLib::direction Mrows, tnbLib::direction Ncols>
template<class SubTensor, tnbLib::direction BRowStart, tnbLib::direction BColStart>
inline tnbLib::MatrixSpace<Form, Cmpt, Mrows, Ncols>::
Block<SubTensor, BRowStart, BColStart>::
Block(msType& matrix)
	:
	matrix_(matrix)
{
	static_assert
		(
			msType::mRows >= BRowStart + mRows,
			"Rows in block > rows in matrix"
			);
	static_assert
		(
			msType::nCols >= BColStart + nCols,
			"Columns in block > columns in matrix"
			);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Form, class Cmpt, tnbLib::direction Mrows, tnbLib::direction Ncols>
template<tnbLib::direction Row, tnbLib::direction Col>
inline const Cmpt& tnbLib::MatrixSpace<Form, Cmpt, Mrows, Ncols>::elmt() const
{
	static_assert(Row < Mrows && Col < Ncols, "Address outside matrix");
	return this->v_[Row*Ncols + Col];
}


template<class Form, class Cmpt, tnbLib::direction Mrows, tnbLib::direction Ncols>
template<tnbLib::direction Row, tnbLib::direction Col>
inline Cmpt& tnbLib::MatrixSpace<Form, Cmpt, Mrows, Ncols>::elmt()
{
	static_assert(Row < Mrows && Col < Ncols, "Address outside matrix");
	return this->v_[Row*Ncols + Col];
}


template<class Form, class Cmpt, tnbLib::direction Mrows, tnbLib::direction Ncols>
inline const Cmpt& tnbLib::MatrixSpace<Form, Cmpt, Mrows, Ncols>::xx() const
{
	return elmt<0, 0>();
}


template<class Form, class Cmpt, tnbLib::direction Mrows, tnbLib::direction Ncols>
inline Cmpt& tnbLib::MatrixSpace<Form, Cmpt, Mrows, Ncols>::xx()
{
	return elmt<0, 0>();
}


template<class Form, class Cmpt, tnbLib::direction Mrows, tnbLib::direction Ncols>
inline const Cmpt& tnbLib::MatrixSpace<Form, Cmpt, Mrows, Ncols>::xy() const
{
	return elmt<0, 1>();
}


template<class Form, class Cmpt, tnbLib::direction Mrows, tnbLib::direction Ncols>
inline Cmpt& tnbLib::MatrixSpace<Form, Cmpt, Mrows, Ncols>::xy()
{
	return elmt<0, 1>();
}


template<class Form, class Cmpt, tnbLib::direction Mrows, tnbLib::direction Ncols>
inline const Cmpt& tnbLib::MatrixSpace<Form, Cmpt, Mrows, Ncols>::xz() const
{
	return elmt<0, 2>();
}


template<class Form, class Cmpt, tnbLib::direction Mrows, tnbLib::direction Ncols>
inline Cmpt& tnbLib::MatrixSpace<Form, Cmpt, Mrows, Ncols>::xz()
{
	return elmt<0, 2>();
}


template<class Form, class Cmpt, tnbLib::direction Mrows, tnbLib::direction Ncols>
inline const Cmpt& tnbLib::MatrixSpace<Form, Cmpt, Mrows, Ncols>::yx() const
{
	return elmt<1, 0>();
}


template<class Form, class Cmpt, tnbLib::direction Mrows, tnbLib::direction Ncols>
inline Cmpt& tnbLib::MatrixSpace<Form, Cmpt, Mrows, Ncols>::yx()
{
	return elmt<1, 0>();
}


template<class Form, class Cmpt, tnbLib::direction Mrows, tnbLib::direction Ncols>
inline const Cmpt& tnbLib::MatrixSpace<Form, Cmpt, Mrows, Ncols>::yy() const
{
	return elmt<1, 1>();
}


template<class Form, class Cmpt, tnbLib::direction Mrows, tnbLib::direction Ncols>
inline Cmpt& tnbLib::MatrixSpace<Form, Cmpt, Mrows, Ncols>::yy()
{
	return elmt<1, 1>();
}


template<class Form, class Cmpt, tnbLib::direction Mrows, tnbLib::direction Ncols>
inline const Cmpt& tnbLib::MatrixSpace<Form, Cmpt, Mrows, Ncols>::yz() const
{
	return elmt<1, 2>();
}


template<class Form, class Cmpt, tnbLib::direction Mrows, tnbLib::direction Ncols>
inline Cmpt& tnbLib::MatrixSpace<Form, Cmpt, Mrows, Ncols>::yz()
{
	return elmt<1, 2>();
}


template<class Form, class Cmpt, tnbLib::direction Mrows, tnbLib::direction Ncols>
inline const Cmpt& tnbLib::MatrixSpace<Form, Cmpt, Mrows, Ncols>::zx() const
{
	return elmt<2, 0>();
}


template<class Form, class Cmpt, tnbLib::direction Mrows, tnbLib::direction Ncols>
inline Cmpt& tnbLib::MatrixSpace<Form, Cmpt, Mrows, Ncols>::zx()
{
	return elmt<2, 0>();
}


template<class Form, class Cmpt, tnbLib::direction Mrows, tnbLib::direction Ncols>
inline const Cmpt& tnbLib::MatrixSpace<Form, Cmpt, Mrows, Ncols>::zy() const
{
	return elmt<2, 1>();
}


template<class Form, class Cmpt, tnbLib::direction Mrows, tnbLib::direction Ncols>
inline Cmpt& tnbLib::MatrixSpace<Form, Cmpt, Mrows, Ncols>::zy()
{
	return elmt<2, 1>();
}


template<class Form, class Cmpt, tnbLib::direction Mrows, tnbLib::direction Ncols>
inline const Cmpt& tnbLib::MatrixSpace<Form, Cmpt, Mrows, Ncols>::zz() const
{
	return elmt<2, 2>();
}

template<class Form, class Cmpt, tnbLib::direction Mrows, tnbLib::direction Ncols>
inline Cmpt& tnbLib::MatrixSpace<Form, Cmpt, Mrows, Ncols>::zz()
{
	return elmt<2, 2>();
}

template<class Form, class Cmpt, tnbLib::direction Mrows, tnbLib::direction Ncols>
inline tnbLib::MatrixSpace<Form, Cmpt, Mrows, Ncols>
tnbLib::MatrixSpace<Form, Cmpt, Mrows, Ncols>::identity()
{
	static_assert(Mrows == Ncols, "Matrix is not square");
	msType result(Zero);

	for (direction i = 0; i < Ncols; ++i)
	{
		result(i, i) = 1;
	}

	return result;
}


template<class Form, class Cmpt, tnbLib::direction Mrows, tnbLib::direction Ncols>
inline typename tnbLib::typeOfTranspose<Cmpt, Form>::type
tnbLib::MatrixSpace<Form, Cmpt, Mrows, Ncols>::T() const
{
	typename typeOfTranspose<Cmpt, Form>::type result;

	for (direction i = 0; i < Mrows; ++i)
	{
		for (direction j = 0; j < Ncols; ++j)
		{
			result(j, i) = operator()(i, j);
		}
	}

	return result;
}


template<class Form, class Cmpt, tnbLib::direction Mrows, tnbLib::direction Ncols>
template
<
	class SubTensor,
	tnbLib::direction BRowStart,
	tnbLib::direction BColStart
>
inline typename tnbLib::MatrixSpace<Form, Cmpt, Mrows, Ncols>::template
ConstBlock<SubTensor, BRowStart, BColStart>
tnbLib::MatrixSpace<Form, Cmpt, Mrows, Ncols>::block() const
{
	return *this;
}


template<class Form, class Cmpt, tnbLib::direction Mrows, tnbLib::direction Ncols>
template
<
	class SubTensor,
	tnbLib::direction BRowStart,
	tnbLib::direction BColStart
>
inline
typename tnbLib::MatrixSpace<Form, Cmpt, Mrows, Ncols>::template
Block<SubTensor, BRowStart, BColStart>
tnbLib::MatrixSpace<Form, Cmpt, Mrows, Ncols>::block()
{
	return *this;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class Form, class Cmpt, tnbLib::direction Mrows, tnbLib::direction Ncols>
inline const Cmpt& tnbLib::MatrixSpace<Form, Cmpt, Mrows, Ncols>::operator()
(
	const direction& i,
	const direction& j
	) const
{
#ifdef FULLDEBUG
	if (i > Mrows - 1 || j > Ncols - 1)
	{
		FatalErrorInFunction
			<< "indices out of range"
			<< abort(FatalError);
	}
#endif

	return this->v_[i*Ncols + j];
}


template<class Form, class Cmpt, tnbLib::direction Mrows, tnbLib::direction Ncols>
inline Cmpt& tnbLib::MatrixSpace<Form, Cmpt, Mrows, Ncols>::operator()
(
	const direction& i,
	const direction& j
	)
{
#ifdef FULLDEBUG
	if (i > Mrows - 1 || j > Ncols - 1)
	{
		FatalErrorInFunction
			<< "indices out of range"
			<< abort(FatalError);
	}
#endif

	return this->v_[i*Ncols + j];
}


template<class Form, class Cmpt, tnbLib::direction Mrows, tnbLib::direction Ncols>
template<class SubTensor, tnbLib::direction BRowStart, tnbLib::direction BColStart>
inline SubTensor
tnbLib::MatrixSpace<Form, Cmpt, Mrows, Ncols>::
ConstBlock<SubTensor, BRowStart, BColStart>::
operator()() const
{
	return *this;
}


template<class Form, class Cmpt, tnbLib::direction Mrows, tnbLib::direction Ncols>
template<class SubTensor, tnbLib::direction BRowStart, tnbLib::direction BColStart>
inline const Cmpt&
tnbLib::MatrixSpace<Form, Cmpt, Mrows, Ncols>::
ConstBlock<SubTensor, BRowStart, BColStart>::
operator()(const direction i, const direction j) const
{
	return matrix_(BRowStart + i, BColStart + j);
}


template<class Form, class Cmpt, tnbLib::direction Mrows, tnbLib::direction Ncols>
template<class SubTensor, tnbLib::direction BRowStart, tnbLib::direction BColStart>
inline SubTensor
tnbLib::MatrixSpace<Form, Cmpt, Mrows, Ncols>::
Block<SubTensor, BRowStart, BColStart>::
operator()() const
{
	SubTensor st;

	for (direction i = 0; i < SubTensor::mRows; ++i)
	{
		for (direction j = 0; j < SubTensor::nCols; ++j)
		{
			st[i*SubTensor::nCols + j] = operator()(i, j);
		}
	}

	return st;
}


template<class Form, class Cmpt, tnbLib::direction Mrows, tnbLib::direction Ncols>
template<class SubTensor, tnbLib::direction BRowStart, tnbLib::direction BColStart>
inline const Cmpt&
tnbLib::MatrixSpace<Form, Cmpt, Mrows, Ncols>::
Block<SubTensor, BRowStart, BColStart>::
operator()(const direction i, const direction j) const
{
	return matrix_(BRowStart + i, BColStart + j);
}


template<class Form, class Cmpt, tnbLib::direction Mrows, tnbLib::direction Ncols>
template<class SubTensor, tnbLib::direction BRowStart, tnbLib::direction BColStart>
inline Cmpt&
tnbLib::MatrixSpace<Form, Cmpt, Mrows, Ncols>::
Block<SubTensor, BRowStart, BColStart>::
operator()(const direction i, const direction j)
{
	return matrix_(BRowStart + i, BColStart + j);
}


template<class Form, class Cmpt, tnbLib::direction Mrows, tnbLib::direction Ncols>
inline void tnbLib::MatrixSpace<Form, Cmpt, Mrows, Ncols>::operator=
(
	const tnbLib::zero
	)
{
	MatrixSpace::vsType::operator=(Zero);
}


template<class Form, class Cmpt, tnbLib::direction Mrows, tnbLib::direction Ncols>
template<class Form2>
inline void tnbLib::MatrixSpace<Form, Cmpt, Mrows, Ncols>::operator&=
(
	const MatrixSpace<Form, Cmpt, Ncols, Ncols>& matrix
	)
{
	*this = *this & matrix;
}


template<class Form, class Cmpt, tnbLib::direction Mrows, tnbLib::direction Ncols>
template
<
	template<class, tnbLib::direction, tnbLib::direction> class Block2,
	tnbLib::direction BRowStart,
	tnbLib::direction BColStart
>
inline void tnbLib::MatrixSpace<Form, Cmpt, Mrows, Ncols>::operator=
(
	const Block2<Form, BRowStart, BColStart>& block
	)
{
	for (direction i = 0; i < Mrows; ++i)
	{
		for (direction j = 0; j < Ncols; ++j)
		{
			operator()(i, j) = block(i, j);
		}
	}
}


template<class Form, class Cmpt, tnbLib::direction Mrows, tnbLib::direction Ncols>
template<class SubTensor, tnbLib::direction BRowStart, tnbLib::direction BColStart>
template<class Form2>
inline void
tnbLib::MatrixSpace<Form, Cmpt, Mrows, Ncols>::
Block<SubTensor, BRowStart, BColStart>::
operator=
(
	const MatrixSpace<Form2, Cmpt, SubTensor::mRows, SubTensor::nCols>& matrix
	)
{
	for (direction i = 0; i < mRows; ++i)
	{
		for (direction j = 0; j < nCols; ++j)
		{
			operator()(i, j) = matrix(i, j);
		}
	}
}


template<class Form, class Cmpt, tnbLib::direction Mrows, tnbLib::direction Ncols>
template<class SubTensor, tnbLib::direction BRowStart, tnbLib::direction BColStart>
template<class VSForm>
inline void
tnbLib::MatrixSpace<Form, Cmpt, Mrows, Ncols>::
Block<SubTensor, BRowStart, BColStart>::
operator=
(
	const VectorSpace<VSForm, Cmpt, SubTensor::mRows>& v
	)
{
	static_assert(nCols == 1, "Matrix must have a single column");

	for (direction i = 0; i < SubTensor::mRows; ++i)
	{
		operator()(i, 0) = v[i];
	}
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * Friend Functions  * * * * * * * * * * * * * //

	template<class Form, class Cmpt, direction Mrows, direction Ncols>
	inline typename typeOfTranspose<Cmpt, Form>::type T
	(
		const MatrixSpace<Form, Cmpt, Ncols, Mrows>& matrix
	)
	{
		return matrix.T();
	}


	template<class Form, class Cmpt, direction Ncmpts>
	inline typename typeOfTranspose<Cmpt, Form>::type T
	(
		const VectorSpace<Form, Cmpt, Ncmpts>& v
	)
	{
		typename typeOfTranspose<Cmpt, Form>::type result;

		for (direction i = 0; i < Ncmpts; ++i)
		{
			result[i] = v[i];
		}

		return result;
	}


	// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

	template
		<
		class Form1,
		class Form2,
		class Cmpt,
		direction Mrows1,
		direction Ncols1,
		direction Mrows2,
		direction Ncols2
		>
		inline typename typeOfInnerProduct<Cmpt, Form1, Form2>::type operator&
		(
			const MatrixSpace<Form1, Cmpt, Mrows1, Ncols1>& matrix1,
			const MatrixSpace<Form2, Cmpt, Mrows2, Ncols2>& matrix2
			)
	{
		static_assert
			(
				Ncols1 == Mrows2,
				"Number of columns in matrix 1 != number of rows in matrix 2"
				);

		typename typeOfInnerProduct<Cmpt, Form1, Form2>::type result(Zero);

		for (direction i = 0; i < Mrows1; ++i)
		{
			for (direction j = 0; j < Ncols2; ++j)
			{
				for (direction k = 0; k < Mrows2; k++)
				{
					result(i, j) += matrix1(i, k)*matrix2(k, j);
				}
			}
		}

		return result;
	}


	template<class Form, class VSForm, class Cmpt, direction Mrows, direction Ncols>
	inline typename typeOfInnerProduct<Cmpt, Form, VSForm>::type operator&
		(
			const MatrixSpace<Form, Cmpt, Mrows, Ncols>& matrix,
			const VectorSpace<VSForm, Cmpt, Ncols>& v
			)
	{
		typename typeOfInnerProduct<Cmpt, Form, VSForm>::type result(Zero);

		for (direction i = 0; i < Mrows; ++i)
		{
			for (direction j = 0; j < Ncols; ++j)
			{
				result[i] += matrix(i, j)*v[j];
			}
		}

		return result;
	}


	template
		<
		class Form1,
		class Form2,
		class Cmpt,
		direction Ncmpts1,
		direction Ncmpts2
		>
		inline typename typeOfOuterProduct<Cmpt, Form1, Form2>::type operator*
		(
			const VectorSpace<Form1, Cmpt, Ncmpts1>& v1,
			const VectorSpace<Form2, Cmpt, Ncmpts2>& v2
			)
	{
		typename typeOfOuterProduct<Cmpt, Form1, Form2>::type result;

		for (direction i = 0; i < Ncmpts1; ++i)
		{
			for (direction j = 0; j < Ncmpts2; ++j)
			{
				result(i, j) = v1[i] * v2[j];
			}
		}

		return result;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //