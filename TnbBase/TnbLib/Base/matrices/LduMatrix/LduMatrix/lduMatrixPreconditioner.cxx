#include <lduMatrix.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineRunTimeSelectionTable(lduMatrix::preconditioner, symMatrix);
	defineRunTimeSelectionTable(lduMatrix::preconditioner, asymMatrix);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::word tnbLib::lduMatrix::preconditioner::getName
(
	const dictionary& solverControls
)
{
	word name;

	// handle primitive or dictionary entry
	const entry& e = solverControls.lookupEntry("preconditioner", false, false);
	if (e.isDict())
	{
		e.dict().lookup("preconditioner") >> name;
	}
	else
	{
		e.stream() >> name;
	}

	return name;
}


tnbLib::autoPtr<tnbLib::lduMatrix::preconditioner>
tnbLib::lduMatrix::preconditioner::New
(
	const solver& sol,
	const dictionary& solverControls
)
{
	word name;

	// handle primitive or dictionary entry
	const entry& e = solverControls.lookupEntry("preconditioner", false, false);
	if (e.isDict())
	{
		e.dict().lookup("preconditioner") >> name;
	}
	else
	{
		e.stream() >> name;
	}

	const dictionary& controls = e.isDict() ? e.dict() : dictionary::null;

	if (sol.matrix().symmetric())
	{
		symMatrixConstructorTable::iterator constructorIter =
			symMatrixConstructorTablePtr_->find(name);

		if (constructorIter == symMatrixConstructorTablePtr_->end())
		{
			FatalIOErrorInFunction
			(
				controls
			) << "Unknown symmetric matrix preconditioner "
				<< name << nl << nl
				<< "Valid symmetric matrix preconditioners :" << endl
				<< symMatrixConstructorTablePtr_->sortedToc()
				<< exit(FatalIOError);
		}

		return autoPtr<lduMatrix::preconditioner>
			(
				constructorIter()
				(
					sol,
					controls
					)
				);
	}
	else if (sol.matrix().asymmetric())
	{
		asymMatrixConstructorTable::iterator constructorIter =
			asymMatrixConstructorTablePtr_->find(name);

		if (constructorIter == asymMatrixConstructorTablePtr_->end())
		{
			FatalIOErrorInFunction
			(
				controls
			) << "Unknown asymmetric matrix preconditioner "
				<< name << nl << nl
				<< "Valid asymmetric matrix preconditioners :" << endl
				<< asymMatrixConstructorTablePtr_->sortedToc()
				<< exit(FatalIOError);
		}

		return autoPtr<lduMatrix::preconditioner>
			(
				constructorIter()
				(
					sol,
					controls
					)
				);
	}
	else
	{
		FatalIOErrorInFunction
		(
			controls
		) << "cannot solve incomplete matrix, "
			"no diagonal or off-diagonal coefficient"
			<< exit(FatalIOError);

		return autoPtr<lduMatrix::preconditioner>(nullptr);
	}
}


// ************************************************************************* //