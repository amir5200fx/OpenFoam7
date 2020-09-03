#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type, class DType, class LUType>
tnbLib::PCICG<Type, DType, LUType>::PCICG
(
	const word& fieldName,
	const LduMatrix<Type, DType, LUType>& matrix,
	const dictionary& solverDict
)
	:
	LduMatrix<Type, DType, LUType>::solver
	(
		fieldName,
		matrix,
		solverDict
	)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type, class DType, class LUType>
typename tnbLib::SolverPerformance<Type>
tnbLib::PCICG<Type, DType, LUType>::solve(Field<Type>& psi) const
{
	word preconditionerName(this->controlDict_.lookup("preconditioner"));

	// --- Setup class containing solver performance data
	SolverPerformance<Type> solverPerf
	(
		preconditionerName + typeName,
		this->fieldName_
	);

	label nIter = 0;

	label nCells = psi.size();

	Type* __restrict psiPtr = psi.begin();

	Field<Type> pA(nCells);
	Type* __restrict pAPtr = pA.begin();

	Field<Type> wA(nCells);
	Type* __restrict wAPtr = wA.begin();

	Type wArA = solverPerf.great_*pTraits<Type>::one;
	Type wArAold = wArA;

	// --- Calculate A.psi
	this->matrix_.Amul(wA, psi);

	// --- Calculate initial residual field
	Field<Type> rA(this->matrix_.source() - wA);
	Type* __restrict rAPtr = rA.begin();

	// --- Calculate normalisation factor
	Type normFactor = this->normFactor(psi, wA, pA);

	if (LduMatrix<Type, DType, LUType>::debug >= 2)
	{
		Info << "   Normalisation factor = " << normFactor << endl;
	}

	// --- Calculate normalised residual norm
	solverPerf.initialResidual() = cmptDivide(gSumCmptMag(rA), normFactor);
	solverPerf.finalResidual() = solverPerf.initialResidual();

	// --- Check convergence, solve if not converged
	if
		(
			this->minIter_ > 0
			|| !solverPerf.checkConvergence(this->tolerance_, this->relTol_)
			)
	{
		// --- Select and construct the preconditioner
		autoPtr<typename LduMatrix<Type, DType, LUType>::preconditioner>
			preconPtr = LduMatrix<Type, DType, LUType>::preconditioner::New
			(
				*this,
				this->controlDict_
			);

		// --- Solver iteration
		do
		{
			// --- Store previous wArA
			wArAold = wArA;

			// --- Precondition residual
			preconPtr->precondition(wA, rA);

			// --- Update search directions:
			wArA = gSumCmptProd(wA, rA);

			if (nIter == 0)
			{
				for (label cell = 0; cell < nCells; cell++)
				{
					pAPtr[cell] = wAPtr[cell];
				}
			}
			else
			{
				Type beta = cmptDivide
				(
					wArA,
					stabilise(wArAold, solverPerf.vsmall_)
				);

				for (label cell = 0; cell < nCells; cell++)
				{
					pAPtr[cell] = wAPtr[cell] + cmptMultiply(beta, pAPtr[cell]);
				}
			}


			// --- Update preconditioned residual
			this->matrix_.Amul(wA, pA);

			Type wApA = gSumCmptProd(wA, pA);


			// --- Test for singularity
			if
				(
					solverPerf.checkSingularity
					(
						cmptDivide(cmptMag(wApA), normFactor)
					)
					)
			{
				break;
			}


			// --- Update solution and residual:

			Type alpha = cmptDivide
			(
				wArA,
				stabilise(wApA, solverPerf.vsmall_)
			);

			for (label cell = 0; cell < nCells; cell++)
			{
				psiPtr[cell] += cmptMultiply(alpha, pAPtr[cell]);
				rAPtr[cell] -= cmptMultiply(alpha, wAPtr[cell]);
			}

			solverPerf.finalResidual() =
				cmptDivide(gSumCmptMag(rA), normFactor);

		} while
			(
			(
				nIter++ < this->maxIter_
				&& !solverPerf.checkConvergence(this->tolerance_, this->relTol_)
				)
				|| nIter < this->minIter_
				);
	}

	solverPerf.nIterations() =
		pTraits<typename pTraits<Type>::labelType>::one*nIter;

	return solverPerf;
}


// ************************************************************************* //