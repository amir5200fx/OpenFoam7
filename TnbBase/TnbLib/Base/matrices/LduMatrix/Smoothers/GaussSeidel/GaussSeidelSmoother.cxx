#include <GaussSeidelSmoother.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(GaussSeidelSmoother, 0);

	lduMatrix::smoother::addsymMatrixConstructorToTable<GaussSeidelSmoother>
		addGaussSeidelSmootherSymMatrixConstructorToTable_;

	lduMatrix::smoother::addasymMatrixConstructorToTable<GaussSeidelSmoother>
		addGaussSeidelSmootherAsymMatrixConstructorToTable_;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::GaussSeidelSmoother::GaussSeidelSmoother
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
	)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::GaussSeidelSmoother::smooth
(
	const word& fieldName_,
	scalarField& psi,
	const lduMatrix& matrix_,
	const scalarField& source,
	const FieldField<Field, scalar>& interfaceBouCoeffs_,
	const lduInterfaceFieldPtrsList& interfaces_,
	const direction cmpt,
	const label nSweeps
)
{
	scalar* __restrict psiPtr = psi.begin();

	const label nCells = psi.size();

	scalarField bPrime(nCells);
	scalar* __restrict bPrimePtr = bPrime.begin();

	const scalar* const __restrict diagPtr = matrix_.diag().begin();
	const scalar* const __restrict upperPtr =
		matrix_.upper().begin();
	const scalar* const __restrict lowerPtr =
		matrix_.lower().begin();

	const label* const __restrict uPtr =
		matrix_.lduAddr().upperAddr().begin();

	const label* const __restrict ownStartPtr =
		matrix_.lduAddr().ownerStartAddr().begin();


	// Parallel boundary initialisation.  The parallel boundary is treated
	// as an effective jacobi interface in the boundary.
	// Note: there is a change of sign in the coupled
	// interface update.  The reason for this is that the
	// internal coefficients are all located at the l.h.s. of
	// the matrix whereas the "implicit" coefficients on the
	// coupled boundaries are all created as if the
	// coefficient contribution is of a source-kind (i.e. they
	// have a sign as if they are on the r.h.s. of the matrix.
	// To compensate for this, it is necessary to turn the
	// sign of the contribution.

	FieldField<Field, scalar>& mBouCoeffs =
		const_cast<FieldField<Field, scalar>&>
		(
			interfaceBouCoeffs_
			);

	forAll(mBouCoeffs, patchi)
	{
		if (interfaces_.set(patchi))
		{
			mBouCoeffs[patchi].negate();
		}
	}


	for (label sweep = 0; sweep < nSweeps; sweep++)
	{
		bPrime = source;

		matrix_.initMatrixInterfaces
		(
			mBouCoeffs,
			interfaces_,
			psi,
			bPrime,
			cmpt
		);

		matrix_.updateMatrixInterfaces
		(
			mBouCoeffs,
			interfaces_,
			psi,
			bPrime,
			cmpt
		);

		scalar psii;
		label fStart;
		label fEnd = ownStartPtr[0];

		for (label celli = 0; celli < nCells; celli++)
		{
			// Start and end of this row
			fStart = fEnd;
			fEnd = ownStartPtr[celli + 1];

			// Get the accumulated neighbour side
			psii = bPrimePtr[celli];

			// Accumulate the owner product side
			for (label facei = fStart; facei < fEnd; facei++)
			{
				psii -= upperPtr[facei] * psiPtr[uPtr[facei]];
			}

			// Finish psi for this cell
			psii /= diagPtr[celli];

			// Distribute the neighbour side using psi for this cell
			for (label facei = fStart; facei < fEnd; facei++)
			{
				bPrimePtr[uPtr[facei]] -= lowerPtr[facei] * psii;
			}

			psiPtr[celli] = psii;
		}
	}

	// Restore interfaceBouCoeffs_
	forAll(mBouCoeffs, patchi)
	{
		if (interfaces_.set(patchi))
		{
			mBouCoeffs[patchi].negate();
		}
	}
}


void tnbLib::GaussSeidelSmoother::smooth
(
	scalarField& psi,
	const scalarField& source,
	const direction cmpt,
	const label nSweeps
) const
{
	smooth
	(
		fieldName_,
		psi,
		matrix_,
		source,
		interfaceBouCoeffs_,
		interfaces_,
		cmpt,
		nSweeps
	);
}


// ************************************************************************* //