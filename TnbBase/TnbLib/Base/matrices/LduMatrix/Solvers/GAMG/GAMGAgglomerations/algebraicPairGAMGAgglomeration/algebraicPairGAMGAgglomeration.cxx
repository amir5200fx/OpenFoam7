#include <algebraicPairGAMGAgglomeration.hxx>

#include <lduMatrix.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(algebraicPairGAMGAgglomeration, 0);

	addToRunTimeSelectionTable
	(
		GAMGAgglomeration,
		algebraicPairGAMGAgglomeration,
		lduMatrix
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::algebraicPairGAMGAgglomeration::algebraicPairGAMGAgglomeration
(
	const lduMatrix& matrix,
	const dictionary& controlDict
)
	:
	pairGAMGAgglomeration(matrix.mesh(), controlDict)
{
	const lduMesh& mesh = matrix.mesh();

	if (matrix.hasLower())
	{
		agglomerate(mesh, max(mag(matrix.upper()), mag(matrix.lower())));
	}
	else
	{
		agglomerate(mesh, mag(matrix.upper()));
	}
}


// ************************************************************************* //