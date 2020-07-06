#include <DILUSmoother.hxx>

#include <DILUPreconditioner.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(DILUSmoother, 0);

	lduMatrix::smoother::addasymMatrixConstructorToTable<DILUSmoother>
		addDILUSmootherAsymMatrixConstructorToTable_;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::DILUSmoother::DILUSmoother
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
	rD_(matrix_.diag())
{
	DILUPreconditioner::calcReciprocalD(rD_, matrix_);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::DILUSmoother::smooth
(
	scalarField& psi,
	const scalarField& source,
	const direction cmpt,
	const label nSweeps
) const
{
	const scalar* const __restrict rDPtr = rD_.begin();

	const label* const __restrict uPtr =
		matrix_.lduAddr().upperAddr().begin();
	const label* const __restrict lPtr =
		matrix_.lduAddr().lowerAddr().begin();

	const scalar* const __restrict upperPtr = matrix_.upper().begin();
	const scalar* const __restrict lowerPtr = matrix_.lower().begin();

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
			label u = uPtr[face];
			rAPtr[u] -= rDPtr[u] * lowerPtr[face] * rAPtr[lPtr[face]];
		}

		label nFacesM1 = nFaces - 1;
		for (label face = nFacesM1; face >= 0; face--)
		{
			label l = lPtr[face];
			rAPtr[l] -= rDPtr[l] * upperPtr[face] * rAPtr[uPtr[face]];
		}

		psi += rA;
	}
}


// ************************************************************************* //