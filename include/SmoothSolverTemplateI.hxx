#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type, class DType, class LUType>
tnbLib::SmoothSolver<Type, DType, LUType>::SmoothSolver
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
	),
	nSweeps_(1)
{
	readControls();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type, class DType, class LUType>
void tnbLib::SmoothSolver<Type, DType, LUType>::readControls()
{
	LduMatrix<Type, DType, LUType>::solver::readControls();
	this->readControl(this->controlDict_, nSweeps_, "nSweeps");
}


template<class Type, class DType, class LUType>
tnbLib::SolverPerformance<Type>
tnbLib::SmoothSolver<Type, DType, LUType>::solve(Field<Type>& psi) const
{
	// --- Setup class containing solver performance data
	SolverPerformance<Type> solverPerf
	(
		typeName,
		this->fieldName_
	);

	label nIter = 0;

	// If the nSweeps_ is negative do a fixed number of sweeps
	if (nSweeps_ < 0)
	{
		autoPtr<typename LduMatrix<Type, DType, LUType>::smoother>
			smootherPtr = LduMatrix<Type, DType, LUType>::smoother::New
			(
				this->fieldName_,
				this->matrix_,
				this->controlDict_
			);

		smootherPtr->smooth(psi, -nSweeps_);

		nIter -= nSweeps_;
	}
	else
	{
		Type normFactor = Zero;

		{
			Field<Type> Apsi(psi.size());
			Field<Type> temp(psi.size());

			// Calculate A.psi
			this->matrix_.Amul(Apsi, psi);

			// Calculate normalisation factor
			normFactor = this->normFactor(psi, Apsi, temp);

			// Calculate residual magnitude
			solverPerf.initialResidual() = cmptDivide
			(
				gSumCmptMag(this->matrix_.source() - Apsi),
				normFactor
			);
			solverPerf.finalResidual() = solverPerf.initialResidual();
		}

		if (LduMatrix<Type, DType, LUType>::debug >= 2)
		{
			Info << "   Normalisation factor = " << normFactor << endl;
		}


		// Check convergence, solve if not converged
		if
			(
				this->minIter_ > 0
				|| !solverPerf.checkConvergence(this->tolerance_, this->relTol_)
				)
		{
			autoPtr<typename LduMatrix<Type, DType, LUType>::smoother>
				smootherPtr = LduMatrix<Type, DType, LUType>::smoother::New
				(
					this->fieldName_,
					this->matrix_,
					this->controlDict_
				);

			// Smoothing loop
			do
			{
				smootherPtr->smooth
				(
					psi,
					nSweeps_
				);

				// Calculate the residual to check convergence
				solverPerf.finalResidual() = cmptDivide
				(
					gSumCmptMag(this->matrix_.residual(psi)),
					normFactor
				);
			} while
				(
				(
					(nIter += nSweeps_) < this->maxIter_
					&& !solverPerf.checkConvergence(this->tolerance_, this->relTol_)
					)
					|| nIter < this->minIter_
					);
		}
	}

	solverPerf.nIterations() =
		pTraits<typename pTraits<Type>::labelType>::one*nIter;

	return solverPerf;
}


// ************************************************************************* //