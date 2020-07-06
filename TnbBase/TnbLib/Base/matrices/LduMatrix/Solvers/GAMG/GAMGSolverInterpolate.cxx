#include <GAMGSolver.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::GAMGSolver::interpolate
(
	scalarField& psi,
	scalarField& Apsi,
	const lduMatrix& m,
	const FieldField<Field, scalar>& interfaceBouCoeffs,
	const lduInterfaceFieldPtrsList& interfaces,
	const direction cmpt
) const
{
	scalar* __restrict psiPtr = psi.begin();

	const label* const __restrict uPtr = m.lduAddr().upperAddr().begin();
	const label* const __restrict lPtr = m.lduAddr().lowerAddr().begin();

	const scalar* const __restrict diagPtr = m.diag().begin();
	const scalar* const __restrict upperPtr = m.upper().begin();
	const scalar* const __restrict lowerPtr = m.lower().begin();

	Apsi = 0;
	scalar* __restrict ApsiPtr = Apsi.begin();

	m.initMatrixInterfaces
	(
		interfaceBouCoeffs,
		interfaces,
		psi,
		Apsi,
		cmpt
	);

	const label nFaces = m.upper().size();
	for (label face = 0; face < nFaces; face++)
	{
		ApsiPtr[uPtr[face]] += lowerPtr[face] * psiPtr[lPtr[face]];
		ApsiPtr[lPtr[face]] += upperPtr[face] * psiPtr[uPtr[face]];
	}

	m.updateMatrixInterfaces
	(
		interfaceBouCoeffs,
		interfaces,
		psi,
		Apsi,
		cmpt
	);

	const label nCells = m.diag().size();
	for (label celli = 0; celli < nCells; celli++)
	{
		psiPtr[celli] = -ApsiPtr[celli] / (diagPtr[celli]);
	}
}


void tnbLib::GAMGSolver::interpolate
(
	scalarField& psi,
	scalarField& Apsi,
	const lduMatrix& m,
	const FieldField<Field, scalar>& interfaceBouCoeffs,
	const lduInterfaceFieldPtrsList& interfaces,
	const labelList& restrictAddressing,
	const scalarField& psiC,
	const direction cmpt
) const
{
	interpolate
	(
		psi,
		Apsi,
		m,
		interfaceBouCoeffs,
		interfaces,
		cmpt
	);

	const label nCells = m.diag().size();
	scalar* __restrict psiPtr = psi.begin();
	const scalar* const __restrict diagPtr = m.diag().begin();

	const label nCCells = psiC.size();
	scalarField corrC(nCCells, 0);
	scalarField diagC(nCCells, 0);

	for (label celli = 0; celli < nCells; celli++)
	{
		corrC[restrictAddressing[celli]] += diagPtr[celli] * psiPtr[celli];
		diagC[restrictAddressing[celli]] += diagPtr[celli];
	}

	for (label ccelli = 0; ccelli < nCCells; ccelli++)
	{
		corrC[ccelli] = psiC[ccelli] - corrC[ccelli] / diagC[ccelli];
	}

	for (label celli = 0; celli < nCells; celli++)
	{
		psiPtr[celli] += corrC[restrictAddressing[celli]];
	}
}


// ************************************************************************* //