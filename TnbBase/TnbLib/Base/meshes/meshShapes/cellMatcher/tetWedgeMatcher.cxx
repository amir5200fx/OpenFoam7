#include <tetWedgeMatcher.hxx>

#include <cellMatcher.hxx>
#include <primitiveMesh.hxx>
#include <cellModeller.hxx>
#include <ListOps.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

const tnbLib::label tnbLib::tetWedgeMatcher::vertPerCell = 5;
const tnbLib::label tnbLib::tetWedgeMatcher::facePerCell = 4;
const tnbLib::label tnbLib::tetWedgeMatcher::maxVertPerFace = 4;


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::tetWedgeMatcher::tetWedgeMatcher()
	:
	cellMatcher
	(
		vertPerCell,
		facePerCell,
		maxVertPerFace,
		"tetWedge"
	)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::tetWedgeMatcher::~tetWedgeMatcher()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::tetWedgeMatcher::matchShape
(
	const bool checkOnly,
	const faceList& faces,
	const labelList& owner,
	const label celli,
	const labelList& myFaces
)
{
	if (!faceSizeMatch(faces, myFaces))
	{
		return false;
	}

	// Is tetWedge for sure now. No other shape has two tri, two quad
	if (checkOnly)
	{
		return true;
	}

	// Calculate localFaces_ and mapping pointMap_, faceMap_
	label numVert = calcLocalFaces(faces, myFaces);

	if (numVert != vertPerCell)
	{
		return false;
	}

	// Set up 'edge' to face mapping.
	calcEdgeAddressing(numVert);

	// Set up point on face to index-in-face mapping
	calcPointFaceIndex();

	// Storage for maps -vertex to mesh and -face to mesh
	vertLabels_.setSize(vertPerCell);
	faceLabels_.setSize(facePerCell);

	//
	// Try first triangular face. Rotate in all directions.
	// Walk path to other triangular face.
	//

	label face0I = -1;
	forAll(faceSize_, facei)
	{
		if (faceSize_[facei] == 3)
		{
			face0I = facei;
			break;
		}
	}

	const face& face0 = localFaces_[face0I];

	// Try all rotations of this face
	for (label face0vert0 = 0; face0vert0 < faceSize_[face0I]; face0vert0++)
	{
		//
		// Try to follow prespecified path on faces of cell,
		// starting at face0vert0
		//

		vertLabels_[0] = pointMap_[face0[face0vert0]];
		faceLabels_[0] = faceMap_[face0I];

		// Walk face 0 from vertex 0 to 1
		label face0vert1 =
			nextVert
			(
				face0vert0,
				faceSize_[face0I],
				!(owner[faceMap_[face0I]] == celli)
			);
		vertLabels_[1] = pointMap_[face0[face0vert1]];

		// Jump edge from face0 to face1 (the other triangular face)
		label face1I =
			otherFace
			(
				numVert,
				face0[face0vert0],
				face0[face0vert1],
				face0I
			);

		if (faceSize_[face1I] != 3)
		{
			continue;
		}
		faceLabels_[1] = faceMap_[face1I];


		// Now correctly oriented tet-wedge for sure.

		// Walk face 0 from vertex 1 to 2
		label face0vert2 =
			nextVert
			(
				face0vert1,
				faceSize_[face0I],
				!(owner[faceMap_[face0I]] == celli)
			);
		vertLabels_[2] = pointMap_[face0[face0vert2]];

		// Jump edge from face0 to face3
		label face3I =
			otherFace
			(
				numVert,
				face0[face0vert1],
				face0[face0vert2],
				face0I
			);
		faceLabels_[3] = faceMap_[face3I];

		// Jump edge from face0 to face2
		label face2I =
			otherFace
			(
				numVert,
				face0[face0vert2],
				face0[face0vert0],
				face0I
			);
		faceLabels_[2] = faceMap_[face2I];

		// Get index of vertex 2 in face3
		label face3vert2 = pointFaceIndex_[face0[face0vert2]][face3I];

		// Walk face 3 from vertex 2 to 4
		label face3vert4 =
			nextVert
			(
				face3vert2,
				faceSize_[face3I],
				(owner[faceMap_[face3I]] == celli)
			);

		const face& face3 = localFaces_[face3I];

		vertLabels_[4] = pointMap_[face3[face3vert4]];

		// Walk face 3 from vertex 4 to 3
		label face3vert3 =
			nextVert
			(
				face3vert4,
				faceSize_[face3I],
				(owner[faceMap_[face3I]] == celli)
			);
		vertLabels_[3] = pointMap_[face3[face3vert3]];

		return true;
	}

	// Tried all triangular faces, in all rotations but no match found
	return false;
}


tnbLib::label tnbLib::tetWedgeMatcher::faceHashValue() const
{
	return 2 * 3 + 2 * 4;
}


bool tnbLib::tetWedgeMatcher::faceSizeMatch
(
	const faceList& faces,
	const labelList& myFaces
) const
{
	if (myFaces.size() != 4)
	{
		return false;
	}

	label nTris = 0;
	label nQuads = 0;

	forAll(myFaces, myFacei)
	{
		label size = faces[myFaces[myFacei]].size();

		if (size == 3)
		{
			nTris++;
		}
		else if (size == 4)
		{
			nQuads++;
		}
		else
		{
			return false;
		}
	}
	if ((nTris == 2) && (nQuads == 2))
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool tnbLib::tetWedgeMatcher::isA(const primitiveMesh& mesh, const label celli)
{
	return matchShape
	(
		true,
		mesh.faces(),
		mesh.faceOwner(),
		celli,
		mesh.cells()[celli]
	);
}


bool tnbLib::tetWedgeMatcher::isA(const faceList& faces)
{
	// Do as if mesh with one cell only
	return matchShape
	(
		true,
		faces,                      // all faces in mesh
		labelList(faces.size(), 0), // cell 0 is owner of all faces
		0,                          // cell label
		identity(faces.size())      // faces of cell 0
	);
}


bool tnbLib::tetWedgeMatcher::matches
(
	const primitiveMesh& mesh,
	const label celli,
	cellShape& shape
)
{
	if
		(
			matchShape
			(
				false,
				mesh.faces(),
				mesh.faceOwner(),
				celli,
				mesh.cells()[celli]
			)
			)
	{
		shape = cellShape(model(), vertLabels());

		return true;
	}
	else
	{
		return false;
	}
}


// ************************************************************************* //