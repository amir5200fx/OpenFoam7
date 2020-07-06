#include <PBiCGStab.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(PBiCGStab, 0);

	lduMatrix::solver::addsymMatrixConstructorToTable<PBiCGStab>
		addPBiCGStabSymMatrixConstructorToTable_;

	lduMatrix::solver::addasymMatrixConstructorToTable<PBiCGStab>
		addPBiCGStabAsymMatrixConstructorToTable_;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::PBiCGStab::PBiCGStab
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

tnbLib::solverPerformance tnbLib::PBiCGStab::solve
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

	scalarField yA(nCells);
	scalar* __restrict yAPtr = yA.begin();

	// --- Calculate A.psi
	matrix_.Amul(yA, psi, interfaceBouCoeffs_, interfaces_, cmpt);

	// --- Calculate initial residual field
	scalarField rA(source - yA);
	scalar* __restrict rAPtr = rA.begin();

	// --- Calculate normalisation factor
	const scalar normFactor = this->normFactor(psi, source, yA, pA);

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
		scalarField AyA(nCells);
		scalar* __restrict AyAPtr = AyA.begin();

		scalarField sA(nCells);
		scalar* __restrict sAPtr = sA.begin();

		scalarField zA(nCells);
		scalar* __restrict zAPtr = zA.begin();

		scalarField tA(nCells);
		scalar* __restrict tAPtr = tA.begin();

		// --- Store initial residual
		const scalarField rA0(rA);

		// --- Initial values not used
		scalar rA0rA = 0;
		scalar alpha = 0;
		scalar omega = 0;

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
			// --- Store previous rA0rA
			const scalar rA0rAold = rA0rA;

			rA0rA = gSumProd(rA0, rA, matrix().mesh().comm());

			// --- Test for singularity
			if (solverPerf.checkSingularity(mag(rA0rA)))
			{
				break;
			}

			// --- Update pA
			if (solverPerf.nIterations() == 0)
			{
				for (label cell = 0; cell < nCells; cell++)
				{
					pAPtr[cell] = rAPtr[cell];
				}
			}
			else
			{
				// --- Test for singularity
				if (solverPerf.checkSingularity(mag(omega)))
				{
					break;
				}

				const scalar beta = (rA0rA / rA0rAold)*(alpha / omega);

				for (label cell = 0; cell < nCells; cell++)
				{
					pAPtr[cell] =
						rAPtr[cell] + beta * (pAPtr[cell] - omega * AyAPtr[cell]);
				}
			}

			// --- Precondition pA
			preconPtr->precondition(yA, pA, cmpt);

			// --- Calculate AyA
			matrix_.Amul(AyA, yA, interfaceBouCoeffs_, interfaces_, cmpt);

			const scalar rA0AyA = gSumProd(rA0, AyA, matrix().mesh().comm());

			alpha = rA0rA / rA0AyA;

			// --- Calculate sA
			for (label cell = 0; cell < nCells; cell++)
			{
				sAPtr[cell] = rAPtr[cell] - alpha * AyAPtr[cell];
			}

			// --- Test sA for convergence
			solverPerf.finalResidual() =
				gSumMag(sA, matrix().mesh().comm()) / normFactor;

			if (solverPerf.checkConvergence(tolerance_, relTol_))
			{
				for (label cell = 0; cell < nCells; cell++)
				{
					psiPtr[cell] += alpha * yAPtr[cell];
				}

				solverPerf.nIterations()++;

				return solverPerf;
			}

			// --- Precondition sA
			preconPtr->precondition(zA, sA, cmpt);

			// --- Calculate tA
			matrix_.Amul(tA, zA, interfaceBouCoeffs_, interfaces_, cmpt);

			const scalar tAtA = gSumSqr(tA, matrix().mesh().comm());

			// --- Calculate omega from tA and sA
			//     (cheaper than using zA with preconditioned tA)
			omega = gSumProd(tA, sA, matrix().mesh().comm()) / tAtA;

			// --- Update solution and residual
			for (label cell = 0; cell < nCells; cell++)
			{
				psiPtr[cell] += alpha * yAPtr[cell] + omega * zAPtr[cell];
				rAPtr[cell] = sAPtr[cell] - omega * tAPtr[cell];
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