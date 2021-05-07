#include <rigidBodySolver.hxx>

// * * * * * * * * * * * * * * * * Selector  * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::RBD::rigidBodySolver> tnbLib::RBD::rigidBodySolver::New
(
	rigidBodyMotion& body,
	const dictionary& dict
)
{
	word rigidBodySolverType(dict.lookup("type"));

	Info << "Selecting rigidBodySolver " << rigidBodySolverType << endl;

	dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(rigidBodySolverType);

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown rigidBodySolverType type "
			<< rigidBodySolverType << endl << endl
			<< "Valid rigidBodySolver types are : " << endl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return cstrIter()(body, dict);
}


// ************************************************************************* //