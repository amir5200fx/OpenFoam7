#include <sixDoFSolver.hxx>

// * * * * * * * * * * * * * * * * Selector  * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::sixDoFSolver> tnbLib::sixDoFSolver::New
(
	const dictionary& dict,
	sixDoFRigidBodyMotion& body
)
{
	word sixDoFSolverType(dict.lookup("type"));

	Info << "Selecting sixDoFSolver " << sixDoFSolverType << endl;

	dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(sixDoFSolverType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown sixDoFSolverType type "
			<< sixDoFSolverType << endl << endl
			<< "Valid sixDoFSolver types are : " << endl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return cstrIter()(dict, body);
}


// ************************************************************************* //