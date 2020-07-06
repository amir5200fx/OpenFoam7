#include <GAMGSolver.hxx>

#include <vector2D.hxx>
#include <IOstreams.hxx>  // added by amir

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::GAMGSolver::scale
(
	scalarField& field,
	scalarField& Acf,
	const lduMatrix& A,
	const FieldField<Field, scalar>& interfaceLevelBouCoeffs,
	const lduInterfaceFieldPtrsList& interfaceLevel,
	const scalarField& source,
	const direction cmpt
) const
{
	A.Amul
	(
		Acf,
		field,
		interfaceLevelBouCoeffs,
		interfaceLevel,
		cmpt
	);

	scalar scalingFactorNum = 0.0;
	scalar scalingFactorDenom = 0.0;

	forAll(field, i)
	{
		scalingFactorNum += source[i] * field[i];
		scalingFactorDenom += Acf[i] * field[i];
	}

	vector2D scalingVector(scalingFactorNum, scalingFactorDenom);
	A.mesh().reduce(scalingVector, sumOp<vector2D>());

	const scalar sf = scalingVector.x() / stabilise(scalingVector.y(), vSmall);

	if (debug >= 2)
	{
		Pout << sf << " ";
	}

	const scalarField& D = A.diag();

	forAll(field, i)
	{
		field[i] = sf * field[i] + (source[i] - sf * Acf[i]) / D[i];
	}
}


// ************************************************************************* //