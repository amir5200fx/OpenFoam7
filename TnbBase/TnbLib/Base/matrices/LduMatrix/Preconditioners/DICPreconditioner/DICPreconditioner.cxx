#include <DICPreconditioner.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(DICPreconditioner, 0);

	lduMatrix::preconditioner::
		addsymMatrixConstructorToTable<DICPreconditioner>
		addDICPreconditionerSymMatrixConstructorToTable_;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::DICPreconditioner::DICPreconditioner
(
	const lduMatrix::solver& sol,
	const dictionary&
)
	:
	lduMatrix::preconditioner(sol),
	rD_(sol.matrix().diag())
{
	calcReciprocalD(rD_, sol.matrix());
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::DICPreconditioner::calcReciprocalD
(
	scalarField& rD,
	const lduMatrix& matrix
)
{
	scalar* __restrict rDPtr = rD.begin();

	const label* const __restrict uPtr = matrix.lduAddr().upperAddr().begin();
	const label* const __restrict lPtr = matrix.lduAddr().lowerAddr().begin();
	const scalar* const __restrict upperPtr = matrix.upper().begin();

	// Calculate the DIC diagonal
	const label nFaces = matrix.upper().size();
	for (label face = 0; face < nFaces; face++)
	{
		rDPtr[uPtr[face]] -= upperPtr[face] * upperPtr[face] / rDPtr[lPtr[face]];
	}


	// Calculate the reciprocal of the preconditioned diagonal
	const label nCells = rD.size();

	for (label cell = 0; cell < nCells; cell++)
	{
		rDPtr[cell] = 1.0 / rDPtr[cell];
	}
}


void tnbLib::DICPreconditioner::precondition
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
	const scalar* const __restrict upperPtr =
		solver_.matrix().upper().begin();

	label nCells = wA.size();
	label nFaces = solver_.matrix().upper().size();
	label nFacesM1 = nFaces - 1;

	for (label cell = 0; cell < nCells; cell++)
	{
		wAPtr[cell] = rDPtr[cell] * rAPtr[cell];
	}

	for (label face = 0; face < nFaces; face++)
	{
		wAPtr[uPtr[face]] -= rDPtr[uPtr[face]] * upperPtr[face] * wAPtr[lPtr[face]];
	}

	for (label face = nFacesM1; face >= 0; face--)
	{
		wAPtr[lPtr[face]] -= rDPtr[lPtr[face]] * upperPtr[face] * wAPtr[uPtr[face]];
	}
}


// ************************************************************************* //