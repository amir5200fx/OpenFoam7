#include <edgeFaceCirculator.hxx>

#include <primitiveMesh.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

const tnbLib::primitiveMesh* const tnbLib::edgeFaceCirculator::endConstIterMeshPtr
= nullptr;

const tnbLib::edgeFaceCirculator tnbLib::edgeFaceCirculator::endConstIter
(
	*tnbLib::edgeFaceCirculator::endConstIterMeshPtr, // primitiveMesh
	-1,                                             // faceLabel
	false,                                          // ownerSide
	-1,                                             // index
	false                                           // isBoundaryEdge
);


// ************************************************************************* //