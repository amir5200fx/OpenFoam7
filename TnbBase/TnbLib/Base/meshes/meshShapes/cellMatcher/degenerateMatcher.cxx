#include <degenerateMatcher.hxx>

#include <ListOps.hxx>
#include <cellShape.hxx>  // added by amir
#include <primitiveMesh.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

tnbLib::hexMatcher tnbLib::degenerateMatcher::hex;
tnbLib::wedgeMatcher tnbLib::degenerateMatcher::wedge;
tnbLib::prismMatcher tnbLib::degenerateMatcher::prism;
tnbLib::tetWedgeMatcher tnbLib::degenerateMatcher::tetWedge;
tnbLib::pyrMatcher tnbLib::degenerateMatcher::pyr;
tnbLib::tetMatcher tnbLib::degenerateMatcher::tet;


tnbLib::cellShape tnbLib::degenerateMatcher::match
(
	const faceList& faces,
	const labelList& owner,
	const label celli,
	const labelList& cellFaces
)
{
	// Recognize in order of assumed occurrence.

	if (hex.matchShape(false, faces, owner, celli, cellFaces))
	{
		return cellShape(hex.model(), hex.vertLabels());
	}
	else if (tet.matchShape(false, faces, owner, celli, cellFaces))
	{
		return cellShape(tet.model(), tet.vertLabels());
	}
	else if (prism.matchShape(false, faces, owner, celli, cellFaces))
	{
		return cellShape(prism.model(), prism.vertLabels());
	}
	else if (pyr.matchShape(false, faces, owner, celli, cellFaces))
	{
		return cellShape(pyr.model(), pyr.vertLabels());
	}
	else if (wedge.matchShape(false, faces, owner, celli, cellFaces))
	{
		return cellShape(wedge.model(), wedge.vertLabels());
	}
	else if (tetWedge.matchShape(false, faces, owner, celli, cellFaces))
	{
		return cellShape(tetWedge.model(), tetWedge.vertLabels());
	}
	else
	{
		return cellShape(*(cellModeller::lookup(0)), labelList(0));
	}
}


tnbLib::cellShape tnbLib::degenerateMatcher::match(const faceList& faces)
{
	// Do as if single cell mesh; all faces are referenced by a single cell

	return match
	(
		faces,
		labelList(faces.size(), 0),    // cell 0 is owner of all faces
		0,                             // cell 0
		identity(faces.size())         // cell 0 consists of all faces
	);
}


tnbLib::cellShape tnbLib::degenerateMatcher::match(const cellShape& shape)
{
	return match(shape.collapsedFaces());
}


tnbLib::cellShape tnbLib::degenerateMatcher::match
(
	const primitiveMesh& mesh,
	const label celli
)
{
	return match
	(
		mesh.faces(),
		mesh.faceOwner(),
		celli,
		mesh.cells()[celli]
	);
}


// ************************************************************************* //