#include <diagonalPreconditioner.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(diagonalPreconditioner, 0);

	lduMatrix::preconditioner::
		addsymMatrixConstructorToTable<diagonalPreconditioner>
		adddiagonalPreconditionerSymMatrixConstructorToTable_;

	lduMatrix::preconditioner::
		addasymMatrixConstructorToTable<diagonalPreconditioner>
		adddiagonalPreconditionerAsymMatrixConstructorToTable_;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::diagonalPreconditioner::diagonalPreconditioner
(
	const lduMatrix::solver& sol,
	const dictionary&
)
	:
	lduMatrix::preconditioner(sol),
	rD(sol.matrix().diag().size())
{
	scalar* __restrict rDPtr = rD.begin();
	const scalar* __restrict DPtr = solver_.matrix().diag().begin();

	label nCells = rD.size();

	// Generate reciprocal diagonal
	for (label cell = 0; cell < nCells; cell++)
	{
		rDPtr[cell] = 1.0 / DPtr[cell];
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::diagonalPreconditioner::precondition
(
	scalarField& wA,
	const scalarField& rA,
	const direction
) const
{
	scalar* __restrict wAPtr = wA.begin();
	const scalar* __restrict rAPtr = rA.begin();
	const scalar* __restrict rDPtr = rD.begin();

	label nCells = wA.size();

	for (label cell = 0; cell < nCells; cell++)
	{
		wAPtr[cell] = rDPtr[cell] * rAPtr[cell];
	}
}


// ************************************************************************* //