#include <faceAreaPairGAMGAgglomeration.hxx>

#include <fvMesh.hxx>
#include <surfaceFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(faceAreaPairGAMGAgglomeration, 0);

	addToRunTimeSelectionTable
	(
		GAMGAgglomeration,
		faceAreaPairGAMGAgglomeration,
		lduMesh
	);

	addToRunTimeSelectionTable
	(
		GAMGAgglomeration,
		faceAreaPairGAMGAgglomeration,
		geometry
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::faceAreaPairGAMGAgglomeration::faceAreaPairGAMGAgglomeration
(
	const lduMesh& mesh,
	const dictionary& controlDict
)
	:
	pairGAMGAgglomeration(mesh, controlDict)
{
	const fvMesh& fvmesh = refCast<const fvMesh>(mesh);

	// agglomerate(mesh, sqrt(fvmesh.magSf().primitiveField()));
	agglomerate
	(
		mesh,
		mag
		(
			cmptMultiply
			(
				fvmesh.Sf().primitiveField()
				/ sqrt(fvmesh.magSf().primitiveField()),
				vector(1, 1.01, 1.02)
				// vector::one
			)
		)
	);
}


tnbLib::faceAreaPairGAMGAgglomeration::faceAreaPairGAMGAgglomeration
(
	const lduMesh& mesh,
	const scalarField& cellVolumes,
	const vectorField& faceAreas,
	const dictionary& controlDict
)
	:
	pairGAMGAgglomeration(mesh, controlDict)
{
	// agglomerate(mesh, sqrt(mag(faceAreas)));
	agglomerate
	(
		mesh,
		mag
		(
			cmptMultiply
			(
				faceAreas
				/ sqrt(mag(faceAreas)),
				vector(1, 1.01, 1.02)
				// vector::one
			)
		)
	);
}


// ************************************************************************* //