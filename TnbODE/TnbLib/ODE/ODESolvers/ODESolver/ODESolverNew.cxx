#include <ODESolver.hxx>

#include <dictionary.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::ODESolver> tnbLib::ODESolver::New
(
	const ODESystem& odes,
	const dictionary& dict
)
{
	word ODESolverTypeName(dict.lookup("solver"));
	Info << "Selecting ODE solver " << ODESolverTypeName << endl;

	dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(ODESolverTypeName);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown ODESolver type "
			<< ODESolverTypeName << nl << nl
			<< "Valid ODESolvers are : " << endl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<ODESolver>(cstrIter()(odes, dict));
}


// ************************************************************************* //