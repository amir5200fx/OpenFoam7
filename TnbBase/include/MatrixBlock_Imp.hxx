#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class MatrixType>
tnbLib::MatrixBlock<MatrixType>::operator tnbLib::Field<typename tnbLib::MatrixBlock<MatrixType>::cmptType>() const
{
	if (nCols_ != 1)
	{
		FatalErrorInFunction
			<< "Number of columns " << nCols_ << " != 1"
			<< abort(FatalError);
	}

	Field<cmptType> f(mRows_);

	forAll(f, i)
	{
		f[i] = operator()(i, 0);
	}

	return f;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class MatrixType>
template<class Form>
void tnbLib::MatrixBlock<MatrixType>::operator=
(
	const Matrix<Form, cmptType>& Mb
	)
{
	if (mRows_ != Mb.m() || nCols_ != Mb.n())
	{
		FatalErrorInFunction
			<< "Attempt to assign blocks of different sizes: "
			<< mRows_ << "x" << nCols_ << " != "
			<< Mb.m() << "x" << Mb.n()
			<< abort(FatalError);
	}

	for (label i = 0; i < mRows_; i++)
	{
		for (label j = 0; j < nCols_; j++)
		{
			(*this)(i, j) = Mb(i, j);
		}
	}
}


template<class MatrixType>
void tnbLib::MatrixBlock<MatrixType>::operator=
(
	const ConstMatrixBlock<MatrixType>& Mb
	)
{
	if (this != &Mb)
	{
		if (mRows_ != Mb.m() || nCols_ != Mb.n())
		{
			FatalErrorInFunction
				<< "Attempt to assign blocks of different sizes: "
				<< mRows_ << "x" << nCols_ << " != "
				<< Mb.m() << "x" << Mb.n()
				<< abort(FatalError);
		}

		for (label i = 0; i < mRows_; i++)
		{
			for (label j = 0; j < nCols_; j++)
			{
				(*this)(i, j) = Mb(i, j);
			}
		}
	}
}


template<class MatrixType>
void tnbLib::MatrixBlock<MatrixType>::operator=
(
	const MatrixBlock<MatrixType>& Mb
	)
{
	if (this != &Mb)
	{
		if (mRows_ != Mb.m() || nCols_ != Mb.n())
		{
			FatalErrorInFunction
				<< "Attempt to assign blocks of different sizes: "
				<< mRows_ << "x" << nCols_ << " != "
				<< Mb.m() << "x" << Mb.n()
				<< abort(FatalError);
		}

		for (label i = 0; i < mRows_; i++)
		{
			for (label j = 0; j < nCols_; j++)
			{
				(*this)(i, j) = Mb(i, j);
			}
		}
	}
}


template<class MatrixType>
template<class MatrixType2>
void tnbLib::MatrixBlock<MatrixType>::operator=
(
	const ConstMatrixBlock<MatrixType2>& Mb
	)
{
	if (this != &Mb)
	{
		if (mRows_ != Mb.m() || nCols_ != Mb.n())
		{
			FatalErrorInFunction
				<< "Attempt to assign blocks of different sizes: "
				<< mRows_ << "x" << nCols_ << " != "
				<< Mb.m() << "x" << Mb.n()
				<< abort(FatalError);
		}

		for (label i = 0; i < mRows_; i++)
		{
			for (label j = 0; j < nCols_; j++)
			{
				(*this)(i, j) = Mb(i, j);
			}
		}
	}
}


template<class MatrixType>
template<class MatrixType2>
void tnbLib::MatrixBlock<MatrixType>::operator=
(
	const MatrixBlock<MatrixType2>& Mb
	)
{
	if (this != &Mb)
	{
		if (mRows_ != Mb.m() || nCols_ != Mb.n())
		{
			FatalErrorInFunction
				<< "Attempt to assign blocks of different sizes: "
				<< mRows_ << "x" << nCols_ << " != "
				<< Mb.m() << "x" << Mb.n()
				<< abort(FatalError);
		}

		for (label i = 0; i < mRows_; i++)
		{
			for (label j = 0; j < nCols_; j++)
			{
				(*this)(i, j) = Mb(i, j);
			}
		}
	}
}


template<class MatrixType>
template
<
	template<class, tnbLib::direction, tnbLib::direction> class MSBlock,
	class SubTensor,
	tnbLib::direction BRowStart,
	tnbLib::direction BColStart
>
void tnbLib::MatrixBlock<MatrixType>::operator=
(
	const MSBlock<SubTensor, BRowStart, BColStart>& Mb
	)
{
	if (mRows_ != Mb.mRows || nCols_ != Mb.nCols)
	{
		FatalErrorInFunction
			<< "Attempt to assign blocks of different sizes: "
			<< mRows_ << "x" << nCols_ << " != "
			<< Mb.mRows << "x" << Mb.nCols
			<< abort(FatalError);
	}

	for (direction i = 0; i < mRows_; ++i)
	{
		for (direction j = 0; j < nCols_; ++j)
		{
			operator()(i, j) = Mb(i, j);
		}
	}
}


template<class MatrixType>
template
<
	template<class, tnbLib::direction> class VSBlock,
	class SubVector,
	tnbLib::direction BStart
>
void tnbLib::MatrixBlock<MatrixType>::operator=
(
	const VSBlock<SubVector, BStart>& Mb
	)
{
	if (mRows_ != Mb.nComponents || nCols_ != 1)
	{
		FatalErrorInFunction
			<< "Attempt to assign blocks of different sizes: "
			<< mRows_ << "x" << nCols_ << " != "
			<< Mb.nComponents << "x" << 1
			<< abort(FatalError);
	}

	for (direction i = 0; i < mRows_; ++i)
	{
		operator()(i, 0) = Mb[i];
	}
}


template<class MatrixType>
template<class MSForm, tnbLib::direction Nrows, tnbLib::direction Ncols>
void tnbLib::MatrixBlock<MatrixType>::operator=
(
	const MatrixSpace<MSForm, cmptType, Nrows, Ncols>& ms
	)
{
	if (mRows_ != Nrows || nCols_ != Ncols)
	{
		FatalErrorInFunction
			<< "Attempt to assign blocks of different sizes: "
			<< mRows_ << "x" << nCols_ << " != "
			<< Nrows << "x" << Ncols
			<< abort(FatalError);
	}

	for (label i = 0; i < mRows_; i++)
	{
		for (label j = 0; j < nCols_; j++)
		{
			(*this)(i, j) = ms(i, j);
		}
	}
}


template<class MatrixType>
template<class VSForm, tnbLib::direction Ncmpts>
void tnbLib::MatrixBlock<MatrixType>::operator=
(
	const VectorSpace<VSForm, cmptType, Ncmpts>& ms
	)
{
	if (mRows_ != Ncmpts || nCols_ != 1)
	{
		FatalErrorInFunction
			<< "Attempt to assign blocks of different sizes: "
			<< mRows_ << "x" << nCols_ << " != "
			<< Ncmpts << "x" << 1
			<< abort(FatalError);
	}

	for (direction i = 0; i < Ncmpts; ++i)
	{
		operator()(i, 0) = ms[i];
	}
}


template<class MatrixType>
void tnbLib::MatrixBlock<MatrixType>::operator=(const Field<cmptType>& f)
{
	if (mRows_ != f.size() || nCols_ != 1)
	{
		FatalErrorInFunction
			<< "Error: cannot assign blocks of different size (left is "
			<< mRows_ << "x" << nCols_ << " != "
			<< f.size() << "x" << 1
			<< abort(FatalError);
	}

	forAll(f, i)
	{
		operator()(i, 0) = f[i];
	}
}


// ************************************************************************* //