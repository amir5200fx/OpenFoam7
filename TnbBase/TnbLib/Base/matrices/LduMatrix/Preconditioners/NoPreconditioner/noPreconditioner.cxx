#include <noPreconditioner.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(noPreconditioner, 0);

	lduMatrix::preconditioner::
		addsymMatrixConstructorToTable<noPreconditioner>
		addnoPreconditionerSymMatrixConstructorToTable_;

	lduMatrix::preconditioner::
		addasymMatrixConstructorToTable<noPreconditioner>
		addnoPreconditionerAsymMatrixConstructorToTable_;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::noPreconditioner::noPreconditioner
(
	const lduMatrix::solver& sol,
	const dictionary&
)
	:
	lduMatrix::preconditioner(sol)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::noPreconditioner::precondition
(
	scalarField& wA,
	const scalarField& rA,
	const direction
) const
{
	scalar* __restrict wAPtr = wA.begin();
	const scalar* __restrict rAPtr = rA.begin();

	label nCells = wA.size();

	for (label cell = 0; cell < nCells; cell++)
	{
		wAPtr[cell] = rAPtr[cell];
	}
}


// ************************************************************************* //