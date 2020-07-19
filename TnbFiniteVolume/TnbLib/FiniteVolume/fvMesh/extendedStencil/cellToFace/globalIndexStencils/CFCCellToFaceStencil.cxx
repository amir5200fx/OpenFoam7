#include <CFCCellToFaceStencil.hxx>

#include <CFCCellToCellStencil.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::CFCCellToFaceStencil::CFCCellToFaceStencil(const polyMesh& mesh)
	:
	cellToFaceStencil(mesh)
{
	// Calculate per cell the (face) connected cells (in global numbering)
	CFCCellToCellStencil globalCellCells(mesh);

	// Add stencils of neighbouring cells to create faceStencil
	labelListList faceStencil;
	calcFaceStencil(globalCellCells, faceStencil);

	// Transfer to *this
	transfer(faceStencil);
}


// ************************************************************************* //