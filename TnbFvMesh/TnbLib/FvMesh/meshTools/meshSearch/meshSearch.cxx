#include <meshSearch.hxx>

#include <polyMesh.hxx>
#include <indexedOctree.hxx>
#include <DynamicList.hxx>
#include <demandDrivenData.hxx>
#include <treeDataCell.hxx>
#include <treeDataFace.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(meshSearch, 0);

	scalar meshSearch::tol_ = 1e-3;

	// Intersection operation that checks previous successful hits so that they
	// are not duplicated
	class findUniqueIntersectOp
		:
		public treeDataFace::findIntersectOp
	{
	public:

		const indexedOctree<treeDataFace>& tree_;

		const List<pointIndexHit>& hits_;

	public:

		//- Construct from components
		findUniqueIntersectOp
		(
			const indexedOctree<treeDataFace>& tree,
			const List<pointIndexHit>& hits
		)
			:
			treeDataFace::findIntersectOp(tree),
			tree_(tree),
			hits_(hits)
		{}

		//- Calculate intersection of triangle with ray. Sets result
		//  accordingly
		bool operator()
			(
				const label index,
				const point& start,
				const point& end,
				point& intersectionPoint
				) const
		{
			const primitiveMesh& mesh = tree_.shapes().mesh();

			// Check whether this hit has already happened. If the new face
			// index is the same as an existing hit then return no new hit. If
			// the new face shares a point with an existing hit face and the
			// line passes through both faces in the same direction, then this
			// is also assumed to be a duplicate hit.
			const label newFacei = tree_.shapes().faceLabels()[index];
			const face& newFace = mesh.faces()[newFacei];
			const scalar newDot = mesh.faceAreas()[newFacei] & (end - start);
			forAll(hits_, hiti)
			{
				const label oldFacei = hits_[hiti].index();
				const face& oldFace = mesh.faces()[oldFacei];
				const scalar oldDot =
					mesh.faceAreas()[oldFacei] & (end - start);

				if
					(
						hits_[hiti].index() == newFacei
						|| (
							newDot*oldDot > 0
							&& (labelHashSet(newFace) & labelHashSet(oldFace)).size()
							)
						)
				{
					return false;
				}
			}

			const bool hit =
				treeDataFace::findIntersectOp::operator()
				(
					index,
					start,
					end,
					intersectionPoint
					);

			return hit;
		}
	};
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

bool tnbLib::meshSearch::findNearer
(
	const point& sample,
	const pointField& points,
	label& nearestI,
	scalar& nearestDistSqr
)
{
	bool nearer = false;

	forAll(points, pointi)
	{
		scalar distSqr = magSqr(points[pointi] - sample);

		if (distSqr < nearestDistSqr)
		{
			nearestDistSqr = distSqr;
			nearestI = pointi;
			nearer = true;
		}
	}

	return nearer;
}


bool tnbLib::meshSearch::findNearer
(
	const point& sample,
	const pointField& points,
	const labelList& indices,
	label& nearestI,
	scalar& nearestDistSqr
)
{
	bool nearer = false;

	forAll(indices, i)
	{
		label pointi = indices[i];

		scalar distSqr = magSqr(points[pointi] - sample);

		if (distSqr < nearestDistSqr)
		{
			nearestDistSqr = distSqr;
			nearestI = pointi;
			nearer = true;
		}
	}

	return nearer;
}


// tree based searching
tnbLib::label tnbLib::meshSearch::findNearestCellTree(const point& location) const
{
	const indexedOctree<treeDataCell>& tree = cellTree();

	pointIndexHit info = tree.findNearest
	(
		location,
		magSqr(tree.bb().max() - tree.bb().min())
	);

	if (!info.hit())
	{
		info = tree.findNearest(location, tnbLib::sqr(great));
	}
	return info.index();
}


tnbLib::label tnbLib::meshSearch::findNearestCellLinear(const point& location) const
{
	const vectorField& centres = mesh_.cellCentres();

	label nearestIndex = 0;
	scalar minProximity = magSqr(centres[nearestIndex] - location);

	findNearer
	(
		location,
		centres,
		nearestIndex,
		minProximity
	);

	return nearestIndex;
}


tnbLib::label tnbLib::meshSearch::findNearestCellWalk
(
	const point& location,
	const label seedCelli
) const
{
	if (seedCelli < 0)
	{
		FatalErrorInFunction
			<< "illegal seedCell:" << seedCelli << exit(FatalError);
	}

	// Walk in direction of face that decreases distance

	label curCelli = seedCelli;
	scalar distanceSqr = magSqr(mesh_.cellCentres()[curCelli] - location);

	bool closer;

	do
	{
		// Try neighbours of curCelli
		closer = findNearer
		(
			location,
			mesh_.cellCentres(),
			mesh_.cellCells()[curCelli],
			curCelli,
			distanceSqr
		);
	} while (closer);

	return curCelli;
}


tnbLib::label tnbLib::meshSearch::findNearestFaceTree(const point& location) const
{
	// Search nearest cell centre.
	const indexedOctree<treeDataCell>& tree = cellTree();

	// Search with decent span
	pointIndexHit info = tree.findNearest
	(
		location,
		magSqr(tree.bb().max() - tree.bb().min())
	);

	if (!info.hit())
	{
		// Search with desperate span
		info = tree.findNearest(location, tnbLib::sqr(great));
	}


	// Now check any of the faces of the nearest cell
	const vectorField& centres = mesh_.faceCentres();
	const cell& ownFaces = mesh_.cells()[info.index()];

	label nearestFacei = ownFaces[0];
	scalar minProximity = magSqr(centres[nearestFacei] - location);

	findNearer
	(
		location,
		centres,
		ownFaces,
		nearestFacei,
		minProximity
	);

	return nearestFacei;
}


tnbLib::label tnbLib::meshSearch::findNearestFaceLinear(const point& location) const
{
	const vectorField& centres = mesh_.faceCentres();

	label nearestFacei = 0;
	scalar minProximity = magSqr(centres[nearestFacei] - location);

	findNearer
	(
		location,
		centres,
		nearestFacei,
		minProximity
	);

	return nearestFacei;
}


tnbLib::label tnbLib::meshSearch::findNearestFaceWalk
(
	const point& location,
	const label seedFacei
) const
{
	if (seedFacei < 0)
	{
		FatalErrorInFunction
			<< "illegal seedFace:" << seedFacei << exit(FatalError);
	}

	const vectorField& centres = mesh_.faceCentres();


	// Walk in direction of face that decreases distance

	label curFacei = seedFacei;
	scalar distanceSqr = magSqr(centres[curFacei] - location);

	while (true)
	{
		label betterFacei = curFacei;

		findNearer
		(
			location,
			centres,
			mesh_.cells()[mesh_.faceOwner()[curFacei]],
			betterFacei,
			distanceSqr
		);

		if (mesh_.isInternalFace(curFacei))
		{
			findNearer
			(
				location,
				centres,
				mesh_.cells()[mesh_.faceNeighbour()[curFacei]],
				betterFacei,
				distanceSqr
			);
		}

		if (betterFacei == curFacei)
		{
			break;
		}

		curFacei = betterFacei;
	}

	return curFacei;
}


tnbLib::label tnbLib::meshSearch::findCellLinear(const point& location) const
{
	bool cellFound = false;
	label n = 0;

	label celli = -1;

	while ((!cellFound) && (n < mesh_.nCells()))
	{
		if (mesh_.pointInCell(location, n, cellDecompMode_))
		{
			cellFound = true;
			celli = n;
		}
		else
		{
			n++;
		}
	}
	if (cellFound)
	{
		return celli;
	}
	else
	{
		return -1;
	}
}


tnbLib::label tnbLib::meshSearch::findCellWalk
(
	const point& location,
	const label seedCelli
) const
{
	if (seedCelli < 0)
	{
		FatalErrorInFunction
			<< "illegal seedCell:" << seedCelli << exit(FatalError);
	}

	if (mesh_.pointInCell(location, seedCelli, cellDecompMode_))
	{
		return seedCelli;
	}

	// Walk in direction of face that decreases distance
	label curCelli = seedCelli;
	scalar nearestDistSqr = magSqr(mesh_.cellCentres()[curCelli] - location);

	while (true)
	{
		// Try neighbours of curCelli

		const cell& cFaces = mesh_.cells()[curCelli];

		label nearestCelli = -1;

		forAll(cFaces, i)
		{
			label facei = cFaces[i];

			if (mesh_.isInternalFace(facei))
			{
				label celli = mesh_.faceOwner()[facei];
				if (celli == curCelli)
				{
					celli = mesh_.faceNeighbour()[facei];
				}

				// Check if this is the correct cell
				if (mesh_.pointInCell(location, celli, cellDecompMode_))
				{
					return celli;
				}

				// Also calculate the nearest cell
				scalar distSqr = magSqr(mesh_.cellCentres()[celli] - location);

				if (distSqr < nearestDistSqr)
				{
					nearestDistSqr = distSqr;
					nearestCelli = celli;
				}
			}
		}

		if (nearestCelli == -1)
		{
			return -1;
		}

		// Continue with the nearest cell
		curCelli = nearestCelli;
	}

	return -1;
}


tnbLib::label tnbLib::meshSearch::findNearestBoundaryFaceWalk
(
	const point& location,
	const label seedFacei
) const
{
	if (seedFacei < 0)
	{
		FatalErrorInFunction
			<< "illegal seedFace:" << seedFacei << exit(FatalError);
	}

	// Start off from seedFacei

	label curFacei = seedFacei;

	const face& f = mesh_.faces()[curFacei];

	scalar minDist = f.nearestPoint
	(
		location,
		mesh_.points()
	).distance();

	bool closer;

	do
	{
		closer = false;

		// Search through all neighbouring boundary faces by going
		// across edges

		label lastFacei = curFacei;

		const labelList& myEdges = mesh_.faceEdges()[curFacei];

		forAll(myEdges, myEdgeI)
		{
			const labelList& neighbours = mesh_.edgeFaces()[myEdges[myEdgeI]];

			// Check any face which uses edge, is boundary face and
			// is not curFacei itself.

			forAll(neighbours, nI)
			{
				label facei = neighbours[nI];

				if
					(
					(facei >= mesh_.nInternalFaces())
						&& (facei != lastFacei)
						)
				{
					const face& f = mesh_.faces()[facei];

					pointHit curHit = f.nearestPoint
					(
						location,
						mesh_.points()
					);

					// If the face is closer, reset current face and distance
					if (curHit.distance() < minDist)
					{
						minDist = curHit.distance();
						curFacei = facei;
						closer = true;  // a closer neighbour has been found
					}
				}
			}
		}
	} while (closer);

	return curFacei;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::meshSearch::meshSearch
(
	const polyMesh& mesh,
	const polyMesh::cellDecomposition cellDecompMode
)
	:
	mesh_(mesh),
	cellDecompMode_(cellDecompMode)
{
	if
		(
			cellDecompMode_ == polyMesh::FACE_DIAG_TRIS
			|| cellDecompMode_ == polyMesh::CELL_TETS)
	{
		// Force construction of face diagonals
		(void)mesh.tetBasePtIs();
	}
}


tnbLib::meshSearch::meshSearch
(
	const polyMesh& mesh,
	const treeBoundBox& bb,
	const polyMesh::cellDecomposition cellDecompMode
)
	:
	mesh_(mesh),
	cellDecompMode_(cellDecompMode)
{
	overallBbPtr_.reset(new treeBoundBox(bb));

	if
		(
			cellDecompMode_ == polyMesh::FACE_DIAG_TRIS
			|| cellDecompMode_ == polyMesh::CELL_TETS
			)
	{
		// Force construction of face diagonals
		(void)mesh.tetBasePtIs();
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::meshSearch::~meshSearch()
{
	clearOut();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::indexedOctree<tnbLib::treeDataFace>&
tnbLib::meshSearch::boundaryTree() const
{
	if (!boundaryTreePtr_.valid())
	{
		//
		// Construct tree
		//

		if (!overallBbPtr_.valid())
		{
			overallBbPtr_.reset
			(
				new treeBoundBox(mesh_.points())
			);

			treeBoundBox& overallBb = overallBbPtr_();

			// Extend slightly and make 3D
			overallBb = overallBb.extend(1e-4);
		}

		// all boundary faces (not just walls)
		labelList bndFaces(mesh_.nFaces() - mesh_.nInternalFaces());
		forAll(bndFaces, i)
		{
			bndFaces[i] = mesh_.nInternalFaces() + i;
		}

		boundaryTreePtr_.reset
		(
			new indexedOctree<treeDataFace>
			(
				treeDataFace    // all information needed to search faces
				(
					false,                      // do not cache bb
					mesh_,
					bndFaces                    // boundary faces only
				),
				overallBbPtr_(),                // overall search domain
				8,                              // maxLevel
				10,                             // leafsize
				3.0                             // duplicity
				)
		);
	}

	return boundaryTreePtr_();
}


const tnbLib::indexedOctree<tnbLib::treeDataCell>&
tnbLib::meshSearch::cellTree() const
{
	if (!cellTreePtr_.valid())
	{
		//
		// Construct tree
		//

		if (!overallBbPtr_.valid())
		{
			overallBbPtr_.reset
			(
				new treeBoundBox(mesh_.points())
			);

			treeBoundBox& overallBb = overallBbPtr_();

			// Extend slightly and make 3D
			overallBb = overallBb.extend(1e-4);
		}

		cellTreePtr_.reset
		(
			new indexedOctree<treeDataCell>
			(
				treeDataCell
				(
					false,          // not cache bb
					mesh_,
					cellDecompMode_ // cell decomposition mode for inside tests
				),
				overallBbPtr_(),
				8,              // maxLevel
				10,             // leafsize
				6.0             // duplicity
				)
		);
	}

	return cellTreePtr_();
}


tnbLib::label tnbLib::meshSearch::findNearestCell
(
	const point& location,
	const label seedCelli,
	const bool useTreeSearch
) const
{
	if (seedCelli == -1)
	{
		if (useTreeSearch)
		{
			return findNearestCellTree(location);
		}
		else
		{
			return findNearestCellLinear(location);
		}
	}
	else
	{
		return findNearestCellWalk(location, seedCelli);
	}
}


tnbLib::label tnbLib::meshSearch::findNearestFace
(
	const point& location,
	const label seedFacei,
	const bool useTreeSearch
) const
{
	if (seedFacei == -1)
	{
		if (useTreeSearch)
		{
			return findNearestFaceTree(location);
		}
		else
		{
			return findNearestFaceLinear(location);
		}
	}
	else
	{
		return findNearestFaceWalk(location, seedFacei);
	}
}


tnbLib::label tnbLib::meshSearch::findCell
(
	const point& location,
	const label seedCelli,
	const bool useTreeSearch
) const
{
	// Find the nearest cell centre to this location
	if (seedCelli == -1)
	{
		if (useTreeSearch)
		{
			return cellTree().findInside(location);
		}
		else
		{
			return findCellLinear(location);
		}
	}
	else
	{
		return findCellWalk(location, seedCelli);
	}
}


tnbLib::label tnbLib::meshSearch::findNearestBoundaryFace
(
	const point& location,
	const label seedFacei,
	const bool useTreeSearch
) const
{
	if (seedFacei == -1)
	{
		if (useTreeSearch)
		{
			const indexedOctree<treeDataFace>& tree = boundaryTree();

			pointIndexHit info = boundaryTree().findNearest
			(
				location,
				magSqr(tree.bb().max() - tree.bb().min())
			);

			if (!info.hit())
			{
				info = boundaryTree().findNearest
				(
					location,
					tnbLib::sqr(great)
				);
			}

			return tree.shapes().faceLabels()[info.index()];
		}
		else
		{
			scalar minDist = great;

			label minFacei = -1;

			for
				(
					label facei = mesh_.nInternalFaces();
					facei < mesh_.nFaces();
					facei++
					)
			{
				const face& f = mesh_.faces()[facei];

				pointHit curHit =
					f.nearestPoint
					(
						location,
						mesh_.points()
					);

				if (curHit.distance() < minDist)
				{
					minDist = curHit.distance();
					minFacei = facei;
				}
			}
			return minFacei;
		}
	}
	else
	{
		return findNearestBoundaryFaceWalk(location, seedFacei);
	}
}


tnbLib::pointIndexHit tnbLib::meshSearch::intersection
(
	const point& pStart,
	const point& pEnd
) const
{
	pointIndexHit curHit = boundaryTree().findLine(pStart, pEnd);

	if (curHit.hit())
	{
		// Change index into octreeData into face label
		curHit.setIndex(boundaryTree().shapes().faceLabels()[curHit.index()]);
	}
	return curHit;
}


tnbLib::List<tnbLib::pointIndexHit> tnbLib::meshSearch::intersections
(
	const point& pStart,
	const point& pEnd
) const
{
	DynamicList<pointIndexHit> hits;
	pointIndexHit curHit;

	findUniqueIntersectOp iop(boundaryTree(), hits);

	while (true)
	{
		// Get the next hit, or quit
		curHit = boundaryTree().findLine(pStart, pEnd, iop);
		if (!curHit.hit()) break;

		// Change index into octreeData into face label
		curHit.setIndex(boundaryTree().shapes().faceLabels()[curHit.index()]);

		hits.append(curHit);
	}

	hits.shrink();

	return move(hits);
}


bool tnbLib::meshSearch::isInside(const point& p) const
{
	return (boundaryTree().getVolumeType(p) == volumeType::inside);
}


void tnbLib::meshSearch::clearOut()
{
	boundaryTreePtr_.clear();
	cellTreePtr_.clear();
	overallBbPtr_.clear();
}


void tnbLib::meshSearch::correct()
{
	clearOut();
}


// ************************************************************************* //