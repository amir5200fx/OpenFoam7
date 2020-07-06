#include <FDICSmoother.hxx>

#include <FDICPreconditioner.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(FDICSmoother, 0);

	lduMatrix::smoother::addsymMatrixConstructorToTable<FDICSmoother>
		addFDICSmootherSymMatrixConstructorToTable_;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::FDICSmoother::FDICSmoother
(
	const word& fieldName,
	const lduMatrix& matrix,
	const FieldField<Field, scalar>& interfaceBouCoeffs,
	const FieldField<Field, scalar>& interfaceIntCoeffs,
	const lduInterfaceFieldPtrsList& interfaces
)
	:
	lduMatrix::smoother
	(
		fieldName,
		matrix,
		interfaceBouCoeffs,
		interfaceIntCoeffs,
		interfaces
	),
	rD_(matrix_.diag()),
	rDuUpper_(matrix_.upper().size()),
	rDlUpper_(matrix_.upper().size())
{
	scalar* __restrict rDPtr = rD_.begin();
	scalar* __restrict rDuUpperPtr = rDuUpper_.begin();
	scalar* __restrict rDlUpperPtr = rDlUpper_.begin();

	const label* const __restrict uPtr =
		matrix_.lduAddr().upperAddr().begin();
	const label* const __restrict lPtr =
		matrix_.lduAddr().lowerAddr().begin();
	const scalar* const __restrict upperPtr =
		matrix_.upper().begin();

	label nCells = rD_.size();
	label nFaces = matrix_.upper().size();

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

void tnbLib::FDICSmoother::smooth
(
	scalarField& psi,
	const scalarField& source,
	const direction cmpt,
	const label nSweeps
) const
{
	const scalar* const __restrict rDuUpperPtr = rDuUpper_.begin();
	const scalar* const __restrict rDlUpperPtr = rDlUpper_.begin();

	const label* const __restrict uPtr =
		matrix_.lduAddr().upperAddr().begin();
	const label* const __restrict lPtr =
		matrix_.lduAddr().lowerAddr().begin();

	// Temporary storage for the residual
	scalarField rA(rD_.size());
	scalar* __restrict rAPtr = rA.begin();

	for (label sweep = 0; sweep < nSweeps; sweep++)
	{
		matrix_.residual
		(
			rA,
			psi,
			source,
			interfaceBouCoeffs_,
			interfaces_,
			cmpt
		);

		rA *= rD_;

		label nFaces = matrix_.upper().size();
		for (label face = 0; face < nFaces; face++)
		{
			rAPtr[uPtr[face]] -= rDuUpperPtr[face] * rAPtr[lPtr[face]];
		}

		label nFacesM1 = nFaces - 1;
		for (label face = nFacesM1; face >= 0; face--)
		{
			rAPtr[lPtr[face]] -= rDlUpperPtr[face] * rAPtr[uPtr[face]];
		}

		psi += rA;
	}
}


// ************************************************************************* //