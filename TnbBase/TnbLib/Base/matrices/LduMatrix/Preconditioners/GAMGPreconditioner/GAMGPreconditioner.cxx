#include <GAMGPreconditioner.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(GAMGPreconditioner, 0);

	lduMatrix::preconditioner::addsymMatrixConstructorToTable
		<GAMGPreconditioner> addGAMGPreconditionerSymMatrixConstructorToTable_;

	lduMatrix::preconditioner::addasymMatrixConstructorToTable
		<GAMGPreconditioner> addGAMGPreconditionerAsymMatrixConstructorToTable_;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::GAMGPreconditioner::GAMGPreconditioner
(
	const lduMatrix::solver& sol,
	const dictionary& solverControls
)
	:
	GAMGSolver
	(
		sol.fieldName(),
		sol.matrix(),
		sol.interfaceBouCoeffs(),
		sol.interfaceIntCoeffs(),
		sol.interfaces(),
		solverControls
	),
	lduMatrix::preconditioner(sol),
	nVcycles_(2)
{
	readControls();
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::GAMGPreconditioner::~GAMGPreconditioner()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::GAMGPreconditioner::readControls()
{
	GAMGSolver::readControls();
	nVcycles_ = controlDict_.lookupOrDefault<label>("nVcycles", 2);
}


void tnbLib::GAMGPreconditioner::precondition
(
	scalarField& wA,
	const scalarField& rA,
	const direction cmpt
) const
{
	wA = 0.0;
	scalarField AwA(wA.size());
	scalarField finestCorrection(wA.size());
	scalarField finestResidual(rA);

	// Create coarse grid correction fields
	PtrList<scalarField> coarseCorrFields;

	// Create coarse grid sources
	PtrList<scalarField> coarseSources;

	// Create the smoothers for all levels
	PtrList<lduMatrix::smoother> smoothers;

	// Scratch fields if processor-agglomerated coarse level meshes
	// are bigger than original. Usually not needed
	scalarField ApsiScratch;
	scalarField finestCorrectionScratch;

	// Initialise the above data structures
	initVcycle
	(
		coarseCorrFields,
		coarseSources,
		smoothers,
		ApsiScratch,
		finestCorrectionScratch
	);

	for (label cycle = 0; cycle < nVcycles_; cycle++)
	{
		Vcycle
		(
			smoothers,
			wA,
			rA,
			AwA,
			finestCorrection,
			finestResidual,

			(ApsiScratch.size() ? ApsiScratch : AwA),
			(
				finestCorrectionScratch.size()
				? finestCorrectionScratch
				: finestCorrection
				),

			coarseCorrFields,
			coarseSources,
			cmpt
		);

		if (cycle < nVcycles_ - 1)
		{
			// Calculate finest level residual field
			matrix_.Amul(AwA, wA, interfaceBouCoeffs_, interfaces_, cmpt);
			finestResidual = rA;
			finestResidual -= AwA;
		}
	}
}


// ************************************************************************* //