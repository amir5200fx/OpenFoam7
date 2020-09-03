#pragma once
#include <DiagonalSolverTemplate.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type, class DType, class LUType>
tnbLib::autoPtr<typename tnbLib::LduMatrix<Type, DType, LUType>::solver>
tnbLib::LduMatrix<Type, DType, LUType>::solver::New
(
	const word& fieldName,
	const LduMatrix<Type, DType, LUType>& matrix,
	const dictionary& solverDict
)
{
	word solverName = solverDict.lookup("solver");

	if (matrix.diagonal())
	{
		return autoPtr<typename LduMatrix<Type, DType, LUType>::solver>
			(
				new DiagonalSolver<Type, DType, LUType>
				(
					fieldName,
					matrix,
					solverDict
					)
				);
	}
	else if (matrix.symmetric())
	{
		typename symMatrixConstructorTable::iterator constructorIter =
			symMatrixConstructorTablePtr_->find(solverName);

		if (constructorIter == symMatrixConstructorTablePtr_->end())
		{
			FatalIOErrorInFunction(solverDict)
				<< "Unknown symmetric matrix solver " << solverName
				<< endl << endl
				<< "Valid symmetric matrix solvers are :" << endl
				<< symMatrixConstructorTablePtr_->toc()
				<< exit(FatalIOError);
		}

		return autoPtr<typename LduMatrix<Type, DType, LUType>::solver>
			(
				constructorIter()
				(
					fieldName,
					matrix,
					solverDict
					)
				);
	}
	else if (matrix.asymmetric())
	{
		typename asymMatrixConstructorTable::iterator constructorIter =
			asymMatrixConstructorTablePtr_->find(solverName);

		if (constructorIter == asymMatrixConstructorTablePtr_->end())
		{
			FatalIOErrorInFunction(solverDict)
				<< "Unknown asymmetric matrix solver " << solverName
				<< endl << endl
				<< "Valid asymmetric matrix solvers are :" << endl
				<< asymMatrixConstructorTablePtr_->toc()
				<< exit(FatalIOError);
		}

		return autoPtr<typename LduMatrix<Type, DType, LUType>::solver>
			(
				constructorIter()
				(
					fieldName,
					matrix,
					solverDict
					)
				);
	}
	else
	{
		FatalIOErrorInFunction(solverDict)
			<< "cannot solve incomplete matrix, "
			"no diagonal or off-diagonal coefficient"
			<< exit(FatalIOError);

		return autoPtr<typename LduMatrix<Type, DType, LUType>::solver>
			(
				nullptr
				);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type, class DType, class LUType>
tnbLib::LduMatrix<Type, DType, LUType>::solver::solver
(
	const word& fieldName,
	const LduMatrix<Type, DType, LUType>& matrix,
	const dictionary& solverDict
)
	:
	fieldName_(fieldName),
	matrix_(matrix),

	controlDict_(solverDict),

	maxIter_(defaultMaxIter_),
	minIter_(0),
	tolerance_(1e-6*pTraits<Type>::one),
	relTol_(Zero)
{
	readControls();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type, class DType, class LUType>
void tnbLib::LduMatrix<Type, DType, LUType>::solver::readControls()
{
	readControl(controlDict_, maxIter_, "maxIter");
	readControl(controlDict_, minIter_, "minIter");
	readControl(controlDict_, tolerance_, "tolerance");
	readControl(controlDict_, relTol_, "relTol");
}


template<class Type, class DType, class LUType>
void tnbLib::LduMatrix<Type, DType, LUType>::solver::read
(
	const dictionary& solverDict
)
{
	controlDict_ = solverDict;
	readControls();
}


template<class Type, class DType, class LUType>
Type tnbLib::LduMatrix<Type, DType, LUType>::solver::normFactor
(
	const Field<Type>& psi,
	const Field<Type>& Apsi,
	Field<Type>& tmpField
) const
{
	// --- Calculate A dot reference value of psi
	matrix_.sumA(tmpField);
	cmptMultiply(tmpField, tmpField, gAverage(psi));

	return stabilise
	(
		gSum(cmptMag(Apsi - tmpField) + cmptMag(matrix_.source() - tmpField)),
		SolverPerformance<Type>::small_
	);

	// At convergence this simpler method is equivalent to the above
	// return stabilise(2*gSumCmptMag(matrix_.source()), matrix_.small_);
}


// ************************************************************************* //