#include <smoothSolver.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(smoothSolver, 0);

	lduMatrix::solver::addsymMatrixConstructorToTable<smoothSolver>
		addsmoothSolverSymMatrixConstructorToTable_;

	lduMatrix::solver::addasymMatrixConstructorToTable<smoothSolver>
		addsmoothSolverAsymMatrixConstructorToTable_;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::smoothSolver::smoothSolver
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
{
	readControls();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::smoothSolver::readControls()
{
	lduMatrix::solver::readControls();
	nSweeps_ = controlDict_.lookupOrDefault<label>("nSweeps", 1);
}


tnbLib::solverPerformance tnbLib::smoothSolver::solve
(
	scalarField& psi,
	const scalarField& source,
	const direction cmpt
) const
{
	// Setup class containing solver performance data
	solverPerformance solverPerf(typeName, fieldName_);

	// If the nSweeps_ is negative do a fixed number of sweeps
	if (nSweeps_ < 0)
	{
		autoPtr<lduMatrix::smoother> smootherPtr = lduMatrix::smoother::New
		(
			fieldName_,
			matrix_,
			interfaceBouCoeffs_,
			interfaceIntCoeffs_,
			interfaces_,
			controlDict_
		);

		smootherPtr->smooth
		(
			psi,
			source,
			cmpt,
			-nSweeps_
		);

		solverPerf.nIterations() -= nSweeps_;
	}
	else
	{
		scalar normFactor = 0;

		{
			scalarField Apsi(psi.size());
			scalarField temp(psi.size());

			// Calculate A.psi
			matrix_.Amul(Apsi, psi, interfaceBouCoeffs_, interfaces_, cmpt);

			// Calculate normalisation factor
			normFactor = this->normFactor(psi, source, Apsi, temp);

			// Calculate residual magnitude
			solverPerf.initialResidual() = gSumMag
			(
				(source - Apsi)(),
				matrix().mesh().comm()
			) / normFactor;
			solverPerf.finalResidual() = solverPerf.initialResidual();
		}

		if (lduMatrix::debug >= 2)
		{
			Info.masterStream(matrix().mesh().comm())
				<< "   Normalisation factor = " << normFactor << endl;
		}


		// Check convergence, solve if not converged
		if
			(
				minIter_ > 0
				|| !solverPerf.checkConvergence(tolerance_, relTol_)
				)
		{
			autoPtr<lduMatrix::smoother> smootherPtr = lduMatrix::smoother::New
			(
				fieldName_,
				matrix_,
				interfaceBouCoeffs_,
				interfaceIntCoeffs_,
				interfaces_,
				controlDict_
			);

			// Smoothing loop
			do
			{
				smootherPtr->smooth
				(
					psi,
					source,
					cmpt,
					nSweeps_
				);

				// Calculate the residual to check convergence
				solverPerf.finalResidual() = gSumMag
				(
					matrix_.residual
					(
						psi,
						source,
						interfaceBouCoeffs_,
						interfaces_,
						cmpt
					)(),
					matrix().mesh().comm()
				) / normFactor;
			} while
				(
				(
					(solverPerf.nIterations() += nSweeps_) < maxIter_
					&& !solverPerf.checkConvergence(tolerance_, relTol_)
					)
					|| solverPerf.nIterations() < minIter_
					);
		}
	}

	return solverPerf;
}


// ************************************************************************* //