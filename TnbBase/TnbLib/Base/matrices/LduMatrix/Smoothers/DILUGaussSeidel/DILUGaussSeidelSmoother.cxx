#include <DILUGaussSeidelSmoother.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(DILUGaussSeidelSmoother, 0);

	lduMatrix::smoother::
		addasymMatrixConstructorToTable<DILUGaussSeidelSmoother>
		addDILUGaussSeidelSmootherAsymMatrixConstructorToTable_;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::DILUGaussSeidelSmoother::DILUGaussSeidelSmoother
(
	const word& fieldName,
	const lduMatrix& matrix,
	const FieldField<Field, scalar>& interfaceBouCoeffs,
	const FieldField<Field, scalar>& interfaceIntCoeffs,
	const lduInterfaceFieldPtrsList& interfaces
)
	:
	lduMatrix::smoother
	(
		fieldName,
		matrix,
		interfaceBouCoeffs,
		interfaceIntCoeffs,
		interfaces
	),
	diluSmoother_
	(
		fieldName,
		matrix,
		interfaceBouCoeffs,
		interfaceIntCoeffs,
		interfaces
	),
	gsSmoother_
	(
		fieldName,
		matrix,
		interfaceBouCoeffs,
		interfaceIntCoeffs,
		interfaces
	)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::DILUGaussSeidelSmoother::smooth
(
	scalarField& psi,
	const scalarField& source,
	const direction cmpt,
	const label nSweeps
) const
{
	diluSmoother_.smooth(psi, source, cmpt, nSweeps);
	gsSmoother_.smooth(psi, source, cmpt, nSweeps);
}


// ************************************************************************* //