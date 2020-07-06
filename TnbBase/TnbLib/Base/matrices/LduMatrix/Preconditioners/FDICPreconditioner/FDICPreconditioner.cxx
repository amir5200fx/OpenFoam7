#include <FDICPreconditioner.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(FDICPreconditioner, 0);

	lduMatrix::preconditioner::
		addsymMatrixConstructorToTable<FDICPreconditioner>
		addFDICPreconditionerSymMatrixConstructorToTable_;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::FDICPreconditioner::FDICPreconditioner
(
	const lduMatrix::solver& sol,
	const dictionary&
)
	:
	lduMatrix::preconditioner(sol),
	rD_(sol.matrix().diag()),
	rDuUpper_(sol.matrix().upper().size()),
	rDlUpper_(sol.matrix().upper().size())
{
	scalar* __restrict rDPtr = rD_.begin();
	scalar* __restrict rDuUpperPtr = rDuUpper_.begin();
	scalar* __restrict rDlUpperPtr = rDlUpper_.begin();

	const label* const __restrict uPtr =
		solver_.matrix().lduAddr().upperAddr().begin();
	const label* const __restrict lPtr =
		solver_.matrix().lduAddr().lowerAddr().begin();
	const scalar* const __restrict upperPtr =
		solver_.matrix().upper().begin();

	label nCells = rD_.size();
	label nFaces = solver_.matrix().upper().size();

	for (label face = 0; face < nFaces; face++)
	{
		rDPtr[uPtr[face]] -= sqr(upperPtr[face]) / rDPtr[lPtr[face]];
	}

	// Generate reciprocal FDIC
	for (label cell = 0; cell < nCells; cell++)
	{
		rDPtr[cell] = 1.0 / rDPtr[cell];
	}

	for (label face = 0; face < nFaces; face++)
	{
		rDuUpperPtr[face] = rDPtr[uPtr[face]] * upperPtr[face];
		rDlUpperPtr[face] = rDPtr[lPtr[face]] * upperPtr[face];
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::FDICPreconditioner::precondition
(
	scalarField& wA,
	const scalarField& rA,
	const direction
) const
{
	scalar* __restrict wAPtr = wA.begin();
	const scalar* __restrict rAPtr = rA.begin();
	const scalar* __restrict rDPtr = rD_.begin();

	const label* const __restrict uPtr =
		solver_.matrix().lduAddr().upperAddr().begin();
	const label* const __restrict lPtr =
		solver_.matrix().lduAddr().lowerAddr().begin();

	const scalar* const __restrict rDuUpperPtr = rDuUpper_.begin();
	const scalar* const __restrict rDlUpperPtr = rDlUpper_.begin();

	label nCells = wA.size();
	label nFaces = solver_.matrix().upper().size();
	label nFacesM1 = nFaces - 1;

	for (label cell = 0; cell < nCells; cell++)
	{
		wAPtr[cell] = rDPtr[cell] * rAPtr[cell];
	}

	for (label face = 0; face < nFaces; face++)
	{
		wAPtr[uPtr[face]] -= rDuUpperPtr[face] * wAPtr[lPtr[face]];
	}

	for (label face = nFacesM1; face >= 0; face--)
	{
		wAPtr[lPtr[face]] -= rDlUpperPtr[face] * wAPtr[uPtr[face]];
	}
}


// ************************************************************************* //