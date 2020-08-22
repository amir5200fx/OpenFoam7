#include <polyMeshFilter.hxx>

#include <polyMesh.hxx>
#include <fvMesh.hxx>
#include <unitConversion.hxx>
#include <edgeCollapser.hxx>
#include <syncTools.hxx>
#include <polyTopoChange.hxx>
#include <globalIndex.hxx>
#include <PackedBoolList.hxx>
#include <pointSet.hxx>
#include <faceSet.hxx>
#include <cellSet.hxx>

#include <PstreamReduceOps.hxx>  // added by amir

// * * * * * * * * * * * * * Static Member Functions * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(polyMeshFilter, 0);
}


void tnbLib::polyMeshFilter::updateSets(const mapPolyMesh& map)
{
	updateSets<pointSet>(map);
	updateSets<faceSet>(map);
	updateSets<cellSet>(map);
}


void tnbLib::polyMeshFilter::copySets
(
	const polyMesh& oldMesh,
	const polyMesh& newMesh
)
{
	copySets<pointSet>(oldMesh, newMesh);
	copySets<faceSet>(oldMesh, newMesh);
	copySets<cellSet>(oldMesh, newMesh);
}


tnbLib::autoPtr<tnbLib::fvMesh> tnbLib::polyMeshFilter::copyMesh(const fvMesh& mesh)
{
	polyTopoChange originalMeshToNewMesh(mesh);

	autoPtr<fvMesh> meshCopy;
	autoPtr<mapPolyMesh> mapPtr = originalMeshToNewMesh.makeMesh
	(
		meshCopy,
		IOobject
		(
			mesh.name(),
			mesh.polyMesh::instance(),
			mesh.time(),
			IOobject::NO_READ,
			IOobject::NO_WRITE,
			false
		),
		mesh,
		true // parallel sync
	);

	const mapPolyMesh& map = mapPtr();

	// Update fields
	meshCopy().updateMesh(map);
	if (map.hasMotionPoints())
	{
		meshCopy().movePoints(map.preMotionPoints());
	}

	copySets(mesh, meshCopy());

	return meshCopy;
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

tnbLib::label tnbLib::polyMeshFilter::filterFacesLoop(const label nOriginalBadFaces)
{
	label nBadFaces = labelMax;
	label nOuterIterations = 0;

	// Maintain the number of times a point has been part of a bad face
	labelList pointErrorCount(mesh_.nPoints(), 0);

	PackedBoolList newErrorPoint(mesh_.nPoints());
	edgeCollapser::checkMeshQuality
	(
		mesh_,
		meshQualityCoeffDict(),
		newErrorPoint
	);

	bool newBadFaces = true;

	// Main loop
	// ~~~~~~~~~
	// It tries and do some collapses, checks the resulting mesh and
	// 'freezes' some edges (by marking in minEdgeLen) and tries again.
	// This will iterate ultimately to the situation where every edge is
	// frozen and nothing gets collapsed.
	while
		(
			nOuterIterations < maxIterations()
			//&& nBadFaces > nOriginalBadFaces
			&& newBadFaces
			)
	{
		Info << nl << "Outer Iteration = " << nOuterIterations++ << nl
			<< endl;

		printScalarFieldStats("Edge Filter Factor", minEdgeLen_);
		printScalarFieldStats("Face Filter Factor", faceFilterFactor_);

		// Reset the new mesh to the old mesh
		newMeshPtr_ = copyMesh(mesh_);
		fvMesh& newMesh = newMeshPtr_();

		scalarField newMeshFaceFilterFactor = faceFilterFactor_;
		pointPriority_.reset(new labelList(originalPointPriority_));

		labelList origToCurrentPointMap(identity(newMesh.nPoints()));

		{
			label nInnerIterations = 0;
			label nPrevLocalCollapse = labelMax;

			Info << incrIndent;

			while (true)
			{
				Info << nl << indent << "Inner iteration = "
					<< nInnerIterations++ << nl << incrIndent << endl;

				label nLocalCollapse = filterFaces
				(
					newMesh,
					newMeshFaceFilterFactor,
					origToCurrentPointMap
				);
				Info << decrIndent;

				if
					(
						nLocalCollapse >= nPrevLocalCollapse
						|| nLocalCollapse == 0
						)
				{
					Info << decrIndent;
					break;
				}
				else
				{
					nPrevLocalCollapse = nLocalCollapse;
				}
			}
		}

		scalarField newMeshMinEdgeLen = minEdgeLen_;

		{
			label nInnerIterations = 0;
			label nPrevLocalCollapse = labelMax;

			Info << incrIndent;

			while (true)
			{
				Info << nl << indent << "Inner iteration = "
					<< nInnerIterations++ << nl << incrIndent << endl;

				label nLocalCollapse = filterEdges
				(
					newMesh,
					newMeshMinEdgeLen,
					origToCurrentPointMap
				);
				Info << decrIndent;

				if
					(
						nLocalCollapse >= nPrevLocalCollapse
						|| nLocalCollapse == 0
						)
				{
					Info << decrIndent;
					break;
				}
				else
				{
					nPrevLocalCollapse = nLocalCollapse;
				}
			}
		}


		// Mesh check
		// ~~~~~~~~~~~~~~~~~~
		// Do not allow collapses in regions of error.
		// Updates minEdgeLen, nRelaxedEdges

		if (controlMeshQuality())
		{
			PackedBoolList isErrorPoint(newMesh.nPoints());
			nBadFaces = edgeCollapser::checkMeshQuality
			(
				newMesh,
				meshQualityCoeffDict(),
				isErrorPoint
			);

			Info << nl << "    Number of bad faces     : " << nBadFaces << nl
				<< "    Number of marked points : "
				<< returnReduce(isErrorPoint.count(), sumOp<unsigned int>())
				<< endl;

			updatePointErrorCount
			(
				isErrorPoint,
				origToCurrentPointMap,
				pointErrorCount
			);

			checkMeshEdgesAndRelaxEdges
			(
				newMesh,
				origToCurrentPointMap,
				isErrorPoint,
				pointErrorCount
			);

			checkMeshFacesAndRelaxEdges
			(
				newMesh,
				origToCurrentPointMap,
				isErrorPoint,
				pointErrorCount
			);

			newBadFaces = false;
			forAll(mesh_.points(), pI)
			{
				if
					(
						origToCurrentPointMap[pI] >= 0
						&& isErrorPoint[origToCurrentPointMap[pI]]
						)
				{
					if (!newErrorPoint[pI])
					{
						newBadFaces = true;
						break;
					}
				}
			}

			reduce(newBadFaces, orOp<bool>());
		}
		else
		{
			return -1;
		}
	}

	return nBadFaces;
}


tnbLib::label tnbLib::polyMeshFilter::filterFaces
(
	polyMesh& newMesh,
	scalarField& newMeshFaceFilterFactor,
	labelList& origToCurrentPointMap
)
{
	// Per edge collapse status
	PackedBoolList collapseEdge(newMesh.nEdges());

	Map<point> collapsePointToLocation(newMesh.nPoints());

	edgeCollapser collapser(newMesh, collapseFacesCoeffDict());

	{
		// Collapse faces
		labelPair nCollapsedPtEdge = collapser.markSmallSliverFaces
		(
			newMeshFaceFilterFactor,
			pointPriority_(),
			collapseEdge,
			collapsePointToLocation
		);

		label nCollapsed = 0;
		forAll(nCollapsedPtEdge, collapseTypeI)
		{
			nCollapsed += nCollapsedPtEdge[collapseTypeI];
		}

		reduce(nCollapsed, sumOp<label>());

		label nToPoint = returnReduce(nCollapsedPtEdge.first(), sumOp<label>());
		label nToEdge = returnReduce(nCollapsedPtEdge.second(), sumOp<label>());

		Info << indent
			<< "Collapsing " << nCollapsed << " faces "
			<< "(to point = " << nToPoint << ", to edge = " << nToEdge << ")"
			<< endl;

		if (nCollapsed == 0)
		{
			return 0;
		}
	}

	// Merge edge collapses into consistent collapse-network.
	// Make sure no cells get collapsed.
	List<pointEdgeCollapse> allPointInfo;
	const globalIndex globalPoints(newMesh.nPoints());

	collapser.consistentCollapse
	(
		globalPoints,
		pointPriority_(),
		collapsePointToLocation,
		collapseEdge,
		allPointInfo
	);

	label nLocalCollapse = collapseEdge.count();

	reduce(nLocalCollapse, sumOp<label>());
	Info << nl << indent << "Collapsing " << nLocalCollapse
		<< " edges after synchronisation and PointEdgeWave" << endl;

	if (nLocalCollapse == 0)
	{
		return 0;
	}

	{
		// Apply collapses to current mesh
		polyTopoChange newMeshMod(newMesh);

		// Insert mesh refinement into polyTopoChange.
		collapser.setRefinement(allPointInfo, newMeshMod);

		Info << indent << "Apply changes to the current mesh" << endl;

		// Apply changes to current mesh
		autoPtr<mapPolyMesh> newMapPtr = newMeshMod.changeMesh
		(
			newMesh,
			false
		);
		const mapPolyMesh& newMap = newMapPtr();

		// Update fields
		newMesh.updateMesh(newMap);
		if (newMap.hasMotionPoints())
		{
			newMesh.movePoints(newMap.preMotionPoints());
		}
		updateSets(newMap);

		updatePointPriorities(newMesh, newMap.pointMap());

		mapOldMeshFaceFieldToNewMesh
		(
			newMesh,
			newMap.faceMap(),
			newMeshFaceFilterFactor
		);

		updateOldToNewPointMap
		(
			newMap.reversePointMap(),
			origToCurrentPointMap
		);
	}

	return nLocalCollapse;
}


tnbLib::label tnbLib::polyMeshFilter::filterEdges
(
	polyMesh& newMesh,
	scalarField& newMeshMinEdgeLen,
	labelList& origToCurrentPointMap
)
{
	// Per edge collapse status
	PackedBoolList collapseEdge(newMesh.nEdges());

	Map<point> collapsePointToLocation(newMesh.nPoints());

	edgeCollapser collapser(newMesh, collapseFacesCoeffDict());

	// Work out which edges to collapse
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// This is by looking at minEdgeLen (to avoid frozen edges)
	// and marking in collapseEdge.
	label nSmallCollapsed = collapser.markSmallEdges
	(
		newMeshMinEdgeLen,
		pointPriority_(),
		collapseEdge,
		collapsePointToLocation
	);

	reduce(nSmallCollapsed, sumOp<label>());
	Info << indent << "Collapsing " << nSmallCollapsed
		<< " small edges" << endl;

	// Merge inline edges
	label nMerged = collapser.markMergeEdges
	(
		maxCos(),
		pointPriority_(),
		collapseEdge,
		collapsePointToLocation
	);

	reduce(nMerged, sumOp<label>());
	Info << indent << "Collapsing " << nMerged << " in line edges"
		<< endl;

	if (nMerged + nSmallCollapsed == 0)
	{
		return 0;
	}

	// Merge edge collapses into consistent collapse-network.
	// Make sure no cells get collapsed.
	List<pointEdgeCollapse> allPointInfo;
	const globalIndex globalPoints(newMesh.nPoints());

	collapser.consistentCollapse
	(
		globalPoints,
		pointPriority_(),
		collapsePointToLocation,
		collapseEdge,
		allPointInfo
	);

	label nLocalCollapse = collapseEdge.count();

	reduce(nLocalCollapse, sumOp<label>());
	Info << nl << indent << "Collapsing " << nLocalCollapse
		<< " edges after synchronisation and PointEdgeWave" << endl;

	if (nLocalCollapse == 0)
	{
		return 0;
	}

	// Apply collapses to current mesh
	polyTopoChange newMeshMod(newMesh);

	// Insert mesh refinement into polyTopoChange.
	collapser.setRefinement(allPointInfo, newMeshMod);

	Info << indent << "Apply changes to the current mesh" << endl;

	// Apply changes to current mesh
	autoPtr<mapPolyMesh> newMapPtr = newMeshMod.changeMesh
	(
		newMesh,
		false
	);
	const mapPolyMesh& newMap = newMapPtr();

	// Update fields
	newMesh.updateMesh(newMap);
	if (newMap.hasMotionPoints())
	{
		newMesh.movePoints(newMap.preMotionPoints());
	}
	updateSets(newMap);

	// Synchronise the factors
	mapOldMeshEdgeFieldToNewMesh
	(
		newMesh,
		newMap.pointMap(),
		newMeshMinEdgeLen
	);

	updateOldToNewPointMap
	(
		newMap.reversePointMap(),
		origToCurrentPointMap
	);

	updatePointPriorities(newMesh, newMap.pointMap());

	return nLocalCollapse;
}


void tnbLib::polyMeshFilter::updatePointErrorCount
(
	const PackedBoolList& isErrorPoint,
	const labelList& oldToNewMesh,
	labelList& pointErrorCount
) const
{
	forAll(mesh_.points(), pI)
	{
		if (isErrorPoint[oldToNewMesh[pI]])
		{
			pointErrorCount[pI]++;
		}
	}
}


void tnbLib::polyMeshFilter::checkMeshEdgesAndRelaxEdges
(
	const polyMesh& newMesh,
	const labelList& oldToNewMesh,
	const PackedBoolList& isErrorPoint,
	const labelList& pointErrorCount
)
{
	const edgeList& edges = mesh_.edges();

	forAll(edges, edgeI)
	{
		const edge& e = edges[edgeI];
		label newStart = oldToNewMesh[e[0]];
		label newEnd = oldToNewMesh[e[1]];

		if
			(
				pointErrorCount[e[0]] >= maxPointErrorCount()
				|| pointErrorCount[e[1]] >= maxPointErrorCount()
				)
		{
			minEdgeLen_[edgeI] = -1;
		}

		if
			(
			(newStart >= 0 && isErrorPoint[newStart])
				|| (newEnd >= 0 && isErrorPoint[newEnd])
				)
		{
			minEdgeLen_[edgeI] *= edgeReductionFactor();
		}
	}

	syncTools::syncEdgeList(mesh_, minEdgeLen_, minEqOp<scalar>(), scalar(0));

	for (label smoothIter = 0; smoothIter < maxSmoothIters(); ++smoothIter)
	{
		// Smooth minEdgeLen
		forAll(mesh_.edges(), edgeI)
		{
			const edge& e = mesh_.edges()[edgeI];

			scalar sumMinEdgeLen = 0;
			label nEdges = 0;

			forAll(e, pointi)
			{
				const labelList& pEdges = mesh_.pointEdges()[e[pointi]];

				forAll(pEdges, pEdgeI)
				{
					const label pEdge = pEdges[pEdgeI];
					sumMinEdgeLen += minEdgeLen_[pEdge];
					nEdges++;
				}
			}

			minEdgeLen_[edgeI] = min
			(
				minEdgeLen_[edgeI],
				sumMinEdgeLen / nEdges
			);
		}

		syncTools::syncEdgeList
		(
			mesh_,
			minEdgeLen_,
			minEqOp<scalar>(),
			scalar(0)
		);
	}
}


void tnbLib::polyMeshFilter::checkMeshFacesAndRelaxEdges
(
	const polyMesh& newMesh,
	const labelList& oldToNewMesh,
	const PackedBoolList& isErrorPoint,
	const labelList& pointErrorCount
)
{
	const faceList& faces = mesh_.faces();

	forAll(faces, facei)
	{
		const face& f = faces[facei];

		forAll(f, fpI)
		{
			const label ptIndex = oldToNewMesh[f[fpI]];

			if (pointErrorCount[f[fpI]] >= maxPointErrorCount())
			{
				faceFilterFactor_[facei] = -1;
			}

			if (isErrorPoint[ptIndex])
			{
				faceFilterFactor_[facei] *= faceReductionFactor();

				break;
			}
		}
	}

	syncTools::syncFaceList(mesh_, faceFilterFactor_, minEqOp<scalar>());

	for (label smoothIter = 0; smoothIter < maxSmoothIters(); ++smoothIter)
	{
		// Smooth faceFilterFactor
		forAll(faces, facei)
		{
			const labelList& fEdges = mesh_.faceEdges()[facei];

			scalar sumFaceFilterFactors = 0;
			label nFaces = 0;

			// This is important: Only smooth around faces that share an
			// edge with a bad face
			bool skipFace = true;

			forAll(fEdges, fEdgeI)
			{
				const labelList& eFaces = mesh_.edgeFaces()[fEdges[fEdgeI]];

				forAll(eFaces, eFacei)
				{
					const label eFace = eFaces[eFacei];

					const face& f = faces[eFace];

					forAll(f, fpI)
					{
						const label ptIndex = oldToNewMesh[f[fpI]];

						if (isErrorPoint[ptIndex])
						{
							skipFace = false;
							break;
						}
					}

					if (eFace != facei)
					{
						sumFaceFilterFactors += faceFilterFactor_[eFace];
						nFaces++;
					}
				}
			}

			if (skipFace)
			{
				continue;
			}

			faceFilterFactor_[facei] = min
			(
				faceFilterFactor_[facei],
				sumFaceFilterFactors / nFaces
			);
		}

		// Face filter factor needs to be synchronised!
		syncTools::syncFaceList(mesh_, faceFilterFactor_, minEqOp<scalar>());
	}
}


void tnbLib::polyMeshFilter::updatePointPriorities
(
	const polyMesh& newMesh,
	const labelList& pointMap
)
{
	labelList newPointPriority(newMesh.nPoints(), labelMin);
	const labelList& currPointPriority = pointPriority_();

	forAll(newPointPriority, ptI)
	{
		const label newPointToOldPoint = pointMap[ptI];
		const label origPointPriority = currPointPriority[newPointToOldPoint];

		newPointPriority[ptI] = max(origPointPriority, newPointPriority[ptI]);
	}

	syncTools::syncPointList
	(
		newMesh,
		newPointPriority,
		maxEqOp<label>(),
		labelMin
	);

	pointPriority_.reset(new labelList(newPointPriority));
}


void tnbLib::polyMeshFilter::printScalarFieldStats
(
	const string desc,
	const scalarField& fld
) const
{
	scalar sum = 0;
	scalar validElements = 0;
	scalar min = great;
	scalar max = -great;

	forAll(fld, i)
	{
		const scalar fldElement = fld[i];

		if (fldElement >= 0)
		{
			sum += fldElement;

			if (fldElement < min)
			{
				min = fldElement;
			}

			if (fldElement > max)
			{
				max = fldElement;
			}

			validElements++;
		}
	}

	reduce(sum, sumOp<scalar>());
	reduce(min, minOp<scalar>());
	reduce(max, maxOp<scalar>());
	reduce(validElements, sumOp<label>());
	const label totFieldSize = returnReduce(fld.size(), sumOp<label>());

	Info << incrIndent << indent << desc
		<< ": min = " << min
		<< " av = " << sum / (validElements + small)
		<< " max = " << max << nl
		<< indent
		<< "    " << validElements << " / " << totFieldSize << " elements used"
		<< decrIndent << endl;
}


void tnbLib::polyMeshFilter::mapOldMeshEdgeFieldToNewMesh
(
	const polyMesh& newMesh,
	const labelList& pointMap,
	scalarField& newMeshMinEdgeLen
) const
{
	scalarField tmp(newMesh.nEdges());

	const edgeList& newEdges = newMesh.edges();

	forAll(newEdges, newEdgeI)
	{
		const edge& newEdge = newEdges[newEdgeI];
		const label pStart = newEdge.start();
		const label pEnd = newEdge.end();

		tmp[newEdgeI] = min
		(
			newMeshMinEdgeLen[pointMap[pStart]],
			newMeshMinEdgeLen[pointMap[pEnd]]
		);
	}

	newMeshMinEdgeLen.transfer(tmp);

	syncTools::syncEdgeList
	(
		newMesh,
		newMeshMinEdgeLen,
		maxEqOp<scalar>(),
		scalar(0)
	);
}


void tnbLib::polyMeshFilter::mapOldMeshFaceFieldToNewMesh
(
	const polyMesh& newMesh,
	const labelList& faceMap,
	scalarField& newMeshFaceFilterFactor
) const
{
	scalarField tmp(newMesh.nFaces());

	forAll(faceMap, newFacei)
	{
		const label oldFacei = faceMap[newFacei];

		tmp[newFacei] = newMeshFaceFilterFactor[oldFacei];
	}

	newMeshFaceFilterFactor.transfer(tmp);

	syncTools::syncFaceList
	(
		newMesh,
		newMeshFaceFilterFactor,
		maxEqOp<scalar>()
	);
}


void tnbLib::polyMeshFilter::updateOldToNewPointMap
(
	const labelList& currToNew,
	labelList& origToCurrentPointMap
) const
{
	forAll(origToCurrentPointMap, origPointi)
	{
		label oldPointi = origToCurrentPointMap[origPointi];

		if (oldPointi != -1)
		{
			label newPointi = currToNew[oldPointi];

			if (newPointi >= 0)
			{
				origToCurrentPointMap[origPointi] = newPointi;
			}
			else if (newPointi == -1)
			{
				origToCurrentPointMap[origPointi] = -1;
			}
			else
			{
				origToCurrentPointMap[origPointi] = -newPointi - 2;
			}
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::polyMeshFilter::polyMeshFilter(const fvMesh& mesh)
	:
	polyMeshFilterSettings
	(
		IOdictionary
		(
			IOobject
			(
				"collapseDict",
				mesh.time().system(),
				mesh.time(),
				IOobject::MUST_READ,
				IOobject::NO_WRITE
			)
		)
	),
	mesh_(mesh),
	newMeshPtr_(),
	originalPointPriority_(mesh.nPoints(), labelMin),
	pointPriority_(),
	minEdgeLen_(),
	faceFilterFactor_()
{
	writeSettings(Info);
}


tnbLib::polyMeshFilter::polyMeshFilter
(
	const fvMesh& mesh,
	const labelList& pointPriority
)
	:
	polyMeshFilterSettings
	(
		IOdictionary
		(
			IOobject
			(
				"collapseDict",
				mesh.time().system(),
				mesh.time(),
				IOobject::MUST_READ,
				IOobject::NO_WRITE
			)
		)
	),
	mesh_(mesh),
	newMeshPtr_(),
	originalPointPriority_(pointPriority),
	pointPriority_(),
	minEdgeLen_(),
	faceFilterFactor_()
{
	writeSettings(Info);
}

tnbLib::polyMeshFilter::polyMeshFilter
(
	const fvMesh& mesh,
	const labelList& pointPriority,
	const dictionary& dict
)
	:
	polyMeshFilterSettings(dict),
	mesh_(mesh),
	newMeshPtr_(),
	originalPointPriority_(pointPriority),
	pointPriority_(),
	minEdgeLen_(),
	faceFilterFactor_()
{
	writeSettings(Info);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::polyMeshFilter::~polyMeshFilter()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

tnbLib::label tnbLib::polyMeshFilter::filter(const label nOriginalBadFaces)
{
	minEdgeLen_.resize(mesh_.nEdges(), minLen());
	faceFilterFactor_.resize(mesh_.nFaces(), initialFaceLengthFactor());

	return filterFacesLoop(nOriginalBadFaces);
}


tnbLib::label tnbLib::polyMeshFilter::filter(const faceSet& fSet)
{
	minEdgeLen_.resize(mesh_.nEdges(), minLen());
	faceFilterFactor_.resize(mesh_.nFaces(), initialFaceLengthFactor());

	forAll(faceFilterFactor_, fI)
	{
		if (!fSet.found(fI))
		{
			faceFilterFactor_[fI] = -1;
		}
	}

	return filterFacesLoop(0);
}


tnbLib::label tnbLib::polyMeshFilter::filterEdges
(
	const label nOriginalBadFaces
)
{
	label nBadFaces = labelMax / 2;
	label nPreviousBadFaces = labelMax;
	label nOuterIterations = 0;

	minEdgeLen_.resize(mesh_.nEdges(), minLen());
	faceFilterFactor_.resize(0);

	labelList pointErrorCount(mesh_.nPoints(), 0);

	// Main loop
	// ~~~~~~~~~
	// It tries and do some collapses, checks the resulting mesh and
	// 'freezes' some edges (by marking in minEdgeLen) and tries again.
	// This will iterate ultimately to the situation where every edge is
	// frozen and nothing gets collapsed.
	while
		(
			nOuterIterations < maxIterations()
			&& nBadFaces > nOriginalBadFaces
			&& nBadFaces < nPreviousBadFaces
			)
	{
		Info << nl << "Outer Iteration = " << nOuterIterations++ << nl
			<< endl;

		printScalarFieldStats("Edge Filter Factor", minEdgeLen_);

		nPreviousBadFaces = nBadFaces;

		// Reset the new mesh to the old mesh
		newMeshPtr_ = copyMesh(mesh_);
		fvMesh& newMesh = newMeshPtr_();

		scalarField newMeshMinEdgeLen = minEdgeLen_;
		pointPriority_.reset(new labelList(originalPointPriority_));

		labelList origToCurrentPointMap(identity(newMesh.nPoints()));

		Info << incrIndent;

		label nInnerIterations = 0;
		label nPrevLocalCollapse = labelMax;

		while (true)
		{
			Info << nl
				<< indent << "Inner iteration = " << nInnerIterations++ << nl
				<< incrIndent << endl;

			label nLocalCollapse = filterEdges
			(
				newMesh,
				newMeshMinEdgeLen,
				origToCurrentPointMap
			);

			Info << decrIndent;

			if
				(
					nLocalCollapse >= nPrevLocalCollapse
					|| nLocalCollapse == 0
					)
			{
				Info << decrIndent;
				break;
			}
			else
			{
				nPrevLocalCollapse = nLocalCollapse;
			}
		}

		// Mesh check
		// ~~~~~~~~~~~~~~~~~~
		// Do not allow collapses in regions of error.
		// Updates minEdgeLen, nRelaxedEdges

		if (controlMeshQuality())
		{
			PackedBoolList isErrorPoint(newMesh.nPoints());
			nBadFaces = edgeCollapser::checkMeshQuality
			(
				newMesh,
				meshQualityCoeffDict(),
				isErrorPoint
			);

			Info << nl << "    Number of bad faces     : " << nBadFaces << nl
				<< "    Number of marked points : "
				<< returnReduce(isErrorPoint.count(), sumOp<unsigned int>())
				<< endl;

			updatePointErrorCount
			(
				isErrorPoint,
				origToCurrentPointMap,
				pointErrorCount
			);

			checkMeshEdgesAndRelaxEdges
			(
				newMesh,
				origToCurrentPointMap,
				isErrorPoint,
				pointErrorCount
			);
		}
		else
		{
			return -1;
		}
	}

	return nBadFaces;
}


const tnbLib::autoPtr<tnbLib::fvMesh>& tnbLib::polyMeshFilter::filteredMesh() const
{
	return newMeshPtr_;
}


const tnbLib::autoPtr<tnbLib::labelList>&
tnbLib::polyMeshFilter::pointPriority() const
{
	return pointPriority_;
}


// ************************************************************************* //