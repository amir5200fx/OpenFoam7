#pragma once
#include <lduMatrix.hxx>
#include <IOstreams.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type, class DType, class LUType>
tnbLib::LduMatrix<Type, DType, LUType>::LduMatrix(const lduMesh& mesh)
	:
	lduMesh_(mesh),
	diagPtr_(nullptr),
	upperPtr_(nullptr),
	lowerPtr_(nullptr),
	sourcePtr_(nullptr),
	interfaces_(0),
	interfacesUpper_(0),
	interfacesLower_(0)
{}


template<class Type, class DType, class LUType>
tnbLib::LduMatrix<Type, DType, LUType>::LduMatrix(const LduMatrix& A)
	:
	lduMesh_(A.lduMesh_),
	diagPtr_(nullptr),
	upperPtr_(nullptr),
	lowerPtr_(nullptr),
	sourcePtr_(nullptr),
	interfaces_(0),
	interfacesUpper_(0),
	interfacesLower_(0)
{
	if (A.diagPtr_)
	{
		diagPtr_ = new Field<DType>(*(A.diagPtr_));
	}

	if (A.upperPtr_)
	{
		upperPtr_ = new Field<LUType>(*(A.upperPtr_));
	}

	if (A.lowerPtr_)
	{
		lowerPtr_ = new Field<LUType>(*(A.lowerPtr_));
	}

	if (A.sourcePtr_)
	{
		sourcePtr_ = new Field<Type>(*(A.sourcePtr_));
	}
}


template<class Type, class DType, class LUType>
tnbLib::LduMatrix<Type, DType, LUType>::LduMatrix(LduMatrix& A, bool reuse)
	:
	lduMesh_(A.lduMesh_),
	diagPtr_(nullptr),
	upperPtr_(nullptr),
	lowerPtr_(nullptr),
	sourcePtr_(nullptr),
	interfaces_(0),
	interfacesUpper_(0),
	interfacesLower_(0)
{
	if (reuse)
	{
		if (A.diagPtr_)
		{
			diagPtr_ = A.diagPtr_;
			A.diagPtr_ = nullptr;
		}

		if (A.upperPtr_)
		{
			upperPtr_ = A.upperPtr_;
			A.upperPtr_ = nullptr;
		}

		if (A.lowerPtr_)
		{
			lowerPtr_ = A.lowerPtr_;
			A.lowerPtr_ = nullptr;
		}

		if (A.sourcePtr_)
		{
			sourcePtr_ = A.sourcePtr_;
			A.sourcePtr_ = nullptr;
		}
	}
	else
	{
		if (A.diagPtr_)
		{
			diagPtr_ = new Field<DType>(*(A.diagPtr_));
		}

		if (A.upperPtr_)
		{
			upperPtr_ = new Field<LUType>(*(A.upperPtr_));
		}

		if (A.lowerPtr_)
		{
			lowerPtr_ = new Field<LUType>(*(A.lowerPtr_));
		}

		if (A.sourcePtr_)
		{
			sourcePtr_ = new Field<Type>(*(A.sourcePtr_));
		}
	}
}


template<class Type, class DType, class LUType>
tnbLib::LduMatrix<Type, DType, LUType>::LduMatrix
(
	const lduMesh& mesh,
	Istream& is
)
	:
	lduMesh_(mesh),
	diagPtr_(new Field<DType>(is)),
	upperPtr_(new Field<LUType>(is)),
	lowerPtr_(new Field<LUType>(is)),
	sourcePtr_(new Field<Type>(is)),
	interfaces_(0),
	interfacesUpper_(0),
	interfacesLower_(0)
{}


// * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * * //

template<class Type, class DType, class LUType>
tnbLib::LduMatrix<Type, DType, LUType>::~LduMatrix()
{
	if (diagPtr_)
	{
		delete diagPtr_;
	}

	if (upperPtr_)
	{
		delete upperPtr_;
	}

	if (lowerPtr_)
	{
		delete lowerPtr_;
	}

	if (sourcePtr_)
	{
		delete sourcePtr_;
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type, class DType, class LUType>
tnbLib::Field<DType>& tnbLib::LduMatrix<Type, DType, LUType>::diag()
{
	if (!diagPtr_)
	{
		diagPtr_ = new Field<DType>(lduAddr().size(), Zero);
	}

	return *diagPtr_;
}


template<class Type, class DType, class LUType>
tnbLib::Field<LUType>& tnbLib::LduMatrix<Type, DType, LUType>::upper()
{
	if (!upperPtr_)
	{
		if (lowerPtr_)
		{
			upperPtr_ = new Field<LUType>(*lowerPtr_);
		}
		else
		{
			upperPtr_ = new Field<LUType>
				(
					lduAddr().lowerAddr().size(),
					Zero
					);
		}
	}

	return *upperPtr_;
}


template<class Type, class DType, class LUType>
tnbLib::Field<LUType>& tnbLib::LduMatrix<Type, DType, LUType>::lower()
{
	if (!lowerPtr_)
	{
		if (upperPtr_)
		{
			lowerPtr_ = new Field<LUType>(*upperPtr_);
		}
		else
		{
			lowerPtr_ = new Field<LUType>
				(
					lduAddr().lowerAddr().size(),
					Zero
					);
		}
	}

	return *lowerPtr_;
}


template<class Type, class DType, class LUType>
tnbLib::Field<Type>& tnbLib::LduMatrix<Type, DType, LUType>::source()
{
	if (!sourcePtr_)
	{
		sourcePtr_ = new Field<Type>(lduAddr().size(), Zero);
	}

	return *sourcePtr_;
}


template<class Type, class DType, class LUType>
const tnbLib::Field<DType>& tnbLib::LduMatrix<Type, DType, LUType>::diag() const
{
	if (!diagPtr_)
	{
		FatalErrorInFunction
			<< "diagPtr_ unallocated"
			<< abort(FatalError);
	}

	return *diagPtr_;
}


template<class Type, class DType, class LUType>
const tnbLib::Field<LUType>& tnbLib::LduMatrix<Type, DType, LUType>::upper() const
{
	if (!lowerPtr_ && !upperPtr_)
	{
		FatalErrorInFunction
			<< "lowerPtr_ or upperPtr_ unallocated"
			<< abort(FatalError);
	}

	if (upperPtr_)
	{
		return *upperPtr_;
	}
	else
	{
		return *lowerPtr_;
	}
}


template<class Type, class DType, class LUType>
const tnbLib::Field<LUType>& tnbLib::LduMatrix<Type, DType, LUType>::lower() const
{
	if (!lowerPtr_ && !upperPtr_)
	{
		FatalErrorInFunction
			<< "lowerPtr_ or upperPtr_ unallocated"
			<< abort(FatalError);
	}

	if (lowerPtr_)
	{
		return *lowerPtr_;
	}
	else
	{
		return *upperPtr_;
	}
}


template<class Type, class DType, class LUType>
const tnbLib::Field<Type>& tnbLib::LduMatrix<Type, DType, LUType>::source() const
{
	if (!sourcePtr_)
	{
		FatalErrorInFunction
			<< "sourcePtr_ unallocated"
			<< abort(FatalError);
	}

	return *sourcePtr_;
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

template<class Type, class DType, class LUType>
tnbLib::Ostream& tnbLib::operator<<
(
	Ostream& os,
	const LduMatrix<Type, DType, LUType>& ldum
	)
{
	if (ldum.diagPtr_)
	{
		os << "Diagonal = "
			<< *ldum.diagPtr_
			<< endl << endl;
	}

	if (ldum.upperPtr_)
	{
		os << "Upper triangle = "
			<< *ldum.upperPtr_
			<< endl << endl;
	}

	if (ldum.lowerPtr_)
	{
		os << "Lower triangle = "
			<< *ldum.lowerPtr_
			<< endl << endl;
	}

	if (ldum.sourcePtr_)
	{
		os << "Source = "
			<< *ldum.sourcePtr_
			<< endl << endl;
	}

	os.check("Ostream& operator<<(Ostream&, const LduMatrix&");

	return os;
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //