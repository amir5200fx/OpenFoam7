#include <PBiCG.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(PBiCG, 0);

	lduMatrix::solver::addasymMatrixConstructorToTable<PBiCG>
		addPBiCGAsymMatrixConstructorToTable_;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::PBiCG::PBiCG
(
	const word& fieldName,
	const lduMatrix& matrix,
	const FieldField<Field, scalar>& interfaceBouCoeffs,
	const FieldField<Field, scalar>& interfaceIntCoeffs,
	const lduInterfaceFieldPtrsList& interfaces,
	const dictionary& solverControls
)
	:
	lduMatrix::solver
	(
		fieldName,
		matrix,
		interfaceBouCoeffs,
		interfaceIntCoeffs,
		interfaces,
		solverControls
	)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::solverPerformance tnbLib::PBiCG::solve
(
	scalarField& psi,
	const scalarField& source,
	const direction cmpt
) const
{
	// --- Setup class containing solver performance data
	solverPerformance solverPerf
	(
		lduMatrix::preconditioner::getName(controlDict_) + typeName,
		fieldName_
	);

	const label nCells = psi.size();

	scalar* __restrict psiPtr = psi.begin();

	scalarField pA(nCells);
	scalar* __restrict pAPtr = pA.begin();

	scalarField wA(nCells);
	scalar* __restrict wAPtr = wA.begin();

	// --- Calculate A.psi
	matrix_.Amul(wA, psi, interfaceBouCoeffs_, interfaces_, cmpt);

	// --- Calculate initial residual field
	scalarField rA(source - wA);
	scalar* __restrict rAPtr = rA.begin();

	// --- Calculate normalisation factor
	const scalar normFactor = this->normFactor(psi, source, wA, pA);

	if (lduMatrix::debug >= 2)
	{
		Info << "   Normalisation factor = " << normFactor << endl;
	}

	// --- Calculate normalised residual norm
	solverPerf.initialResidual() =
		gSumMag(rA, matrix().mesh().comm())
		/ normFactor;
	solverPerf.finalResidual() = solverPerf.initialResidual();

	// --- Check convergence, solve if not converged
	if
		(
			minIter_ > 0
			|| !solverPerf.checkConvergence(tolerance_, relTol_)
			)
	{
		scalarField pT(nCells, 0);
		scalar* __restrict pTPtr = pT.begin();

		scalarField wT(nCells);
		scalar* __restrict wTPtr = wT.begin();

		// --- Calculate T.psi
		matrix_.Tmul(wT, psi, interfaceIntCoeffs_, interfaces_, cmpt);

		// --- Calculate initial transpose residual field
		scalarField rT(source - wT);
		scalar* __restrict rTPtr = rT.begin();

		// --- Initial value not used
		scalar wArT = 0;

		// --- Select and construct the preconditioner
		autoPtr<lduMatrix::preconditioner> preconPtr =
			lduMatrix::preconditioner::New
			(
				*this,
				controlDict_
			);

		// --- Solver iteration
		do
		{
			// --- Store previous wArT
			const scalar wArTold = wArT;

			// --- Precondition residuals
			preconPtr->precondition(wA, rA, cmpt);
			preconPtr->preconditionT(wT, rT, cmpt);

			// --- Update search directions:
			wArT = gSumProd(wA, rT, matrix().mesh().comm());

			if (solverPerf.nIterations() == 0)
			{
				for (label cell = 0; cell < nCells; cell++)
				{
					pAPtr[cell] = wAPtr[cell];
					pTPtr[cell] = wTPtr[cell];
				}
			}
			else
			{
				const scalar beta = wArT / wArTold;

				for (label cell = 0; cell < nCells; cell++)
				{
					pAPtr[cell] = wAPtr[cell] + beta * pAPtr[cell];
					pTPtr[cell] = wTPtr[cell] + beta * pTPtr[cell];
				}
			}


			// --- Update preconditioned residuals
			matrix_.Amul(wA, pA, interfaceBouCoeffs_, interfaces_, cmpt);
			matrix_.Tmul(wT, pT, interfaceIntCoeffs_, interfaces_, cmpt);

			const scalar wApT = gSumProd(wA, pT, matrix().mesh().comm());

			// --- Test for singularity
			if (solverPerf.checkSingularity(mag(wApT) / normFactor))
			{
				break;
			}


			// --- Update solution and residual:

			const scalar alpha = wArT / wApT;

			for (label cell = 0; cell < nCells; cell++)
			{
				psiPtr[cell] += alpha * pAPtr[cell];
				rAPtr[cell] -= alpha * wAPtr[cell];
				rTPtr[cell] -= alpha * wTPtr[cell];
			}

			solverPerf.finalResidual() =
				gSumMag(rA, matrix().mesh().comm())
				/ normFactor;
		} while
			(
			(
				++solverPerf.nIterations() < maxIter_
				&& !solverPerf.checkConvergence(tolerance_, relTol_)
				)
				|| solverPerf.nIterations() < minIter_
				);
	}

	// Recommend PBiCGStab if PBiCG fails to converge
	if (solverPerf.nIterations() > max(defaultMaxIter_, maxIter_))
	{
		FatalErrorInFunction
			<< "PBiCG has failed to converge within the maximum number"
			" of iterations " << max(defaultMaxIter_, maxIter_) << nl
			<< "    Please try the more robust PBiCGStab solver."
			<< exit(FatalError);
	}

	return solverPerf;
}


// ************************************************************************* //