#include <extendedCellToCellStencil.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::extendedCellToCellStencil::extendedCellToCellStencil(const polyMesh& mesh)
	:
	mesh_(mesh)
{
	// Check for transformation - not supported.
	const polyBoundaryMesh& patches = mesh.boundaryMesh();

	forAll(patches, patchi)
	{
		if (patches[patchi].coupled())
		{
			const coupledPolyPatch& cpp =
				refCast<const coupledPolyPatch>(patches[patchi]);

			if (!cpp.parallel() || cpp.separated())
			{
				FatalErrorInFunction
					<< "Coupled patches with transformations not supported."
					<< endl
					<< "Problematic patch " << cpp.name() << exit(FatalError);
			}
		}
	}
}


// ************************************************************************* //