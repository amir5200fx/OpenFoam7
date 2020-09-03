#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type, class DType, class LUType>
tnbLib::PBiCICG<Type, DType, LUType>::PBiCICG
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
tnbLib::SolverPerformance<Type>
tnbLib::PBiCICG<Type, DType, LUType>::solve(Field<Type>& psi) const
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

	Field<Type> pT(nCells, Zero);
	Type* __restrict pTPtr = pT.begin();

	Field<Type> wA(nCells);
	Type* __restrict wAPtr = wA.begin();

	Field<Type> wT(nCells);
	Type* __restrict wTPtr = wT.begin();

	Type wArT = solverPerf.great_*pTraits<Type>::one;
	Type wArTold = wArT;

	// --- Calculate A.psi and T.psi
	this->matrix_.Amul(wA, psi);
	this->matrix_.Tmul(wT, psi);

	// --- Calculate initial residual and transpose residual fields
	Field<Type> rA(this->matrix_.source() - wA);
	Field<Type> rT(this->matrix_.source() - wT);
	Type* __restrict rAPtr = rA.begin();
	Type* __restrict rTPtr = rT.begin();

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
	if (!solverPerf.checkConvergence(this->tolerance_, this->relTol_))
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
			// --- Store previous wArT
			wArTold = wArT;

			// --- Precondition residuals
			preconPtr->precondition(wA, rA);
			preconPtr->preconditionT(wT, rT);

			// --- Update search directions:
			wArT = gSumCmptProd(wA, rT);

			if (nIter == 0)
			{
				for (label cell = 0; cell < nCells; cell++)
				{
					pAPtr[cell] = wAPtr[cell];
					pTPtr[cell] = wTPtr[cell];
				}
			}
			else
			{
				Type beta = cmptDivide
				(
					wArT,
					stabilise(wArTold, solverPerf.vsmall_)
				);

				for (label cell = 0; cell < nCells; cell++)
				{
					pAPtr[cell] = wAPtr[cell] + cmptMultiply(beta, pAPtr[cell]);
					pTPtr[cell] = wTPtr[cell] + cmptMultiply(beta, pTPtr[cell]);
				}
			}


			// --- Update preconditioned residuals
			this->matrix_.Amul(wA, pA);
			this->matrix_.Tmul(wT, pT);

			Type wApT = gSumCmptProd(wA, pT);

			// --- Test for singularity
			if
				(
					solverPerf.checkSingularity
					(
						cmptDivide(cmptMag(wApT), normFactor)
					)
					)
			{
				break;
			}


			// --- Update solution and residual:

			Type alpha = cmptDivide
			(
				wArT,
				stabilise(wApT, solverPerf.vsmall_)
			);

			for (label cell = 0; cell < nCells; cell++)
			{
				psiPtr[cell] += cmptMultiply(alpha, pAPtr[cell]);
				rAPtr[cell] -= cmptMultiply(alpha, wAPtr[cell]);
				rTPtr[cell] -= cmptMultiply(alpha, wTPtr[cell]);
			}

			solverPerf.finalResidual() =
				cmptDivide(gSumCmptMag(rA), normFactor);

		} while
			(
				nIter++ < this->maxIter_
				&& !(solverPerf.checkConvergence(this->tolerance_, this->relTol_))
				);
	}

	solverPerf.nIterations() =
		pTraits<typename pTraits<Type>::labelType>::one*nIter;

	return solverPerf;
}


// ************************************************************************* //