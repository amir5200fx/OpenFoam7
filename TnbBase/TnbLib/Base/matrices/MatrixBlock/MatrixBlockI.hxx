#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class MatrixType>
tnbLib::ConstMatrixBlock<MatrixType>::ConstMatrixBlock
(
	const MatrixType& matrix,
	const label m,
	const label n,
	const label mStart,
	const label nStart
)
	:
	matrix_(matrix),
	mRows_(m),
	nCols_(n),
	rowStart_(mStart),
	colStart_(nStart)
{
#ifdef FULLDEBUG
	if
		(
			rowStart_ + mRows_ > matrix.m()
			|| colStart_ + nCols_ > matrix.n()
			)
	{
		FatalErrorInFunction
			<< "Block addresses outside matrix"
			<< abort(FatalError);
	}
#endif
}


template<class MatrixType>
tnbLib::MatrixBlock<MatrixType>::MatrixBlock
(
	MatrixType& matrix,
	const label m,
	const label n,
	const label mStart,
	const label nStart
)
	:
	matrix_(matrix),
	mRows_(m),
	nCols_(n),
	rowStart_(mStart),
	colStart_(nStart)
{
#ifdef FULLDEBUG
	if
		(
			rowStart_ + mRows_ > matrix.m()
			|| colStart_ + nCols_ > matrix.n()
			)
	{
		FatalErrorInFunction
			<< "Block addresses outside matrix"
			<< abort(FatalError);
	}
#endif
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class MatrixType>
inline tnbLib::label tnbLib::ConstMatrixBlock<MatrixType>::m() const
{
	return mRows_;
}


template<class MatrixType>
inline tnbLib::label tnbLib::ConstMatrixBlock<MatrixType>::n() const
{
	return nCols_;
}


template<class MatrixType>
inline tnbLib::label tnbLib::MatrixBlock<MatrixType>::m() const
{
	return mRows_;
}


template<class MatrixType>
inline tnbLib::label tnbLib::MatrixBlock<MatrixType>::n() const
{
	return nCols_;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class MatrixType>
inline const typename MatrixType::cmptType&
tnbLib::ConstMatrixBlock<MatrixType>::operator()
(
	const label i,
	const label j
	) const
{
#ifdef FULLDEBUG
	if (i < 0 || i >= mRows_)
	{
		FatalErrorInFunction
			<< "Index " << i << " out of range 0 ... " << mRows_ - 1
			<< abort(FatalError);
	}
	if (j < 0 || j >= nCols_)
	{
		FatalErrorInFunction
			<< "Index " << j << " out of range 0 ... " << nCols_ - 1
			<< abort(FatalError);
	}
#endif

	return matrix_(i + rowStart_, j + colStart_);
}


template<class MatrixType>
inline const typename MatrixType::cmptType&
tnbLib::MatrixBlock<MatrixType>::operator()
(
	const label i,
	const label j
	) const
{
#ifdef FULLDEBUG
	if (i < 0 || i >= mRows_)
	{
		FatalErrorInFunction
			<< "Index " << i << " out of range 0 ... " << mRows_ - 1
			<< abort(FatalError);
	}
	if (j < 0 || j >= nCols_)
	{
		FatalErrorInFunction
			<< "Index " << j << " out of range 0 ... " << nCols_ - 1
			<< abort(FatalError);
	}
#endif

	return matrix_(i + rowStart_, j + colStart_);
}


template<class MatrixType>
inline typename MatrixType::cmptType&
tnbLib::MatrixBlock<MatrixType>::operator()
(
	const label i,
	const label j
	)
{
#ifdef FULLDEBUG
	if (i < 0 || i >= mRows_)
	{
		FatalErrorInFunction
			<< "Index " << i << " out of range 0 ... " << mRows_ - 1
			<< abort(FatalError);
	}
	if (j < 0 || j >= nCols_)
	{
		FatalErrorInFunction
			<< "Index " << j << " out of range 0 ... " << nCols_ - 1
			<< abort(FatalError);
	}
#endif

	return matrix_(i + rowStart_, j + colStart_);
}


// ************************************************************************* //