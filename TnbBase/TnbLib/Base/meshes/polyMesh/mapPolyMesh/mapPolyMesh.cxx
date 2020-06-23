#include <mapPolyMesh.hxx>

#include <polyMesh.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::mapPolyMesh::mapPolyMesh
(
	const polyMesh& mesh,
	const label nOldPoints,
	const label nOldFaces,
	const label nOldCells,
	const labelList& pointMap,
	const List<objectMap>& pointsFromPoints,
	const labelList& faceMap,
	const List<objectMap>& facesFromPoints,
	const List<objectMap>& facesFromEdges,
	const List<objectMap>& facesFromFaces,
	const labelList& cellMap,
	const List<objectMap>& cellsFromPoints,
	const List<objectMap>& cellsFromEdges,
	const List<objectMap>& cellsFromFaces,
	const List<objectMap>& cellsFromCells,
	const labelList& reversePointMap,
	const labelList& reverseFaceMap,
	const labelList& reverseCellMap,
	const labelHashSet& flipFaceFlux,
	const labelListList& patchPointMap,
	const labelListList& pointZoneMap,
	const labelListList& faceZonePointMap,
	const labelListList& faceZoneFaceMap,
	const labelListList& cellZoneMap,
	const pointField& preMotionPoints,
	const labelList& oldPatchStarts,
	const labelList& oldPatchNMeshPoints,
	const autoPtr<scalarField>& oldCellVolumesPtr
)
	:
mesh_(mesh),
nOldPoints_(nOldPoints),
nOldFaces_(nOldFaces),
nOldCells_(nOldCells),
pointMap_(pointMap),
pointsFromPointsMap_(pointsFromPoints),
faceMap_(faceMap),
facesFromPointsMap_(facesFromPoints),
facesFromEdgesMap_(facesFromEdges),
facesFromFacesMap_(facesFromFaces),
cellMap_(cellMap),
cellsFromPointsMap_(cellsFromPoints),
cellsFromEdgesMap_(cellsFromEdges),
cellsFromFacesMap_(cellsFromFaces),
cellsFromCellsMap_(cellsFromCells),
reversePointMap_(reversePointMap),
reverseFaceMap_(reverseFaceMap),
reverseCellMap_(reverseCellMap),
flipFaceFlux_(flipFaceFlux),
patchPointMap_(patchPointMap),
pointZoneMap_(pointZoneMap),
faceZonePointMap_(faceZonePointMap),
faceZoneFaceMap_(faceZoneFaceMap),
cellZoneMap_(cellZoneMap),
preMotionPoints_(preMotionPoints),
oldPatchSizes_(oldPatchStarts.size()),
oldPatchStarts_(oldPatchStarts),
oldPatchNMeshPoints_(oldPatchNMeshPoints),
oldCellVolumesPtr_(oldCellVolumesPtr)
{
	if (oldPatchStarts_.size())
	{
		// Calculate old patch sizes
		for (label patchi = 0; patchi < oldPatchStarts_.size() - 1; patchi++)
		{
			oldPatchSizes_[patchi] =
				oldPatchStarts_[patchi + 1] - oldPatchStarts_[patchi];
		}

		// Set the last one by hand
		const label lastPatchID = oldPatchStarts_.size() - 1;

		oldPatchSizes_[lastPatchID] = nOldFaces_ - oldPatchStarts_[lastPatchID];

		if (polyMesh::debug)
		{
			if (min(oldPatchSizes_) < 0)
			{
				FatalErrorInFunction
					<< abort(FatalError);
			}
		}
	}
}


tnbLib::mapPolyMesh::mapPolyMesh
(
	const polyMesh& mesh,
	const label nOldPoints,
	const label nOldFaces,
	const label nOldCells,
	labelList& pointMap,
	List<objectMap>& pointsFromPoints,
	labelList& faceMap,
	List<objectMap>& facesFromPoints,
	List<objectMap>& facesFromEdges,
	List<objectMap>& facesFromFaces,
	labelList& cellMap,
	List<objectMap>& cellsFromPoints,
	List<objectMap>& cellsFromEdges,
	List<objectMap>& cellsFromFaces,
	List<objectMap>& cellsFromCells,
	labelList& reversePointMap,
	labelList& reverseFaceMap,
	labelList& reverseCellMap,
	labelHashSet& flipFaceFlux,
	labelListList& patchPointMap,
	labelListList& pointZoneMap,
	labelListList& faceZonePointMap,
	labelListList& faceZoneFaceMap,
	labelListList& cellZoneMap,
	pointField& preMotionPoints,
	labelList& oldPatchStarts,
	labelList& oldPatchNMeshPoints,
	autoPtr<scalarField>& oldCellVolumesPtr,
	const bool reuse
)
	:
mesh_(mesh),
nOldPoints_(nOldPoints),
nOldFaces_(nOldFaces),
nOldCells_(nOldCells),
pointMap_(pointMap, reuse),
pointsFromPointsMap_(pointsFromPoints, reuse),
faceMap_(faceMap, reuse),
facesFromPointsMap_(facesFromPoints, reuse),
facesFromEdgesMap_(facesFromEdges, reuse),
facesFromFacesMap_(facesFromFaces, reuse),
cellMap_(cellMap, reuse),
cellsFromPointsMap_(cellsFromPoints, reuse),
cellsFromEdgesMap_(cellsFromEdges, reuse),
cellsFromFacesMap_(cellsFromFaces, reuse),
cellsFromCellsMap_(cellsFromCells, reuse),
reversePointMap_(reversePointMap, reuse),
reverseFaceMap_(reverseFaceMap, reuse),
reverseCellMap_(reverseCellMap, reuse),
flipFaceFlux_(flipFaceFlux),
patchPointMap_(patchPointMap, reuse),
pointZoneMap_(pointZoneMap, reuse),
faceZonePointMap_(faceZonePointMap, reuse),
faceZoneFaceMap_(faceZoneFaceMap, reuse),
cellZoneMap_(cellZoneMap, reuse),
preMotionPoints_(preMotionPoints, reuse),
oldPatchSizes_(oldPatchStarts.size()),
oldPatchStarts_(oldPatchStarts, reuse),
oldPatchNMeshPoints_(oldPatchNMeshPoints, reuse),
oldCellVolumesPtr_(oldCellVolumesPtr, reuse)
{
	if (oldPatchStarts_.size() > 0)
	{
		// Calculate old patch sizes
		for (label patchi = 0; patchi < oldPatchStarts_.size() - 1; patchi++)
		{
			oldPatchSizes_[patchi] =
				oldPatchStarts_[patchi + 1] - oldPatchStarts_[patchi];
		}

		// Set the last one by hand
		const label lastPatchID = oldPatchStarts_.size() - 1;

		oldPatchSizes_[lastPatchID] = nOldFaces_ - oldPatchStarts_[lastPatchID];

		if (polyMesh::debug)
		{
			if (min(oldPatchSizes_) < 0)
			{
				FatalErrorInFunction
					<< "Calculated negative old patch size."
					<< "  Error in mapping data"
					<< abort(FatalError);
			}
		}
	}
}


// ************************************************************************* //
