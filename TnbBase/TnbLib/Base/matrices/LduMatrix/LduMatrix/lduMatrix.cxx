#include <lduMatrix.hxx>

#include <IOstreams.hxx>
#include <Switch.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(lduMatrix, 1);
}


const tnbLib::label tnbLib::lduMatrix::solver::defaultMaxIter_ = 1000;


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::lduMatrix::lduMatrix(const lduMesh& mesh)
	:
	lduMesh_(mesh),
	lowerPtr_(nullptr),
	diagPtr_(nullptr),
	upperPtr_(nullptr)
{}


tnbLib::lduMatrix::lduMatrix(const lduMatrix& A)
	:
	lduMesh_(A.lduMesh_),
	lowerPtr_(nullptr),
	diagPtr_(nullptr),
	upperPtr_(nullptr)
{
	if (A.lowerPtr_)
	{
		lowerPtr_ = new scalarField(*(A.lowerPtr_));
	}

	if (A.diagPtr_)
	{
		diagPtr_ = new scalarField(*(A.diagPtr_));
	}

	if (A.upperPtr_)
	{
		upperPtr_ = new scalarField(*(A.upperPtr_));
	}
}


tnbLib::lduMatrix::lduMatrix(lduMatrix& A, bool reuse)
	:
	lduMesh_(A.lduMesh_),
	lowerPtr_(nullptr),
	diagPtr_(nullptr),
	upperPtr_(nullptr)
{
	if (reuse)
	{
		if (A.lowerPtr_)
		{
			lowerPtr_ = A.lowerPtr_;
			A.lowerPtr_ = nullptr;
		}

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
	}
	else
	{
		if (A.lowerPtr_)
		{
			lowerPtr_ = new scalarField(*(A.lowerPtr_));
		}

		if (A.diagPtr_)
		{
			diagPtr_ = new scalarField(*(A.diagPtr_));
		}

		if (A.upperPtr_)
		{
			upperPtr_ = new scalarField(*(A.upperPtr_));
		}
	}
}


tnbLib::lduMatrix::lduMatrix(const lduMesh& mesh, Istream& is)
	:
	lduMesh_(mesh),
	lowerPtr_(nullptr),
	diagPtr_(nullptr),
	upperPtr_(nullptr)
{
	Switch hasLow(is);
	Switch hasDiag(is);
	Switch hasUp(is);

	if (hasLow)
	{
		lowerPtr_ = new scalarField(is);
	}
	if (hasDiag)
	{
		diagPtr_ = new scalarField(is);
	}
	if (hasUp)
	{
		upperPtr_ = new scalarField(is);
	}
}


tnbLib::lduMatrix::~lduMatrix()
{
	if (lowerPtr_)
	{
		delete lowerPtr_;
	}

	if (diagPtr_)
	{
		delete diagPtr_;
	}

	if (upperPtr_)
	{
		delete upperPtr_;
	}
}


tnbLib::scalarField& tnbLib::lduMatrix::lower()
{
	if (!lowerPtr_)
	{
		if (upperPtr_)
		{
			lowerPtr_ = new scalarField(*upperPtr_);
		}
		else
		{
			lowerPtr_ = new scalarField(lduAddr().lowerAddr().size(), 0.0);
		}
	}

	return *lowerPtr_;
}


tnbLib::scalarField& tnbLib::lduMatrix::diag()
{
	if (!diagPtr_)
	{
		diagPtr_ = new scalarField(lduAddr().size(), 0.0);
	}

	return *diagPtr_;
}


tnbLib::scalarField& tnbLib::lduMatrix::upper()
{
	if (!upperPtr_)
	{
		if (lowerPtr_)
		{
			upperPtr_ = new scalarField(*lowerPtr_);
		}
		else
		{
			upperPtr_ = new scalarField(lduAddr().lowerAddr().size(), 0.0);
		}
	}

	return *upperPtr_;
}


tnbLib::scalarField& tnbLib::lduMatrix::lower(const label nCoeffs)
{
	if (!lowerPtr_)
	{
		if (upperPtr_)
		{
			lowerPtr_ = new scalarField(*upperPtr_);
		}
		else
		{
			lowerPtr_ = new scalarField(nCoeffs, 0.0);
		}
	}

	return *lowerPtr_;
}


tnbLib::scalarField& tnbLib::lduMatrix::diag(const label size)
{
	if (!diagPtr_)
	{
		diagPtr_ = new scalarField(size, 0.0);
	}

	return *diagPtr_;
}


tnbLib::scalarField& tnbLib::lduMatrix::upper(const label nCoeffs)
{
	if (!upperPtr_)
	{
		if (lowerPtr_)
		{
			upperPtr_ = new scalarField(*lowerPtr_);
		}
		else
		{
			upperPtr_ = new scalarField(nCoeffs, 0.0);
		}
	}

	return *upperPtr_;
}


const tnbLib::scalarField& tnbLib::lduMatrix::lower() const
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


const tnbLib::scalarField& tnbLib::lduMatrix::diag() const
{
	if (!diagPtr_)
	{
		FatalErrorInFunction
			<< "diagPtr_ unallocated"
			<< abort(FatalError);
	}

	return *diagPtr_;
}


const tnbLib::scalarField& tnbLib::lduMatrix::upper() const
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


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const lduMatrix& ldum)
{
	Switch hasLow = ldum.hasLower();
	Switch hasDiag = ldum.hasDiag();
	Switch hasUp = ldum.hasUpper();

	os << hasLow << token::SPACE << hasDiag << token::SPACE
		<< hasUp << token::SPACE;

	if (hasLow)
	{
		os << ldum.lower();
	}

	if (hasDiag)
	{
		os << ldum.diag();
	}

	if (hasUp)
	{
		os << ldum.upper();
	}

	os.check("Ostream& operator<<(Ostream&, const lduMatrix&");

	return os;
}


tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const InfoProxy<lduMatrix>& ip)
{
	const lduMatrix& ldum = ip.t_;

	Switch hasLow = ldum.hasLower();
	Switch hasDiag = ldum.hasDiag();
	Switch hasUp = ldum.hasUpper();

	os << "Lower:" << hasLow
		<< " Diag:" << hasDiag
		<< " Upper:" << hasUp << endl;

	if (hasLow)
	{
		os << "lower:" << ldum.lower().size() << endl;
	}
	if (hasDiag)
	{
		os << "diag :" << ldum.diag().size() << endl;
	}
	if (hasUp)
	{
		os << "upper:" << ldum.upper().size() << endl;
	}


	// if (hasLow)
	//{
	//    os  << "lower contents:" << endl;
	//    forAll(ldum.lower(), i)
	//    {
	//        os  << "i:" << i << "\t" << ldum.lower()[i] << endl;
	//    }
	//    os  << endl;
	//}
	// if (hasDiag)
	//{
	//    os  << "diag contents:" << endl;
	//    forAll(ldum.diag(), i)
	//    {
	//        os  << "i:" << i << "\t" << ldum.diag()[i] << endl;
	//    }
	//    os  << endl;
	//}
	// if (hasUp)
	//{
	//    os  << "upper contents:" << endl;
	//    forAll(ldum.upper(), i)
	//    {
	//        os  << "i:" << i << "\t" << ldum.upper()[i] << endl;
	//    }
	//    os  << endl;
	//}

	os.check("Ostream& operator<<(Ostream&, const lduMatrix&");

	return os;
}


// ************************************************************************* //