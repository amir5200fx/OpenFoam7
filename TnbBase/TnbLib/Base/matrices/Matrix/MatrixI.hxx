#pragma once
#include <MatrixBlock.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Form, class Type>
inline tnbLib::Matrix<Form, Type>::Matrix()
	:
	mRows_(0),
	nCols_(0),
	v_(nullptr)
{}


template<class Form, class Type>
inline tnbLib::autoPtr<tnbLib::Matrix<Form, Type>> tnbLib::Matrix<Form, Type>::
clone() const
{
	return autoPtr<Matrix<Form, Type>>(new Matrix<Form, Type>(*this));
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Form, class Type>
inline const tnbLib::Matrix<Form, Type>& tnbLib::Matrix<Form, Type>::null()
{
	return NullObjectRef<Matrix<Form, Type>>();
}


template<class Form, class Type>
inline tnbLib::label tnbLib::Matrix<Form, Type>::m() const
{
	return mRows_;
}


template<class Form, class Type>
inline tnbLib::label tnbLib::Matrix<Form, Type>::n() const
{
	return nCols_;
}


template<class Form, class Type>
inline tnbLib::label tnbLib::Matrix<Form, Type>::size() const
{
	return mRows_ * nCols_;
}


template<class Form, class Type>
inline void tnbLib::Matrix<Form, Type>::checki(const label i) const
{
#ifdef FULLDEBUG
	if (!mRows_ || !nCols_)
	{
		FatalErrorInFunction
			<< "Attempt to access element from empty matrix"
			<< abort(FatalError);
	}
	else if (i < 0 || i >= mRows_)
	{
		FatalErrorInFunction
			<< "Index " << i << " out of range 0 ... " << mRows_ - 1
			<< abort(FatalError);
	}
#endif
}


template<class Form, class Type>
inline void tnbLib::Matrix<Form, Type>::checkj(const label j) const
{
#ifdef FULLDEBUG
	if (!mRows_ || !nCols_)
	{
		FatalErrorInFunction
			<< "Attempt to access element from empty matrix"
			<< abort(FatalError);
	}
	else if (j < 0 || j >= nCols_)
	{
		FatalErrorInFunction
			<< "index " << j << " out of range 0 ... " << nCols_ - 1
			<< abort(FatalError);
	}
#endif
}


template<class Form, class Type>
inline const Type* tnbLib::Matrix<Form, Type>::v() const
{
	return v_;
}


template<class Form, class Type>
inline Type* tnbLib::Matrix<Form, Type>::v()
{
	return v_;
}


template<class Form, class Type>
inline tnbLib::ConstMatrixBlock<tnbLib::Matrix<Form, Type>>
tnbLib::Matrix<Form, Type>::block
(
	const label m,
	const label n,
	const label mStart,
	const label nStart
) const
{
	return ConstMatrixBlock<mType>
		(
			*this,
			m,
			n,
			mStart,
			nStart
			);
}


template<class Form, class Type>
template<class VectorSpace>
inline tnbLib::ConstMatrixBlock<tnbLib::Matrix<Form, Type>>
tnbLib::Matrix<Form, Type>::block
(
	const label mStart,
	const label nStart
) const
{
	return ConstMatrixBlock<mType>
		(
			*this,
			VectorSpace::mRows,
			VectorSpace::nCols,
			mStart,
			nStart
			);
}


template<class Form, class Type>
inline tnbLib::ConstMatrixBlock<tnbLib::Matrix<Form, Type>>
tnbLib::Matrix<Form, Type>::col
(
	const label m,
	const label mStart
) const
{
	return ConstMatrixBlock<mType>
		(
			*this,
			m,
			1,
			mStart,
			0
			);
}


template<class Form, class Type>
inline tnbLib::ConstMatrixBlock<tnbLib::Matrix<Form, Type>>
tnbLib::Matrix<Form, Type>::col
(
	const label m,
	const label mStart,
	const label nStart
) const
{
	return ConstMatrixBlock<mType>
		(
			*this,
			m,
			1,
			mStart,
			nStart
			);
}


template<class Form, class Type>
inline tnbLib::MatrixBlock<tnbLib::Matrix<Form, Type>>
tnbLib::Matrix<Form, Type>::block
(
	const label m,
	const label n,
	const label mStart,
	const label nStart
)
{
	return MatrixBlock<mType>
		(
			*this,
			m,
			n,
			mStart,
			nStart
			);
}


template<class Form, class Type>
template<class VectorSpace>
inline tnbLib::MatrixBlock<tnbLib::Matrix<Form, Type>>
tnbLib::Matrix<Form, Type>::block(const label mStart, const label nStart)
{
	return MatrixBlock<mType>
		(
			*this,
			VectorSpace::mRows,
			VectorSpace::nCols,
			mStart,
			nStart
			);
}


template<class Form, class Type>
inline tnbLib::MatrixBlock<tnbLib::Matrix<Form, Type>>
tnbLib::Matrix<Form, Type>::col(const label m, const label mStart)
{
	return MatrixBlock<mType>
		(
			*this,
			m,
			1,
			mStart,
			0
			);
}


template<class Form, class Type>
inline tnbLib::MatrixBlock<tnbLib::Matrix<Form, Type>>
tnbLib::Matrix<Form, Type>::col
(
	const label m,
	const label mStart,
	const label nStart
)
{
	return MatrixBlock<mType>
		(
			*this,
			m,
			1,
			mStart,
			nStart
			);
}


template<class Form, class Type>
void tnbLib::Matrix<Form, Type>::shallowResize(const label m, const label n)
{
	mRows_ = m;
	nCols_ = n;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class Form, class Type>
inline const Type& tnbLib::Matrix<Form, Type>::operator()
(
	const label i,
	const label j
	) const
{
	checki(i);
	checkj(j);
	return v_[i*nCols_ + j];
}


template<class Form, class Type>
inline Type& tnbLib::Matrix<Form, Type>::operator()
(
	const label i,
	const label j
	)
{
	checki(i);
	checkj(j);
	return v_[i*nCols_ + j];
}


template<class Form, class Type>
inline const Type* tnbLib::Matrix<Form, Type>::operator[](const label i) const
{
	checki(i);
	return v_ + i * nCols_;
}


template<class Form, class Type>
inline Type* tnbLib::Matrix<Form, Type>::operator[](const label i)
{
	checki(i);
	return v_ + i * nCols_;
}


// ************************************************************************* //