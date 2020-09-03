#pragma once
#include <dictionary.hxx> // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type, class DType, class LUType>
tnbLib::autoPtr<typename tnbLib::LduMatrix<Type, DType, LUType>::preconditioner>
tnbLib::LduMatrix<Type, DType, LUType>::preconditioner::New
(
	const solver& sol,
	const dictionary& preconditionerDict
)
{
	word preconditionerName = preconditionerDict.lookup("preconditioner");

	if (sol.matrix().symmetric())
	{
		typename symMatrixConstructorTable::iterator constructorIter =
			symMatrixConstructorTablePtr_->find(preconditionerName);

		if (constructorIter == symMatrixConstructorTablePtr_->end())
		{
			FatalIOErrorInFunction
			(
				preconditionerDict
			) << "Unknown symmetric matrix preconditioner "
				<< preconditionerName << endl << endl
				<< "Valid symmetric matrix preconditioners are :" << endl
				<< symMatrixConstructorTablePtr_->toc()
				<< exit(FatalIOError);
		}

		return autoPtr<typename LduMatrix<Type, DType, LUType>::preconditioner>
			(
				constructorIter()
				(
					sol,
					preconditionerDict
					)
				);
	}
	else if (sol.matrix().asymmetric())
	{
		typename asymMatrixConstructorTable::iterator constructorIter =
			asymMatrixConstructorTablePtr_->find(preconditionerName);

		if (constructorIter == asymMatrixConstructorTablePtr_->end())
		{
			FatalIOErrorInFunction
			(
				preconditionerDict
			) << "Unknown asymmetric matrix preconditioner "
				<< preconditionerName << endl << endl
				<< "Valid asymmetric matrix preconditioners are :" << endl
				<< asymMatrixConstructorTablePtr_->toc()
				<< exit(FatalIOError);
		}

		return autoPtr<typename LduMatrix<Type, DType, LUType>::preconditioner>
			(
				constructorIter()
				(
					sol,
					preconditionerDict
					)
				);
	}
	else
	{
		FatalIOErrorInFunction
		(
			preconditionerDict
		) << "cannot preconditione incomplete matrix, "
			"no diagonal or off-diagonal coefficient"
			<< exit(FatalIOError);

		return autoPtr<typename LduMatrix<Type, DType, LUType>::preconditioner>
			(
				nullptr
				);
	}
}


// ************************************************************************* //