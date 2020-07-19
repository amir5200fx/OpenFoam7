#include <fvMatrix.hxx>

#include <LduMatrixTemplate.hxx>
#include <Residuals.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::fvMatrix<Type>::setComponentReference
(
	const label patchi,
	const label facei,
	const direction cmpt,
	const scalar value
)
{
	if (psi_.needReference())
	{
		if (Pstream::master())
		{
			internalCoeffs_[patchi][facei].component(cmpt) +=
				diag()[psi_.mesh().boundary()[patchi].faceCells()[facei]];

			boundaryCoeffs_[patchi][facei].component(cmpt) +=
				diag()[psi_.mesh().boundary()[patchi].faceCells()[facei]]
				* value;
		}
	}
}


template<class Type>
tnbLib::SolverPerformance<Type> tnbLib::fvMatrix<Type>::solve
(
	const dictionary& solverControls
)
{
	if (debug)
	{
		Info.masterStream(this->mesh().comm())
			<< "fvMatrix<Type>::solve(const dictionary& solverControls) : "
			"solving fvMatrix<Type>"
			<< endl;
	}

	label maxIter = -1;
	if (solverControls.readIfPresent("maxIter", maxIter))
	{
		if (maxIter == 0)
		{
			return SolverPerformance<Type>();
		}
	}

	word type(solverControls.lookupOrDefault<word>("type", "segregated"));

	if (type == "segregated")
	{
		return solveSegregated(solverControls);
	}
	else if (type == "coupled")
	{
		return solveCoupled(solverControls);
	}
	else
	{
		FatalIOErrorInFunction
		(
			solverControls
		) << "Unknown type " << type
			<< "; currently supported solver types are segregated and coupled"
			<< exit(FatalIOError);

		return SolverPerformance<Type>();
	}
}


template<class Type>
tnbLib::SolverPerformance<Type> tnbLib::fvMatrix<Type>::solveSegregated
(
	const dictionary& solverControls
)
{
	if (debug)
	{
		Info.masterStream(this->mesh().comm())
			<< "fvMatrix<Type>::solveSegregated"
			"(const dictionary& solverControls) : "
			"solving fvMatrix<Type>"
			<< endl;
	}

	GeometricField<Type, fvPatchField, volMesh>& psi =
		const_cast<GeometricField<Type, fvPatchField, volMesh>&>(psi_);

	SolverPerformance<Type> solverPerfVec
	(
		"fvMatrix<Type>::solveSegregated",
		psi.name()
	);

	scalarField saveDiag(diag());

	Field<Type> source(source_);

	// At this point include the boundary source from the coupled boundaries.
	// This is corrected for the implict part by updateMatrixInterfaces within
	// the component loop.
	addBoundarySource(source);

	typename Type::labelType validComponents
	(
		psi.mesh().template validComponents<Type>()
	);

	for (direction cmpt = 0; cmpt < Type::nComponents; cmpt++)
	{
		if (validComponents[cmpt] == -1) continue;

		// copy field and source

		scalarField psiCmpt(psi.primitiveField().component(cmpt));
		addBoundaryDiag(diag(), cmpt);

		scalarField sourceCmpt(source.component(cmpt));

		FieldField<Field, scalar> bouCoeffsCmpt
		(
			boundaryCoeffs_.component(cmpt)
		);

		FieldField<Field, scalar> intCoeffsCmpt
		(
			internalCoeffs_.component(cmpt)
		);

		lduInterfaceFieldPtrsList interfaces =
			psi.boundaryField().scalarInterfaces();

		// Use the initMatrixInterfaces and updateMatrixInterfaces to correct
		// bouCoeffsCmpt for the explicit part of the coupled boundary
		// conditions
		initMatrixInterfaces
		(
			bouCoeffsCmpt,
			interfaces,
			psiCmpt,
			sourceCmpt,
			cmpt
		);

		updateMatrixInterfaces
		(
			bouCoeffsCmpt,
			interfaces,
			psiCmpt,
			sourceCmpt,
			cmpt
		);

		solverPerformance solverPerf;

		// Solver call
		solverPerf = lduMatrix::solver::New
		(
			psi.name() + pTraits<Type>::componentNames[cmpt],
			*this,
			bouCoeffsCmpt,
			intCoeffsCmpt,
			interfaces,
			solverControls
		)->solve(psiCmpt, sourceCmpt, cmpt);

		if (SolverPerformance<Type>::debug)
		{
			solverPerf.print(Info.masterStream(this->mesh().comm()));
		}

		solverPerfVec.replace(cmpt, solverPerf);
		solverPerfVec.solverName() = solverPerf.solverName();

		psi.primitiveFieldRef().replace(cmpt, psiCmpt);
		diag() = saveDiag;
	}

	psi.correctBoundaryConditions();

	Residuals<Type>::append(psi.mesh(), solverPerfVec);

	return solverPerfVec;
}


template<class Type>
tnbLib::SolverPerformance<Type> tnbLib::fvMatrix<Type>::solveCoupled
(
	const dictionary& solverControls
)
{
	if (debug)
	{
		Info.masterStream(this->mesh().comm())
			<< "fvMatrix<Type>::solveCoupled"
			"(const dictionary& solverControls) : "
			"solving fvMatrix<Type>"
			<< endl;
	}

	GeometricField<Type, fvPatchField, volMesh>& psi =
		const_cast<GeometricField<Type, fvPatchField, volMesh>&>(psi_);

	LduMatrix<Type, scalar, scalar> coupledMatrix(psi.mesh());
	coupledMatrix.diag() = diag();
	coupledMatrix.upper() = upper();
	coupledMatrix.lower() = lower();
	coupledMatrix.source() = source();

	addBoundaryDiag(coupledMatrix.diag(), 0);
	addBoundarySource(coupledMatrix.source(), false);

	coupledMatrix.interfaces() = psi.boundaryFieldRef().interfaces();
	coupledMatrix.interfacesUpper() = boundaryCoeffs().component(0);
	coupledMatrix.interfacesLower() = internalCoeffs().component(0);

	autoPtr<typename LduMatrix<Type, scalar, scalar>::solver>
		coupledMatrixSolver
		(
			LduMatrix<Type, scalar, scalar>::solver::New
			(
				psi.name(),
				coupledMatrix,
				solverControls
			)
		);

	SolverPerformance<Type> solverPerf
	(
		coupledMatrixSolver->solve(psi)
	);

	if (SolverPerformance<Type>::debug)
	{
		solverPerf.print(Info.masterStream(this->mesh().comm()));
	}

	psi.correctBoundaryConditions();

	Residuals<Type>::append(psi.mesh(), solverPerf);

	return solverPerf;
}


template<class Type>
tnbLib::autoPtr<typename tnbLib::fvMatrix<Type>::fvSolver>
tnbLib::fvMatrix<Type>::solver()
{
	return solver
	(
		psi_.mesh().solverDict
		(
			psi_.select
			(
				psi_.mesh().data::template lookupOrDefault<bool>
				("finalIteration", false)
			)
		)
	);
}


template<class Type>
tnbLib::SolverPerformance<Type> tnbLib::fvMatrix<Type>::fvSolver::solve()
{
	return solve
	(
		fvMat_.psi_.mesh().solverDict
		(
			fvMat_.psi_.select
			(
				fvMat_.psi_.mesh().data::template lookupOrDefault<bool>
				("finalIteration", false)
			)
		)
	);
}


template<class Type>
tnbLib::SolverPerformance<Type> tnbLib::fvMatrix<Type>::solve(const word& name)
{
	return solve
	(
		psi_.mesh().solverDict
		(
			psi_.mesh().data::template lookupOrDefault<bool>
			("finalIteration", false)
			? word(name + "Final")
			: name
		)
	);
}


template<class Type>
tnbLib::SolverPerformance<Type> tnbLib::fvMatrix<Type>::solve()
{
	return solve
	(
		psi_.mesh().solverDict
		(
			psi_.select
			(
				psi_.mesh().data::template lookupOrDefault<bool>
				(
					"finalIteration",
					false
					)
			)
		)
	);
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>> tnbLib::fvMatrix<Type>::residual() const
{
	tmp<Field<Type>> tres(new Field<Type>(source_));
	Field<Type>& res = tres.ref();

	addBoundarySource(res);

	// Loop over field components
	for (direction cmpt = 0; cmpt < Type::nComponents; cmpt++)
	{
		scalarField psiCmpt(psi_.primitiveField().component(cmpt));

		scalarField boundaryDiagCmpt(psi_.size(), 0.0);
		addBoundaryDiag(boundaryDiagCmpt, cmpt);

		FieldField<Field, scalar> bouCoeffsCmpt
		(
			boundaryCoeffs_.component(cmpt)
		);

		res.replace
		(
			cmpt,
			lduMatrix::residual
			(
				psiCmpt,
				res.component(cmpt) - boundaryDiagCmpt * psiCmpt,
				bouCoeffsCmpt,
				psi_.boundaryField().scalarInterfaces(),
				cmpt
			)
		);
	}

	return tres;
}


// * * * * * * * * * * * * * * * Global Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::SolverPerformance<Type> tnbLib::solve
(
	fvMatrix<Type>& fvm,
	const word& name
)
{
	return fvm.solve(name);
}


template<class Type>
tnbLib::SolverPerformance<Type> tnbLib::solve
(
	const tmp<fvMatrix<Type>>& tfvm,
	const word& name
)
{
	SolverPerformance<Type> solverPerf =
		const_cast<fvMatrix<Type>&>(tfvm()).solve(name);

	tfvm.clear();

	return solverPerf;
}


template<class Type>
tnbLib::SolverPerformance<Type> tnbLib::solve(fvMatrix<Type>& fvm)
{
	return fvm.solve();
}

template<class Type>
tnbLib::SolverPerformance<Type> tnbLib::solve(const tmp<fvMatrix<Type>>& tfvm)
{
	SolverPerformance<Type> solverPerf =
		const_cast<fvMatrix<Type>&>(tfvm()).solve();

	tfvm.clear();

	return solverPerf;
}


// ************************************************************************* //