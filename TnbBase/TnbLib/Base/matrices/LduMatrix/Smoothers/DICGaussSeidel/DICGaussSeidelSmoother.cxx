#include <DICGaussSeidelSmoother.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(DICGaussSeidelSmoother, 0);

	lduMatrix::smoother::addsymMatrixConstructorToTable<DICGaussSeidelSmoother>
		addDICGaussSeidelSmootherSymMatrixConstructorToTable_;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::DICGaussSeidelSmoother::DICGaussSeidelSmoother
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
	dicSmoother_
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

void tnbLib::DICGaussSeidelSmoother::smooth
(
	scalarField& psi,
	const scalarField& source,
	const direction cmpt,
	const label nSweeps
) const
{
	dicSmoother_.smooth(psi, source, cmpt, nSweeps);
	gsSmoother_.smooth(psi, source, cmpt, nSweeps);
}


// ************************************************************************* //