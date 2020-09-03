#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type, class DType, class LUType>
tnbLib::TGaussSeidelSmoother<Type, DType, LUType>::TGaussSeidelSmoother
(
	const word& fieldName,
	const LduMatrix<Type, DType, LUType>& matrix
)
	:
	LduMatrix<Type, DType, LUType>::smoother
	(
		fieldName,
		matrix
	),
	rD_(matrix.diag().size())
{
	const label nCells = matrix.diag().size();
	const DType* const __restrict diagPtr = matrix.diag().begin();
	DType* __restrict rDPtr = rD_.begin();

	for (label celli = 0; celli < nCells; celli++)
	{
		rDPtr[celli] = inv(diagPtr[celli]);
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type, class DType, class LUType>
void tnbLib::TGaussSeidelSmoother<Type, DType, LUType>::smooth
(
	const word& fieldName_,
	Field<Type>& psi,
	const LduMatrix<Type, DType, LUType>& matrix_,
	const Field<DType>& rD_,
	const label nSweeps
)
{
	Type* __restrict psiPtr = psi.begin();

	const label nCells = psi.size();

	Field<Type> bPrime(nCells);
	Type* __restrict bPrimePtr = bPrime.begin();

	const DType* const __restrict rDPtr = rD_.begin();

	const LUType* const __restrict upperPtr =
		matrix_.upper().begin();

	const LUType* const __restrict lowerPtr =
		matrix_.lower().begin();

	const label* const __restrict uPtr =
		matrix_.lduAddr().upperAddr().begin();

	const label* const __restrict ownStartPtr =
		matrix_.lduAddr().ownerStartAddr().begin();


	// Parallel boundary initialisation.  The parallel boundary is treated
	// as an effective jacobi interface in the boundary.
	// Note: there is a change of sign in the coupled
	// interface update to add the contibution to the r.h.s.

	FieldField<Field, LUType> mBouCoeffs(matrix_.interfacesUpper().size());

	forAll(mBouCoeffs, patchi)
	{
		if (matrix_.interfaces().set(patchi))
		{
			mBouCoeffs.set(patchi, -matrix_.interfacesUpper()[patchi]);
		}
	}

	for (label sweep = 0; sweep < nSweeps; sweep++)
	{
		bPrime = matrix_.source();

		matrix_.initMatrixInterfaces
		(
			mBouCoeffs,
			psi,
			bPrime
		);

		matrix_.updateMatrixInterfaces
		(
			mBouCoeffs,
			psi,
			bPrime
		);

		Type curPsi;
		label fStart;
		label fEnd = ownStartPtr[0];

		for (label celli = 0; celli < nCells; celli++)
		{
			// Start and end of this row
			fStart = fEnd;
			fEnd = ownStartPtr[celli + 1];

			// Get the accumulated neighbour side
			curPsi = bPrimePtr[celli];

			// Accumulate the owner product side
			for (label curFace = fStart; curFace < fEnd; curFace++)
			{
				curPsi -= dot(upperPtr[curFace], psiPtr[uPtr[curFace]]);
			}

			// Finish current psi
			curPsi = dot(rDPtr[celli], curPsi);

			// Distribute the neighbour side using current psi
			for (label curFace = fStart; curFace < fEnd; curFace++)
			{
				bPrimePtr[uPtr[curFace]] -= dot(lowerPtr[curFace], curPsi);
			}

			psiPtr[celli] = curPsi;
		}
	}
}


template<class Type, class DType, class LUType>
void tnbLib::TGaussSeidelSmoother<Type, DType, LUType>::smooth
(
	Field<Type>& psi,
	const label nSweeps
) const
{
	smooth(this->fieldName_, psi, this->matrix_, rD_, nSweeps);
}


// ************************************************************************* //