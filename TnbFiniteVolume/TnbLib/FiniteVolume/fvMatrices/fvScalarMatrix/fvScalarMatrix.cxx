#include <fvScalarMatrix.hxx>

#include <Residuals.hxx>
#include <extrapolatedCalculatedFvPatchFields.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<>
void tnbLib::fvMatrix<tnbLib::scalar>::setComponentReference
(
	const label patchi,
	const label facei,
	const direction,
	const scalar value
)
{
	if (psi_.needReference())
	{
		if (Pstream::master())
		{
			internalCoeffs_[patchi][facei] +=
				diag()[psi_.mesh().boundary()[patchi].faceCells()[facei]];

			boundaryCoeffs_[patchi][facei] +=
				diag()[psi_.mesh().boundary()[patchi].faceCells()[facei]]
				* value;
		}
	}
}


template<>
tnbLib::autoPtr<tnbLib::fvMatrix<tnbLib::scalar>::fvSolver>
tnbLib::fvMatrix<tnbLib::scalar>::solver
(
	const dictionary& solverControls
)
{
	if (debug)
	{
		Info.masterStream(this->mesh().comm())
			<< "fvMatrix<scalar>::solver(const dictionary& solverControls) : "
			"solver for fvMatrix<scalar>"
			<< endl;
	}

	scalarField saveDiag(diag());
	addBoundaryDiag(diag(), 0);

	autoPtr<fvMatrix<scalar>::fvSolver> solverPtr
	(
		new fvMatrix<scalar>::fvSolver
		(
			*this,
			lduMatrix::solver::New
			(
				psi_.name(),
				*this,
				boundaryCoeffs_,
				internalCoeffs_,
				psi_.boundaryField().scalarInterfaces(),
				solverControls
			)
		)
	);

	diag() = saveDiag;

	return solverPtr;
}


template<>
tnbLib::solverPerformance tnbLib::fvMatrix<tnbLib::scalar>::fvSolver::solve
(
	const dictionary& solverControls
)
{
	GeometricField<scalar, fvPatchField, volMesh>& psi =
		const_cast<GeometricField<scalar, fvPatchField, volMesh>&>
		(fvMat_.psi());

	scalarField saveDiag(fvMat_.diag());
	fvMat_.addBoundaryDiag(fvMat_.diag(), 0);

	scalarField totalSource(fvMat_.source());
	fvMat_.addBoundarySource(totalSource, false);

	// Assign new solver controls
	solver_->read(solverControls);

	solverPerformance solverPerf = solver_->solve
	(
		psi.primitiveFieldRef(),
		totalSource
	);

	if (solverPerformance::debug)
	{
		solverPerf.print(Info.masterStream(fvMat_.mesh().comm()));
	}

	fvMat_.diag() = saveDiag;

	psi.correctBoundaryConditions();

	Residuals<scalar>::append(psi.mesh(), solverPerf);

	return solverPerf;
}


template<>
tnbLib::solverPerformance tnbLib::fvMatrix<tnbLib::scalar>::solveSegregated
(
	const dictionary& solverControls
)
{
	if (debug)
	{
		Info.masterStream(this->mesh().comm())
			<< "fvMatrix<scalar>::solveSegregated"
			"(const dictionary& solverControls) : "
			"solving fvMatrix<scalar>"
			<< endl;
	}

	GeometricField<scalar, fvPatchField, volMesh>& psi =
		const_cast<GeometricField<scalar, fvPatchField, volMesh>&>(psi_);

	scalarField saveDiag(diag());
	addBoundaryDiag(diag(), 0);

	scalarField totalSource(source_);
	addBoundarySource(totalSource, false);

	// Solver call
	solverPerformance solverPerf = lduMatrix::solver::New
	(
		psi.name(),
		*this,
		boundaryCoeffs_,
		internalCoeffs_,
		psi_.boundaryField().scalarInterfaces(),
		solverControls
	)->solve(psi.primitiveFieldRef(), totalSource);

	if (solverPerformance::debug)
	{
		solverPerf.print(Info.masterStream(mesh().comm()));
	}

	diag() = saveDiag;

	psi.correctBoundaryConditions();

	Residuals<scalar>::append(psi.mesh(), solverPerf);

	return solverPerf;
}


template<>
tnbLib::tmp<tnbLib::scalarField> tnbLib::fvMatrix<tnbLib::scalar>::residual() const
{
	scalarField boundaryDiag(psi_.size(), 0.0);
	addBoundaryDiag(boundaryDiag, 0);

	tmp<scalarField> tres
	(
		lduMatrix::residual
		(
			psi_.primitiveField(),
			source_ - boundaryDiag * psi_.primitiveField(),
			boundaryCoeffs_,
			psi_.boundaryField().scalarInterfaces(),
			0
		)
	);

	addBoundarySource(tres.ref());

	return tres;
}


template<>
tnbLib::tmp<tnbLib::volScalarField> tnbLib::fvMatrix<tnbLib::scalar>::H() const
{
	tmp<volScalarField> tHphi
	(
		volScalarField::New
		(
			"H(" + psi_.name() + ')',
			psi_.mesh(),
			dimensions_ / dimVol,
			extrapolatedCalculatedFvPatchScalarField::typeName
		)
	);
	volScalarField& Hphi = tHphi.ref();

	Hphi.primitiveFieldRef() = (lduMatrix::H(psi_.primitiveField()) + source_);
	addBoundarySource(Hphi.primitiveFieldRef());

	Hphi.primitiveFieldRef() /= psi_.mesh().V();
	Hphi.correctBoundaryConditions();

	return tHphi;
}


template<>
tnbLib::tmp<tnbLib::volScalarField> tnbLib::fvMatrix<tnbLib::scalar>::H1() const
{
	tmp<volScalarField> tH1
	(
		volScalarField::New
		(
			"H(1)",
			psi_.mesh(),
			dimensions_ / (dimVol*psi_.dimensions()),
			extrapolatedCalculatedFvPatchScalarField::typeName
		)
	);
	volScalarField& H1_ = tH1.ref();

	H1_.primitiveFieldRef() = lduMatrix::H1();
	// addBoundarySource(Hphi.primitiveField());

	H1_.primitiveFieldRef() /= psi_.mesh().V();
	H1_.correctBoundaryConditions();

	return tH1;
}


// ************************************************************************* //