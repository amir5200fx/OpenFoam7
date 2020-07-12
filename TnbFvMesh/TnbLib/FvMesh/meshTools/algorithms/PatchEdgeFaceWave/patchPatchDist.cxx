#include <patchPatchDist.hxx>

#include <PatchEdgeFaceWave.hxx>
#include <syncTools.hxx>
#include <polyMesh.hxx>
#include <patchEdgeFaceInfo.hxx>

#include <PstreamReduceOps.hxx> // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::patchPatchDist::patchPatchDist
(
	const polyPatch& patch,
	const labelHashSet& nbrPatchIDs
)
	:
	patch_(patch),
	nbrPatchIDs_(nbrPatchIDs),
	nUnset_(0)
{
	patchPatchDist::correct();
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::patchPatchDist::~patchPatchDist()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::patchPatchDist::correct()
{
	// Mark all edge connected to a nbrPatch.
	label nBnd = 0;
	forAllConstIter(labelHashSet, nbrPatchIDs_, iter)
	{
		label nbrPatchi = iter.key();
		const polyPatch& nbrPatch = patch_.boundaryMesh()[nbrPatchi];
		nBnd += nbrPatch.nEdges() - nbrPatch.nInternalEdges();
	}

	// Mark all edges. Note: should use HashSet but have no syncTools
	// functionality for these.
	EdgeMap<label> nbrEdges(2 * nBnd);

	forAllConstIter(labelHashSet, nbrPatchIDs_, iter)
	{
		label nbrPatchi = iter.key();
		const polyPatch& nbrPatch = patch_.boundaryMesh()[nbrPatchi];
		const labelList& nbrMp = nbrPatch.meshPoints();

		for
			(
				label edgeI = nbrPatch.nInternalEdges();
				edgeI < nbrPatch.nEdges();
				edgeI++
				)
		{
			const edge& e = nbrPatch.edges()[edgeI];
			const edge meshE = edge(nbrMp[e[0]], nbrMp[e[1]]);
			nbrEdges.insert(meshE, nbrPatchi);
		}
	}


	// Make sure these boundary edges are marked everywhere.
	syncTools::syncEdgeMap
	(
		patch_.boundaryMesh().mesh(),
		nbrEdges,
		maxEqOp<label>()
	);


	// Data on all edges and faces
	List<patchEdgeFaceInfo> allEdgeInfo(patch_.nEdges());
	List<patchEdgeFaceInfo> allFaceInfo(patch_.size());

	// Initial seed
	label nBndEdges = patch_.nEdges() - patch_.nInternalEdges();
	DynamicList<label> initialEdges(2 * nBndEdges);
	DynamicList<patchEdgeFaceInfo> initialEdgesInfo(2 * nBndEdges);


	// Seed all my edges that are also nbrEdges

	const labelList& mp = patch_.meshPoints();

	for
		(
			label edgeI = patch_.nInternalEdges();
			edgeI < patch_.nEdges();
			edgeI++
			)
	{
		const edge& e = patch_.edges()[edgeI];
		const edge meshE = edge(mp[e[0]], mp[e[1]]);
		EdgeMap<label>::const_iterator edgeFnd = nbrEdges.find(meshE);
		if (edgeFnd != nbrEdges.end())
		{
			initialEdges.append(edgeI);
			initialEdgesInfo.append
			(
				patchEdgeFaceInfo
				(
					e.centre(patch_.localPoints()),
					0.0
				)
			);
		}
	}


	// Walk
	PatchEdgeFaceWave
		<
		primitivePatch,
		patchEdgeFaceInfo
		> calc
		(
			patch_.boundaryMesh().mesh(),
			patch_,
			initialEdges,
			initialEdgesInfo,
			allEdgeInfo,
			allFaceInfo,
			returnReduce(patch_.nEdges(), sumOp<label>())
		);


	// Extract into *this
	setSize(patch_.size());
	nUnset_ = 0;
	forAll(allFaceInfo, facei)
	{
		if (allFaceInfo[facei].valid(calc.data()))
		{
			operator[](facei) = tnbLib::sqrt(allFaceInfo[facei].distSqr());
		}
		else
		{
			nUnset_++;
		}
	}
}


// ************************************************************************* //