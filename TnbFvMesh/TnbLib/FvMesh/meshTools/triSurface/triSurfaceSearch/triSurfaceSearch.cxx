#include <triSurfaceSearch.hxx>

#include <triSurface.hxx>
#include <PatchTools.hxx>
#include <volumeType.hxx>

// added by amir
#include <dictionary.hxx>  
#include <Map.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

bool tnbLib::triSurfaceSearch::checkUniqueHit
(
	const pointIndexHit& currHit,
	const DynamicList<pointIndexHit, 1, 1>& hits,
	const vector& lineVec
) const
{
	// Classify the hit
	label nearType = -1;
	label nearLabel = -1;

	const labelledTri& f = surface()[currHit.index()];

	f.nearestPointClassify
	(
		currHit.hitPoint(),
		surface().points(),
		nearType,
		nearLabel
	);

	if (nearType == triPointRef::POINT)
	{
		// near point

		const label nearPointi = f[nearLabel];

		const labelList& pointFaces =
			surface().pointFaces()[surface().meshPointMap()[nearPointi]];

		forAll(pointFaces, pI)
		{
			const label pointFacei = pointFaces[pI];

			if (pointFacei != currHit.index())
			{
				forAll(hits, hi)
				{
					const pointIndexHit& hit = hits[hi];

					if (hit.index() == pointFacei)
					{
						return false;
					}
				}
			}
		}
	}
	else if (nearType == triPointRef::EDGE)
	{
		// near edge
		// check if the other face of the edge is already hit

		const labelList& fEdges = surface().faceEdges()[currHit.index()];

		const label edgeI = fEdges[nearLabel];

		const labelList& edgeFaces = surface().edgeFaces()[edgeI];

		forAll(edgeFaces, fi)
		{
			const label edgeFacei = edgeFaces[fi];

			if (edgeFacei != currHit.index())
			{
				forAll(hits, hi)
				{
					const pointIndexHit& hit = hits[hi];

					if (hit.index() == edgeFacei)
					{
						// Check normals
						const vector currHitNormal =
							surface().faceNormals()[currHit.index()];

						const vector existingHitNormal =
							surface().faceNormals()[edgeFacei];

						const label signCurrHit =
							pos0(currHitNormal & lineVec);

						const label signExistingHit =
							pos0(existingHitNormal & lineVec);

						if (signCurrHit == signExistingHit)
						{
							return false;
						}
					}
				}
			}
		}
	}

	return true;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::triSurfaceSearch::triSurfaceSearch(const triSurface& surface)
	:
	surface_(surface),
	tolerance_(indexedOctree<treeDataTriSurface>::perturbTol()),
	maxTreeDepth_(10),
	treePtr_(nullptr)
{}


tnbLib::triSurfaceSearch::triSurfaceSearch
(
	const triSurface& surface,
	const dictionary& dict
)
	:
	surface_(surface),
	tolerance_(indexedOctree<treeDataTriSurface>::perturbTol()),
	maxTreeDepth_(10),
	treePtr_(nullptr)
{
	// Have optional non-standard search tolerance for gappy surfaces.
	if (dict.readIfPresent("tolerance", tolerance_) && tolerance_ > 0)
	{
		Info << "    using intersection tolerance " << tolerance_ << endl;
	}

	// Have optional non-standard tree-depth to limit storage.
	if (dict.readIfPresent("maxTreeDepth", maxTreeDepth_) && maxTreeDepth_ > 0)
	{
		Info << "    using maximum tree depth " << maxTreeDepth_ << endl;
	}
}


tnbLib::triSurfaceSearch::triSurfaceSearch
(
	const triSurface& surface,
	const scalar tolerance,
	const label maxTreeDepth
)
	:
	surface_(surface),
	tolerance_(tolerance),
	maxTreeDepth_(maxTreeDepth),
	treePtr_(nullptr)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::triSurfaceSearch::~triSurfaceSearch()
{
	clearOut();
}


void tnbLib::triSurfaceSearch::clearOut()
{
	treePtr_.clear();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::indexedOctree<tnbLib::treeDataTriSurface>&
tnbLib::triSurfaceSearch::tree() const
{
	if (treePtr_.empty())
	{
		// Calculate bb without constructing local point numbering.
		treeBoundBox bb(Zero, Zero);

		if (surface().size())
		{
			label nPoints;
			PatchTools::calcBounds(surface(), bb, nPoints);

			if (nPoints != surface().points().size())
			{
				WarningInFunction
					<< "Surface does not have compact point numbering."
					<< " Of " << surface().points().size()
					<< " only " << nPoints
					<< " are used. This might give problems in some routines."
					<< endl;
			}

			// Slightly extended bb. Slightly off-centred just so on symmetric
			// geometry there are less face/edge aligned items.
			bb = bb.extend(1e-4);
		}

		scalar oldTol = indexedOctree<treeDataTriSurface>::perturbTol();
		indexedOctree<treeDataTriSurface>::perturbTol() = tolerance_;

		treePtr_.reset
		(
			new indexedOctree<treeDataTriSurface>
			(
				treeDataTriSurface(true, surface_, tolerance_),
				bb,
				maxTreeDepth_,  // maxLevel
				10,             // leafsize
				3.0             // duplicity
				)
		);

		indexedOctree<treeDataTriSurface>::perturbTol() = oldTol;
	}

	return treePtr_();
}


// Determine inside/outside for samples
tnbLib::boolList tnbLib::triSurfaceSearch::calcInside
(
	const pointField& samples
) const
{
	boolList inside(samples.size());

	forAll(samples, sampleI)
	{
		const point& sample = samples[sampleI];

		if (!tree().bb().contains(sample))
		{
			inside[sampleI] = false;
		}
		else if (tree().getVolumeType(sample) == volumeType::inside)
		{
			inside[sampleI] = true;
		}
		else
		{
			inside[sampleI] = false;
		}
	}
	return inside;
}


void tnbLib::triSurfaceSearch::findNearest
(
	const pointField& samples,
	const scalarField& nearestDistSqr,
	List<pointIndexHit>& info
) const
{
	scalar oldTol = indexedOctree<treeDataTriSurface>::perturbTol();
	indexedOctree<treeDataTriSurface>::perturbTol() = tolerance();

	const indexedOctree<treeDataTriSurface>& octree = tree();

	info.setSize(samples.size());

	forAll(samples, i)
	{
		info[i] = octree.findNearest
		(
			samples[i],
			nearestDistSqr[i],
			treeDataTriSurface::findNearestOp(octree)
		);
	}

	indexedOctree<treeDataTriSurface>::perturbTol() = oldTol;
}


tnbLib::pointIndexHit tnbLib::triSurfaceSearch::nearest
(
	const point& pt,
	const vector& span
)
const
{
	const scalar nearestDistSqr = 0.25*magSqr(span);

	return tree().findNearest(pt, nearestDistSqr);
}


void tnbLib::triSurfaceSearch::findLine
(
	const pointField& start,
	const pointField& end,
	List<pointIndexHit>& info
) const
{
	const indexedOctree<treeDataTriSurface>& octree = tree();

	info.setSize(start.size());

	scalar oldTol = indexedOctree<treeDataTriSurface>::perturbTol();
	indexedOctree<treeDataTriSurface>::perturbTol() = tolerance();

	forAll(start, i)
	{
		info[i] = octree.findLine
		(
			start[i],
			end[i]
		);
	}

	indexedOctree<treeDataTriSurface>::perturbTol() = oldTol;
}


void tnbLib::triSurfaceSearch::findLineAny
(
	const pointField& start,
	const pointField& end,
	List<pointIndexHit>& info
) const
{
	const indexedOctree<treeDataTriSurface>& octree = tree();

	info.setSize(start.size());

	scalar oldTol = indexedOctree<treeDataTriSurface>::perturbTol();
	indexedOctree<treeDataTriSurface>::perturbTol() = tolerance();

	forAll(start, i)
	{
		info[i] = octree.findLineAny
		(
			start[i],
			end[i]
		);
	}

	indexedOctree<treeDataTriSurface>::perturbTol() = oldTol;
}


void tnbLib::triSurfaceSearch::findLineAll
(
	const pointField& start,
	const pointField& end,
	List<List<pointIndexHit>>& info
) const
{
	const indexedOctree<treeDataTriSurface>& octree = tree();

	info.setSize(start.size());

	scalar oldTol = indexedOctree<treeDataTriSurface>::perturbTol();
	indexedOctree<treeDataTriSurface>::perturbTol() = tolerance();

	// Work array
	DynamicList<pointIndexHit, 1, 1> hits;

	DynamicList<label> shapeMask;

	treeDataTriSurface::findAllIntersectOp allIntersectOp(octree, shapeMask);

	forAll(start, i)
	{
		hits.clear();
		shapeMask.clear();

		while (true)
		{
			// See if any intersection between pt and end
			pointIndexHit inter = octree.findLine
			(
				start[i],
				end[i],
				allIntersectOp
			);

			if (inter.hit())
			{
				vector lineVec = end[i] - start[i];
				lineVec /= mag(lineVec) + vSmall;

				if (checkUniqueHit(inter, hits, lineVec))
				{
					hits.append(inter);
				}

				shapeMask.append(inter.index());
			}
			else
			{
				break;
			}
		}

		info[i].transfer(hits);
	}

	indexedOctree<treeDataTriSurface>::perturbTol() = oldTol;
}


// ************************************************************************* //