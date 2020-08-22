#include <faceCollapser.hxx>

#include <polyMesh.hxx>
#include <polyTopoChange.hxx>
#include <polyModifyPoint.hxx>
#include <polyModifyFace.hxx>
#include <polyRemoveFace.hxx>
#include <SortableList.hxx>
#include <meshTools.hxx>
#include <OFstream.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

// Insert labelList into labelHashSet. Optional excluded element.
void tnbLib::faceCollapser::insert
(
	const labelList& elems,
	const label excludeElem,
	labelHashSet& set
)
{
	forAll(elems, i)
	{
		if (elems[i] != excludeElem)
		{
			set.insert(elems[i]);
		}
	}
}


// Find edge amongst candidate edges. FatalError if none.
tnbLib::label tnbLib::faceCollapser::findEdge
(
	const edgeList& edges,
	const labelList& edgeLabels,
	const label v0,
	const label v1
)
{
	forAll(edgeLabels, i)
	{
		label edgeI = edgeLabels[i];

		const edge& e = edges[edgeI];

		if
			(
			(e[0] == v0 && e[1] == v1)
				|| (e[0] == v1 && e[1] == v0)
				)
		{
			return edgeI;
		}
	}

	FatalErrorInFunction
		<< " and " << v1 << " in edge labels " << edgeLabels
		<< abort(FatalError);

	return -1;
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

// Replace vertices in face
void tnbLib::faceCollapser::filterFace
(
	const Map<labelList>& splitEdges,
	const label facei,
	polyTopoChange& meshMod
) const
{
	const face& f = mesh_.faces()[facei];
	const labelList& fEdges = mesh_.faceEdges()[facei];

	// Space for replaced vertices and split edges.
	DynamicList<label> newFace(10 * f.size());

	forAll(f, fp)
	{
		label v0 = f[fp];

		newFace.append(v0);

		// Look ahead one to get edge.
		label fp1 = f.fcIndex(fp);

		label v1 = f[fp1];

		// Get split on edge if any.
		label edgeI = findEdge(mesh_.edges(), fEdges, v0, v1);

		Map<labelList>::const_iterator edgeFnd =
			splitEdges.find(edgeI);

		if (edgeFnd != splitEdges.end())
		{
			// edgeI has been split (by introducing new vertices).
			// Insert new vertices in face in correct order
			// (splitEdges was constructed to be from edge.start() to end())

			const labelList& extraVerts = edgeFnd();

			if (v0 == mesh_.edges()[edgeI].start())
			{
				forAll(extraVerts, i)
				{
					newFace.append(extraVerts[i]);
				}
			}
			else
			{
				forAllReverse(extraVerts, i)
				{
					newFace.append(extraVerts[i]);
				}
			}
		}
	}
	face newF(newFace.shrink());

	// Pout<< "Modifying face:" << facei << " from " << f << " to " << newFace
	//    << endl;

	if (newF != f)
	{
		label nei = -1;

		label patchi = -1;

		if (mesh_.isInternalFace(facei))
		{
			nei = mesh_.faceNeighbour()[facei];
		}
		else
		{
			patchi = mesh_.boundaryMesh().whichPatch(facei);
		}

		// Get current zone info
		label zoneID = mesh_.faceZones().whichZone(facei);

		bool zoneFlip = false;

		if (zoneID >= 0)
		{
			const faceZone& fZone = mesh_.faceZones()[zoneID];

			zoneFlip = fZone.flipMap()[fZone.whichFace(facei)];
		}

		meshMod.setAction
		(
			polyModifyFace
			(
				newF,                       // modified face
				facei,                      // label of face being modified
				mesh_.faceOwner()[facei],   // owner
				nei,                        // neighbour
				false,                      // face flip
				patchi,                     // patch for face
				false,                      // remove from zone
				zoneID,                     // zone for face
				zoneFlip                    // face flip in zone
			)
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Construct from mesh
tnbLib::faceCollapser::faceCollapser(const polyMesh& mesh)
	:
	mesh_(mesh)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::faceCollapser::setRefinement
(
	const labelList& faceLabels,
	const labelList& fpStart,
	const labelList& fpEnd,
	polyTopoChange& meshMod
) const
{
	const pointField& points = mesh_.points();
	const edgeList& edges = mesh_.edges();
	const faceList& faces = mesh_.faces();
	const labelListList& edgeFaces = mesh_.edgeFaces();


	// From split edge to newly introduced point(s). Can be more than one per
	// edge!
	Map<labelList> splitEdges(faceLabels.size());

	// Mark faces in any way affect by modifying points/edges. Used later on
	// to prevent having to redo all faces.
	labelHashSet affectedFaces(4 * faceLabels.size());


	//
	// Add/remove vertices and construct mapping
	//

	forAll(faceLabels, i)
	{
		const label facei = faceLabels[i];

		const face& f = faces[facei];

		const label fpA = fpStart[i];
		const label fpB = fpEnd[i];

		const point& pA = points[f[fpA]];
		const point& pB = points[f[fpB]];

		Pout << "Face:" << f << " collapsed to fp:" << fpA << ' ' << fpB
			<< " with points:" << pA << ' ' << pB
			<< endl;

		// Create line from fpA to fpB
		linePointRef lineAB(pA, pB);

		// Get projections of all vertices onto line.

		// Distance(squared) to pA for every point on face.
		SortableList<scalar> dist(f.size());

		dist[fpA] = 0;
		dist[fpB] = magSqr(pB - pA);

		// Step from fpA to fpB
		// ~~~~~~~~~~~~~~~~~~~~
		// (by incrementing)

		label fpMin1 = fpA;
		label fp = f.fcIndex(fpMin1);

		while (fp != fpB)
		{
			// See where fp sorts. Make sure it is above fpMin1!
			pointHit near = lineAB.nearestDist(points[f[fp]]);

			scalar w = magSqr(near.rawPoint() - pA);

			if (w <= dist[fpMin1])
			{
				// Offset.
				w = dist[fpMin1] + 1e-6*(dist[fpB] - dist[fpA]);

				point newPoint
				(
					pA + tnbLib::sqrt(w / (dist[fpB] - dist[fpA]))*(pB - pA)
				);

				Pout << "Adapting position of vertex " << f[fp] << " on face "
					<< f << " from " << near.rawPoint() << " to " << newPoint
					<< endl;

				near.setPoint(newPoint);
			}

			// Responsibility of caller to make sure polyModifyPoint is only
			// called once per point. (so max only one collapse face per
			// edge)
			meshMod.setAction
			(
				polyModifyPoint
				(
					f[fp],
					near.rawPoint(),
					false,
					-1,
					true
				)
			);

			dist[fp] = w;

			// Step to next vertex.
			fpMin1 = fp;
			fp = f.fcIndex(fpMin1);
		}

		// Step from fpA to fpB
		// ~~~~~~~~~~~~~~~~~~~~
		// (by decrementing)

		fpMin1 = fpA;
		fp = f.rcIndex(fpMin1);

		while (fp != fpB)
		{
			// See where fp sorts. Make sure it is below fpMin1!
			pointHit near = lineAB.nearestDist(points[f[fp]]);

			scalar w = magSqr(near.rawPoint() - pA);

			if (w <= dist[fpMin1])
			{
				// Offset.
				w = dist[fpMin1] + 1e-6*(dist[fpB] - dist[fpA]);

				point newPoint
				(
					pA + tnbLib::sqrt(w / (dist[fpB] - dist[fpA]))*(pB - pA)
				);

				Pout << "Adapting position of vertex " << f[fp] << " on face "
					<< f << " from " << near.rawPoint() << " to " << newPoint
					<< endl;

				near.setPoint(newPoint);
			}

			// Responsibility of caller to make sure polyModifyPoint is only
			// called once per point. (so max only one collapse face per
			// edge)
			meshMod.setAction
			(
				polyModifyPoint
				(
					f[fp],
					near.rawPoint(),
					false,
					-1,
					true
				)
			);

			dist[fp] = w;

			// Step to previous vertex.
			fpMin1 = fp;
			fp = f.rcIndex(fpMin1);
		}

		dist.sort();

		// Check that fpB sorts latest.
		if (dist.indices()[dist.size() - 1] != fpB)
		{
			OFstream str("conflictingFace.obj");
			meshTools::writeOBJ(str, faceList(1, f), points);

			FatalErrorInFunction
				<< "Trying to collapse face:" << facei << " vertices:" << f
				<< " to edges between vertices " << f[fpA] << " and "
				<< f[fpB] << " but " << f[fpB] << " does not seem to be the"
				<< " vertex furthest away from " << f[fpA] << endl
				<< "Dumped conflicting face to obj file conflictingFace.obj"
				<< abort(FatalError);
		}


		// From fp to index in sort:
		Pout << "Face:" << f << " fpA:" << fpA << " fpB:" << fpB << nl;

		labelList sortedFp(f.size());
		forAll(dist.indices(), i)
		{
			label fp = dist.indices()[i];

			Pout << "   fp:" << fp << " distance:" << dist[i] << nl;

			sortedFp[fp] = i;
		}

		const labelList& fEdges = mesh_.faceEdges()[facei];

		// Now look up all edges in the face and see if they get extra
		// vertices inserted and build an edge-to-intersected-points table.

		// Order of inserted points is in edge order (from e.start to
		// e.end)

		forAll(f, fp)
		{
			label fp1 = f.fcIndex(fp);

			// Get index in sorted list
			label sorted0 = sortedFp[fp];
			label sorted1 = sortedFp[fp1];

			// Get indices in increasing order
			DynamicList<label> edgePoints(f.size());

			// Whether edgePoints are from fp to fp1
			bool fpToFp1;

			if (sorted0 < sorted1)
			{
				fpToFp1 = true;

				for (label j = sorted0 + 1; j < sorted1; j++)
				{
					edgePoints.append(f[dist.indices()[j]]);
				}
			}
			else
			{
				fpToFp1 = false;

				for (label j = sorted1 + 1; j < sorted0; j++)
				{
					edgePoints.append(f[dist.indices()[j]]);
				}
			}

			if (edgePoints.size())
			{
				edgePoints.shrink();

				label edgeI = findEdge(edges, fEdges, f[fp], f[fp1]);

				const edge& e = edges[edgeI];

				if (fpToFp1 == (f[fp] == e.start()))
				{
					splitEdges.insert(edgeI, edgePoints);
				}
				else
				{
					reverse(edgePoints);
					splitEdges.insert(edgeI, edgePoints);
				}

				// Mark all faces affected
				insert(edgeFaces[edgeI], facei, affectedFaces);
			}
		}
	}

	forAllConstIter(Map<labelList>, splitEdges, iter)
	{
		Pout << "Split edge:" << iter.key()
			<< " verts:" << mesh_.edges()[iter.key()]
			<< " in:" << nl;
		const labelList& edgePoints = iter();

		forAll(edgePoints, i)
		{
			Pout << "    " << edgePoints[i] << nl;
		}
	}


	//
	// Remove faces.
	//

	forAll(faceLabels, i)
	{
		const label facei = faceLabels[i];

		meshMod.setAction(polyRemoveFace(facei));

		// Update list of faces we still have to modify
		affectedFaces.erase(facei);
	}


	//
	// Modify faces affected (but not removed)
	//

	forAllConstIter(labelHashSet, affectedFaces, iter)
	{
		filterFace(splitEdges, iter.key(), meshMod);
	}
}


// ************************************************************************* //