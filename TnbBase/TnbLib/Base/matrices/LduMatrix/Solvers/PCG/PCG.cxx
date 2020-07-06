#include <PCG.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(PCG, 0);

	lduMatrix::solver::addsymMatrixConstructorToTable<PCG>
		addPCGSymMatrixConstructorToTable_;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::PCG::PCG
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

tnbLib::solverPerformance tnbLib::PCG::solve
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

	label nCells = psi.size();

	scalar* __restrict psiPtr = psi.begin();

	scalarField pA(nCells);
	scalar* __restrict pAPtr = pA.begin();

	scalarField wA(nCells);
	scalar* __restrict wAPtr = wA.begin();

	scalar wArA = solverPerf.great_;
	scalar wArAold = wArA;

	// --- Calculate A.psi
	matrix_.Amul(wA, psi, interfaceBouCoeffs_, interfaces_, cmpt);

	// --- Calculate initial residual field
	scalarField rA(source - wA);
	scalar* __restrict rAPtr = rA.begin();

	// --- Calculate normalisation factor
	scalar normFactor = this->normFactor(psi, source, wA, pA);

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
			// --- Store previous wArA
			wArAold = wArA;

			// --- Precondition residual
			preconPtr->precondition(wA, rA, cmpt);

			// --- Update search directions:
			wArA = gSumProd(wA, rA, matrix().mesh().comm());

			if (solverPerf.nIterations() == 0)
			{
				for (label cell = 0; cell < nCells; cell++)
				{
					pAPtr[cell] = wAPtr[cell];
				}
			}
			else
			{
				scalar beta = wArA / wArAold;

				for (label cell = 0; cell < nCells; cell++)
				{
					pAPtr[cell] = wAPtr[cell] + beta * pAPtr[cell];
				}
			}


			// --- Update preconditioned residual
			matrix_.Amul(wA, pA, interfaceBouCoeffs_, interfaces_, cmpt);

			scalar wApA = gSumProd(wA, pA, matrix().mesh().comm());


			// --- Test for singularity
			if (solverPerf.checkSingularity(mag(wApA) / normFactor)) break;


			// --- Update solution and residual:

			scalar alpha = wArA / wApA;

			for (label cell = 0; cell < nCells; cell++)
			{
				psiPtr[cell] += alpha * pAPtr[cell];
				rAPtr[cell] -= alpha * wAPtr[cell];
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

	return solverPerf;
}


// ************************************************************************* //