#include <motionSolver.hxx>

#include <twoDPointCorrector.hxx>

#include <motionSolverList.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(motionSolver, 0);
	defineRunTimeSelectionTable(motionSolver, dictionary);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::motionSolver::motionSolver
(
	const polyMesh& mesh,
	const dictionary& dict,
	const word& type
)
	:
	mesh_(mesh),
	coeffDict_(dict.optionalSubDict(type + "Coeffs"))
{}


tnbLib::autoPtr<tnbLib::motionSolver> tnbLib::motionSolver::clone() const
{
	NotImplemented;
	return autoPtr<motionSolver>(nullptr);
}


// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::motionSolver> tnbLib::motionSolver::New
(
	const polyMesh& mesh,
	const dictionary& solverDict
)
{
	if (solverDict.found("solvers"))
	{
		return autoPtr<motionSolver>(new motionSolverList(mesh, solverDict));
	}
	else
	{
		const word solverTypeName
		(
			solverDict.found("motionSolver")
			? solverDict.lookup("motionSolver")
			: solverDict.lookup("solver")
		);

		Info << "Selecting motion solver: " << solverTypeName << endl;

		const_cast<Time&>(mesh.time()).libs().open
		(
			solverDict,
			"motionSolverLibs",
			dictionaryConstructorTablePtr_
		);

		if (!dictionaryConstructorTablePtr_)
		{
			FatalErrorInFunction
				<< "solver table is empty"
				<< exit(FatalError);
		}

		dictionaryConstructorTable::iterator cstrIter =
			dictionaryConstructorTablePtr_->find(solverTypeName);

		if (cstrIter == dictionaryConstructorTablePtr_->end())
		{
			FatalErrorInFunction
				<< "Unknown solver type "
				<< solverTypeName << nl << nl
				<< "Valid solver types are:" << endl
				<< dictionaryConstructorTablePtr_->sortedToc()
				<< exit(FatalError);
		}

		return autoPtr<motionSolver>(cstrIter()(mesh, solverDict));
	}
}


tnbLib::motionSolver::iNew::iNew(const polyMesh& mesh)
	:
	mesh_(mesh)
{}


tnbLib::autoPtr<tnbLib::motionSolver> tnbLib::motionSolver::iNew::operator()
(
	Istream& is
	) const
{
	dictionaryEntry dict(dictionary::null, is);

	return motionSolver::New(mesh_, dict);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::motionSolver::~motionSolver()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::pointField> tnbLib::motionSolver::newPoints()
{
	solve();
	return curPoints();
}


void tnbLib::motionSolver::twoDCorrectPoints(pointField& p) const
{
	twoDPointCorrector::New(mesh_).correctPoints(p);
}


void tnbLib::motionSolver::updateMesh(const mapPolyMesh& mpm)
{}


bool tnbLib::motionSolver::write() const
{
	return true;
}


// ************************************************************************* //