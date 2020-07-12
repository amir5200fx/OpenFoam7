#include <surfaceIntersection.hxx>

#include <triSurfaceSearch.hxx>
#include <labelPairLookup.hxx>
#include <OFstream.hxx>
#include <HashSet.hxx>
#include <triSurface.hxx>
#include <pointIndexHit.hxx>
#include <meshTools.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::surfaceIntersection::writeOBJ(const point& pt, Ostream& os)
{
	os << "v " << pt.x() << ' ' << pt.y() << ' ' << pt.z() << endl;
}


void tnbLib::surfaceIntersection::writeOBJ
(
	const List<point>& pts,
	const List<edge>& edges,
	Ostream& os
)
{
	forAll(pts, i)
	{
		writeOBJ(pts[i], os);
	}
	forAll(edges, i)
	{
		const edge& e = edges[i];

		os << "l " << e.start() + 1 << ' ' << e.end() + 1 << endl;
	}
}


// Get minimum length of all edges connected to point
tnbLib::scalar tnbLib::surfaceIntersection::minEdgeLen
(
	const triSurface& surf,
	const label pointi
)
{
	const labelList& pEdges = surf.pointEdges()[pointi];

	scalar minLen = great;

	forAll(pEdges, pEdgeI)
	{
		const edge& e = surf.edges()[pEdges[pEdgeI]];

		minLen = min(minLen, e.mag(surf.localPoints()));
	}

	return minLen;
}


// Get edge between fp and fp+1 on facei.
tnbLib::label tnbLib::surfaceIntersection::getEdge
(
	const triSurface& surf,
	const label facei,
	const label fp
)
{
	const edge faceEdge = surf.localFaces()[facei].faceEdge(fp);

	const labelList& eLabels = surf.faceEdges()[facei];

	forAll(eLabels, eI)
	{
		const label edgeI = eLabels[eI];

		if (surf.edges()[edgeI] == faceEdge)
		{
			return edgeI;
		}
	}

	FatalErrorInFunction
		<< "Problem:: Cannot find edge with vertices " << faceEdge
		<< " in face " << facei
		<< abort(FatalError);

	return -1;
}


// Given a map remove all consecutive duplicate elements.
void tnbLib::surfaceIntersection::removeDuplicates
(
	const labelList& map,
	labelList& elems
)
{
	bool hasDuplicate = false;

	label prevVertI = -1;

	forAll(elems, elemI)
	{
		label newVertI = map[elems[elemI]];

		if (newVertI == prevVertI)
		{
			hasDuplicate = true;

			break;
		}
		prevVertI = newVertI;
	}

	if (hasDuplicate)
	{
		// Create copy
		labelList oldElems(elems);

		label elemI = 0;

		// Insert first
		elems[elemI++] = map[oldElems[0]];

		for (label vertI = 1; vertI < oldElems.size(); vertI++)
		{
			// Insert others only if they differ from one before
			label newVertI = map[oldElems[vertI]];

			if (newVertI != elems.last())
			{
				elems[elemI++] = newVertI;
			}
		}
		elems.setSize(elemI);
	}
}


// Remap.
void tnbLib::surfaceIntersection::inlineRemap
(
	const labelList& map,
	labelList& elems
)
{
	forAll(elems, elemI)
	{
		elems[elemI] = map[elems[elemI]];
	}
}


// Remove all duplicate and degenerate elements. Return unique elements and
// map from old to new.
tnbLib::edgeList tnbLib::surfaceIntersection::filterEdges
(
	const edgeList& edges,
	labelList& map
)
{
	HashSet<edge, Hash<edge>> uniqueEdges(10 * edges.size());

	edgeList newEdges(edges.size());

	map.setSize(edges.size());
	map = -1;

	label newEdgeI = 0;

	forAll(edges, edgeI)
	{
		const edge& e = edges[edgeI];

		if
			(
			(e.start() != e.end())
				&& (uniqueEdges.find(e) == uniqueEdges.end())
				)
		{
			// Edge is -non degenerate and -not yet seen.
			uniqueEdges.insert(e);

			map[edgeI] = newEdgeI;

			newEdges[newEdgeI++] = e;
		}
	}

	newEdges.setSize(newEdgeI);

	return newEdges;
}


// Remove all duplicate elements.
tnbLib::labelList tnbLib::surfaceIntersection::filterLabels
(
	const labelList& elems,
	labelList& map
)
{
	labelHashSet uniqueElems(10 * elems.size());

	labelList newElems(elems.size());

	map.setSize(elems.size());
	map = -1;

	label newElemI = 0;

	forAll(elems, elemI)
	{
		label elem = elems[elemI];

		if (uniqueElems.find(elem) == uniqueElems.end())
		{
			// First time elem is seen
			uniqueElems.insert(elem);

			map[elemI] = newElemI;

			newElems[newElemI++] = elem;
		}
	}

	newElems.setSize(newElemI);

	return newElems;
}


void tnbLib::surfaceIntersection::writeIntersectedEdges
(
	const triSurface& surf,
	const labelListList& edgeCutVerts,
	Ostream& os
) const
{
	// Dump all points (surface followed by cutPoints)
	const pointField& pts = surf.localPoints();

	forAll(pts, pointi)
	{
		writeOBJ(pts[pointi], os);
	}
	forAll(cutPoints(), cutPointi)
	{
		writeOBJ(cutPoints()[cutPointi], os);
	}

	forAll(edgeCutVerts, edgeI)
	{
		const labelList& extraVerts = edgeCutVerts[edgeI];

		if (extraVerts.size())
		{
			const edge& e = surf.edges()[edgeI];

			// Start of original edge to first extra point
			os << "l " << e.start() + 1 << ' '
				<< extraVerts[0] + surf.nPoints() + 1 << endl;

			for (label i = 1; i < extraVerts.size(); i++)
			{
				os << "l " << extraVerts[i - 1] + surf.nPoints() + 1 << ' '
					<< extraVerts[i] + surf.nPoints() + 1 << endl;
			}

			os << "l " << extraVerts.last() + surf.nPoints() + 1
				<< ' ' << e.end() + 1 << endl;
		}
	}
}


// Return 0 (p close to start), 1(close to end) or -1.
tnbLib::label tnbLib::surfaceIntersection::classify
(
	const scalar startTol,
	const scalar endTol,
	const point& p,
	const edge& e,
	const pointField& points
)
{
	if (mag(p - points[e.start()]) < startTol)
	{
		return 0;
	}
	else if (mag(p - points[e.end()]) < endTol)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}


// ************************************************************************* //