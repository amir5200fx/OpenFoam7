#include <CPCCellToFaceStencil.hxx>

#include <CPCCellToCellStencil.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::CPCCellToFaceStencil::CPCCellToFaceStencil(const polyMesh& mesh)
	:
	cellToFaceStencil(mesh)
{
	// Calculate per cell the (face) connected cells (in global numbering)
	CPCCellToCellStencil globalCellCells(mesh);

	// Add stencils of neighbouring cells to create faceStencil
	labelListList faceStencil;
	calcFaceStencil(globalCellCells, faceStencil);

	// Transfer to *this
	transfer(faceStencil);
}


// ************************************************************************* //