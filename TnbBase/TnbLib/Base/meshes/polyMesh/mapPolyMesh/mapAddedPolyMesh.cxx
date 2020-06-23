#include <mapAddedPolyMesh.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::mapAddedPolyMesh::mapAddedPolyMesh
(
	const label nOldPoints,
	const label nOldFaces,
	const label nOldCells,
	const label nAddedPoints,
	const label nAddedFaces,
	const label nAddedCells,
	const labelList& oldPointMap,
	const labelList& oldFaceMap,
	const labelList& oldCellMap,

	const labelList& addedPointMap,
	const labelList& addedFaceMap,
	const labelList& addedCellMap,

	const labelList& oldPatchMap,
	const labelList& addedPatchMap,
	const labelList& oldPatchSizes,
	const labelList& oldPatchStarts
)
	:
	nOldPoints_(nOldPoints),
	nOldFaces_(nOldFaces),
	nOldCells_(nOldCells),
	nAddedPoints_(nAddedPoints),
	nAddedFaces_(nAddedFaces),
	nAddedCells_(nAddedCells),

	oldPointMap_(oldPointMap),
	oldFaceMap_(oldFaceMap),
	oldCellMap_(oldCellMap),

	addedPointMap_(addedPointMap),
	addedFaceMap_(addedFaceMap),
	addedCellMap_(addedCellMap),

	oldPatchMap_(oldPatchMap),
	addedPatchMap_(addedPatchMap),

	oldPatchSizes_(oldPatchSizes),
	oldPatchStarts_(oldPatchStarts)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //


// ************************************************************************* //