#include <CECCellToFaceStencil.hxx>

#include <CECCellToCellStencil.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::CECCellToFaceStencil::CECCellToFaceStencil(const polyMesh& mesh)
	:
	cellToFaceStencil(mesh)
{
	// Calculate per cell the (edge) connected cells (in global numbering)
	CECCellToCellStencil globalCellCells(mesh);

	// Add stencils of neighbouring cells to create faceStencil
	labelListList faceStencil;
	calcFaceStencil(globalCellCells, faceStencil);

	// Transfer to *this
	transfer(faceStencil);
}


// ************************************************************************* //