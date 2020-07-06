#include <diagonalSolver.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(diagonalSolver, 0);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::diagonalSolver::diagonalSolver
(
	const word& fieldName,
	const lduMatrix& matrix,
	const FieldField<Field, scalar>& interfaceBouCoeffs,
	const FieldField<Field, scalar>& interfaceIntCoeffs,
	const lduInterfaceFieldPtrsList& interfaces,
	const dictionary& solverControls
)
	:
	lduMatrix::solver
	(
		fieldName,
		matrix,
		interfaceBouCoeffs,
		interfaceIntCoeffs,
		interfaces,
		solverControls
	)
{}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::solverPerformance tnbLib::diagonalSolver::solve
(
	scalarField& psi,
	const scalarField& source,
	const direction cmpt
) const
{
	psi = source / matrix_.diag();

	return solverPerformance
	(
		typeName,
		fieldName_,
		0,
		0,
		0,
		true,
		false
	);
}


// ************************************************************************* //