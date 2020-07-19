#include <faceToCellStencil.hxx>

#include <polyMesh.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::faceToCellStencil::faceToCellStencil(const polyMesh& mesh)
	:
	mesh_(mesh),
	globalNumbering_(mesh_.nFaces())
{}


// ************************************************************************* //