#include <MeshWave.hxx>

#include <polyMesh.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

template<class Type, class TrackingData>
int tnbLib::MeshWave<Type, TrackingData>::dummyTrackData_ = 12345;


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Iterate, propagating changedFacesInfo across mesh, until no change (or
// maxIter reached).
template<class Type, class TrackingData>
tnbLib::MeshWave<Type, TrackingData>::MeshWave
(
	const polyMesh& mesh,
	const labelList& changedFaces,
	const List<Type>& changedFacesInfo,
	const label maxIter,
	TrackingData& td
)
	:
	allFaceInfo_(mesh.nFaces()),
	allCellInfo_(mesh.nCells()),
	calc_
	(
		mesh,
		changedFaces,
		changedFacesInfo,
		allFaceInfo_,
		allCellInfo_,
		maxIter,
		td
	)
{}


// Iterate, propagating changedFacesInfo across mesh, until no change (or
// maxIter reached). Initial cell values specified.
template<class Type, class TrackingData>
tnbLib::MeshWave<Type, TrackingData>::MeshWave
(
	const polyMesh& mesh,
	const labelList& changedFaces,
	const List<Type>& changedFacesInfo,
	const List<Type>& allCellInfo,
	const label maxIter,
	TrackingData& td
)
	:
	allFaceInfo_(mesh.nFaces()),
	allCellInfo_(allCellInfo),
	calc_
	(
		mesh,
		changedFaces,
		changedFacesInfo,
		allFaceInfo_,
		allCellInfo_,
		maxIter,
		td
	)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //


// ************************************************************************* //