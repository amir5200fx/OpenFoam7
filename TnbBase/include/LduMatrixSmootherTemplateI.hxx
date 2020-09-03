#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type, class DType, class LUType>
tnbLib::autoPtr<typename tnbLib::LduMatrix<Type, DType, LUType>::smoother>
tnbLib::LduMatrix<Type, DType, LUType>::smoother::New
(
	const word& fieldName,
	const LduMatrix<Type, DType, LUType>& matrix,
	const dictionary& smootherDict
)
{
	word smootherName = smootherDict.lookup("smoother");

	if (matrix.symmetric())
	{
		typename symMatrixConstructorTable::iterator constructorIter =
			symMatrixConstructorTablePtr_->find(smootherName);

		if (constructorIter == symMatrixConstructorTablePtr_->end())
		{
			FatalIOErrorInFunction(smootherDict)
				<< "Unknown symmetric matrix smoother " << smootherName
				<< endl << endl
				<< "Valid symmetric matrix smoothers are :" << endl
				<< symMatrixConstructorTablePtr_->toc()
				<< exit(FatalIOError);
		}

		return autoPtr<typename LduMatrix<Type, DType, LUType>::smoother>
			(
				constructorIter()
				(
					fieldName,
					matrix
					)
				);
	}
	else if (matrix.asymmetric())
	{
		typename asymMatrixConstructorTable::iterator constructorIter =
			asymMatrixConstructorTablePtr_->find(smootherName);

		if (constructorIter == asymMatrixConstructorTablePtr_->end())
		{
			FatalIOErrorInFunction(smootherDict)
				<< "Unknown asymmetric matrix smoother " << smootherName
				<< endl << endl
				<< "Valid asymmetric matrix smoothers are :" << endl
				<< asymMatrixConstructorTablePtr_->toc()
				<< exit(FatalIOError);
		}

		return autoPtr<typename LduMatrix<Type, DType, LUType>::smoother>
			(
				constructorIter()
				(
					fieldName,
					matrix
					)
				);
	}
	else
	{
		FatalIOErrorInFunction(smootherDict)
			<< "cannot solve incomplete matrix, no off-diagonal coefficients"
			<< exit(FatalIOError);

		return autoPtr<typename LduMatrix<Type, DType, LUType>::smoother>
			(
				nullptr
				);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type, class DType, class LUType>
tnbLib::LduMatrix<Type, DType, LUType>::smoother::smoother
(
	const word& fieldName,
	const LduMatrix<Type, DType, LUType>& matrix
)
	:
	fieldName_(fieldName),
	matrix_(matrix)
{}


// ************************************************************************* //