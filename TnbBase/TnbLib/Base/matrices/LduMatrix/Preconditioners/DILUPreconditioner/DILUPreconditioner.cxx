#include <DILUPreconditioner.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(DILUPreconditioner, 0);

	lduMatrix::preconditioner::
		addasymMatrixConstructorToTable<DILUPreconditioner>
		addDILUPreconditionerAsymMatrixConstructorToTable_;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::DILUPreconditioner::DILUPreconditioner
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

void tnbLib::DILUPreconditioner::calcReciprocalD
(
	scalarField& rD,
	const lduMatrix& matrix
)
{
	scalar* __restrict rDPtr = rD.begin();

	const label* const __restrict uPtr = matrix.lduAddr().upperAddr().begin();
	const label* const __restrict lPtr = matrix.lduAddr().lowerAddr().begin();

	const scalar* const __restrict upperPtr = matrix.upper().begin();
	const scalar* const __restrict lowerPtr = matrix.lower().begin();

	label nFaces = matrix.upper().size();
	for (label face = 0; face < nFaces; face++)
	{
		rDPtr[uPtr[face]] -= upperPtr[face] * lowerPtr[face] / rDPtr[lPtr[face]];
	}


	// Calculate the reciprocal of the preconditioned diagonal
	label nCells = rD.size();

	for (label cell = 0; cell < nCells; cell++)
	{
		rDPtr[cell] = 1.0 / rDPtr[cell];
	}
}


void tnbLib::DILUPreconditioner::precondition
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
	const label* const __restrict losortPtr =
		solver_.matrix().lduAddr().losortAddr().begin();

	const scalar* const __restrict upperPtr =
		solver_.matrix().upper().begin();
	const scalar* const __restrict lowerPtr =
		solver_.matrix().lower().begin();

	label nCells = wA.size();
	label nFaces = solver_.matrix().upper().size();
	label nFacesM1 = nFaces - 1;

	for (label cell = 0; cell < nCells; cell++)
	{
		wAPtr[cell] = rDPtr[cell] * rAPtr[cell];
	}


	label sface;

	for (label face = 0; face < nFaces; face++)
	{
		sface = losortPtr[face];
		wAPtr[uPtr[sface]] -=
			rDPtr[uPtr[sface]] * lowerPtr[sface] * wAPtr[lPtr[sface]];
	}

	for (label face = nFacesM1; face >= 0; face--)
	{
		wAPtr[lPtr[face]] -=
			rDPtr[lPtr[face]] * upperPtr[face] * wAPtr[uPtr[face]];
	}
}


void tnbLib::DILUPreconditioner::preconditionT
(
	scalarField& wT,
	const scalarField& rT,
	const direction
) const
{
	scalar* __restrict wTPtr = wT.begin();
	const scalar* __restrict rTPtr = rT.begin();
	const scalar* __restrict rDPtr = rD_.begin();

	const label* const __restrict uPtr =
		solver_.matrix().lduAddr().upperAddr().begin();
	const label* const __restrict lPtr =
		solver_.matrix().lduAddr().lowerAddr().begin();
	const label* const __restrict losortPtr =
		solver_.matrix().lduAddr().losortAddr().begin();

	const scalar* const __restrict upperPtr =
		solver_.matrix().upper().begin();
	const scalar* const __restrict lowerPtr =
		solver_.matrix().lower().begin();

	label nCells = wT.size();
	label nFaces = solver_.matrix().upper().size();
	label nFacesM1 = nFaces - 1;

	for (label cell = 0; cell < nCells; cell++)
	{
		wTPtr[cell] = rDPtr[cell] * rTPtr[cell];
	}

	for (label face = 0; face < nFaces; face++)
	{
		wTPtr[uPtr[face]] -=
			rDPtr[uPtr[face]] * upperPtr[face] * wTPtr[lPtr[face]];
	}


	label sface;

	for (label face = nFacesM1; face >= 0; face--)
	{
		sface = losortPtr[face];
		wTPtr[lPtr[sface]] -=
			rDPtr[lPtr[sface]] * lowerPtr[sface] * wTPtr[uPtr[sface]];
	}
}


// ************************************************************************* //