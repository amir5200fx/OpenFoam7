#pragma once
#include <indexedOctree.hxx>
#include <triangleFuncs.hxx>
#include <triSurfaceTools.hxx>
#include <triFace.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class PatchType>
tnbLib::treeBoundBox tnbLib::treeDataPrimitivePatch<PatchType>::calcBb
(
	const pointField& points,
	const face& f
)
{
	treeBoundBox bb(points[f[0]], points[f[0]]);

	for (label fp = 1; fp < f.size(); fp++)
	{
		const point& p = points[f[fp]];

		bb.min() = min(bb.min(), p);
		bb.max() = max(bb.max(), p);
	}
	return bb;
}


template<class PatchType>
void tnbLib::treeDataPrimitivePatch<PatchType>::update()
{
	if (cacheBb_)
	{
		bbs_.setSize(patch_.size());

		forAll(patch_, i)
		{
			bbs_[i] = calcBb(patch_.points(), patch_[i]);
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Construct from components
template<class PatchType>
tnbLib::treeDataPrimitivePatch<PatchType>::treeDataPrimitivePatch
(
	const bool cacheBb,
	const PatchType& patch,
	const scalar planarTol
)
	:
	patch_(patch),
	cacheBb_(cacheBb),
	planarTol_(planarTol)
{
	update();
}


template<class PatchType>
tnbLib::treeDataPrimitivePatch<PatchType>::findNearestOp::findNearestOp
(
	const indexedOctree<treeDataPrimitivePatch<PatchType>>& tree
)
	:
	tree_(tree)
{}


template<class PatchType>
tnbLib::treeDataPrimitivePatch<PatchType>::findIntersectOp::findIntersectOp
(
	const indexedOctree<treeDataPrimitivePatch<PatchType>>& tree
)
	:
	tree_(tree)
{}


template<class PatchType>
tnbLib::treeDataPrimitivePatch<PatchType>::findAllIntersectOp::findAllIntersectOp
(
	const indexedOctree<treeDataPrimitivePatch<PatchType>>& tree,
	DynamicList<label>& shapeMask
)
	:
	tree_(tree),
	shapeMask_(shapeMask)
{}


template<class PatchType>
tnbLib::treeDataPrimitivePatch<PatchType>::
findSelfIntersectOp::findSelfIntersectOp
(
	const indexedOctree<treeDataPrimitivePatch<PatchType>>& tree,
	const label edgeID
)
	:
	tree_(tree),
	edgeID_(edgeID)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class PatchType>
tnbLib::pointField tnbLib::treeDataPrimitivePatch<PatchType>::shapePoints() const
{
	pointField cc(patch_.size());

	forAll(patch_, i)
	{
		cc[i] = patch_[i].centre(patch_.points());
	}

	return cc;
}


template<class PatchType>
tnbLib::volumeType tnbLib::treeDataPrimitivePatch<PatchType>::getVolumeType
(
	const indexedOctree<treeDataPrimitivePatch<PatchType>>& oc,
	const point& sample
) const
{
	// Need to determine whether sample is 'inside' or 'outside'
	// Done by finding nearest face. This gives back a face which is
	// guaranteed to contain nearest point. This point can be
	// - in interior of face: compare to face normal
	// - on edge of face: compare to edge normal
	// - on point of face: compare to point normal
	// Unfortunately the octree does not give us back the intersection point
	// or where on the face it has hit so we have to recreate all that
	// information.


	// Find nearest face to sample
	pointIndexHit info = oc.findNearest(sample, sqr(great));

	if (info.index() == -1)
	{
		FatalErrorInFunction
			<< "Could not find " << sample << " in octree."
			<< abort(FatalError);
	}

	// Get actual intersection point on face
	label facei = info.index();

	if (debug & 2)
	{
		Pout << "getSampleType : sample:" << sample
			<< " nearest face:" << facei;
	}

	const pointField& points = patch_.localPoints();
	const typename PatchType::FaceType& f = patch_.localFaces()[facei];

	// Retest to classify where on face info is. Note: could be improved. We
	// already have point.

	pointHit curHit = f.nearestPoint(sample, points);
	const vector area = f.area(points);
	const point& curPt = curHit.rawPoint();

	//
	// 1] Check whether sample is above face
	//

	if (curHit.hit())
	{
		// Nearest point inside face. Compare to face normal.

		if (debug & 2)
		{
			Pout << " -> face hit:" << curPt
				<< " comparing to face normal " << area << endl;
		}
		return indexedOctree<treeDataPrimitivePatch>::getSide
		(
			area,
			sample - curPt
		);
	}

	if (debug & 2)
	{
		Pout << " -> face miss:" << curPt;
	}

	//
	// 2] Check whether intersection is on one of the face vertices or
	//    face centre
	//

	const scalar typDimSqr = mag(area) + vSmall;


	forAll(f, fp)
	{
		if ((magSqr(points[f[fp]] - curPt) / typDimSqr) < planarTol_)
		{
			// Face intersection point equals face vertex fp

			// Calculate point normal (wrong: uses face normals instead of
			// triangle normals)

			return indexedOctree<treeDataPrimitivePatch>::getSide
			(
				patch_.pointNormals()[f[fp]],
				sample - curPt
			);
		}
	}

	const point fc(f.centre(points));

	if ((magSqr(fc - curPt) / typDimSqr) < planarTol_)
	{
		// Face intersection point equals face centre. Normal at face centre
		// is already average of face normals

		if (debug & 2)
		{
			Pout << " -> centre hit:" << fc
				<< " distance:" << magSqr(fc - curPt) / typDimSqr << endl;
		}

		return indexedOctree<treeDataPrimitivePatch>::getSide
		(
			area,
			sample - curPt
		);
	}



	//
	// 3] Get the 'real' edge the face intersection is on
	//

	const labelList& fEdges = patch_.faceEdges()[facei];

	forAll(fEdges, fEdgeI)
	{
		label edgeI = fEdges[fEdgeI];
		const edge& e = patch_.edges()[edgeI];

		pointHit edgeHit = e.line(points).nearestDist(sample);

		if ((magSqr(edgeHit.rawPoint() - curPt) / typDimSqr) < planarTol_)
		{
			// Face intersection point lies on edge e

			// Calculate edge normal (wrong: uses face normals instead of
			// triangle normals)
			const labelList& eFaces = patch_.edgeFaces()[edgeI];

			vector edgeNormal(Zero);

			forAll(eFaces, i)
			{
				edgeNormal += patch_.faceNormals()[eFaces[i]];
			}

			if (debug & 2)
			{
				Pout << " -> real edge hit point:" << edgeHit.rawPoint()
					<< " comparing to edge normal:" << edgeNormal
					<< endl;
			}

			// Found face intersection point on this edge. Compare to edge
			// normal
			return indexedOctree<treeDataPrimitivePatch>::getSide
			(
				edgeNormal,
				sample - curPt
			);
		}
	}


	//
	// 4] Get the internal edge the face intersection is on
	//

	forAll(f, fp)
	{
		pointHit edgeHit = linePointRef
		(
			points[f[fp]],
			fc
		).nearestDist(sample);

		if ((magSqr(edgeHit.rawPoint() - curPt) / typDimSqr) < planarTol_)
		{
			// Face intersection point lies on edge between two face triangles

			// Calculate edge normal as average of the two triangle normals
			vector e = points[f[fp]] - fc;
			vector ePrev = points[f[f.rcIndex(fp)]] - fc;
			vector eNext = points[f[f.fcIndex(fp)]] - fc;

			vector nLeft = ePrev ^ e;
			nLeft /= mag(nLeft) + vSmall;

			vector nRight = e ^ eNext;
			nRight /= mag(nRight) + vSmall;

			if (debug & 2)
			{
				Pout << " -> internal edge hit point:" << edgeHit.rawPoint()
					<< " comparing to edge normal "
					<< 0.5*(nLeft + nRight)
					<< endl;
			}

			// Found face intersection point on this edge. Compare to edge
			// normal
			return indexedOctree<treeDataPrimitivePatch>::getSide
			(
				0.5*(nLeft + nRight),
				sample - curPt
			);
		}
	}

	if (debug & 2)
	{
		Pout << "Did not find sample " << sample
			<< " anywhere related to nearest face " << facei << endl
			<< "Face:";

		forAll(f, fp)
		{
			Pout << "    vertex:" << f[fp] << "  coord:" << points[f[fp]]
				<< endl;
		}
	}

	// Can't determine status of sample with respect to nearest face.
	// Either
	// - tolerances are wrong. (if e.g. face has zero area)
	// - or (more likely) surface is not closed.

	return volumeType::unknown;
}


// Check if any point on shape is inside cubeBb.
template<class PatchType>
bool tnbLib::treeDataPrimitivePatch<PatchType>::overlaps
(
	const label index,
	const treeBoundBox& cubeBb
) const
{
	// 1. Quick rejection: bb does not intersect face bb at all
	if (cacheBb_)
	{
		if (!cubeBb.overlaps(bbs_[index]))
		{
			return false;
		}
	}
	else
	{
		if (!cubeBb.overlaps(calcBb(patch_.points(), patch_[index])))
		{
			return false;
		}
	}


	// 2. Check if one or more face points inside

	const pointField& points = patch_.points();
	const typename PatchType::FaceType& f = patch_[index];

	if (cubeBb.containsAny(points, f))
	{
		return true;
	}

	// 3. Difficult case: all points are outside but connecting edges might
	// go through cube. Use triangle-bounding box intersection.
	const point fc = f.centre(points);

	if (f.size() == 3)
	{
		return triangleFuncs::intersectBb
		(
			points[f[0]],
			points[f[1]],
			points[f[2]],
			cubeBb
		);
	}
	else
	{
		forAll(f, fp)
		{
			bool triIntersects = triangleFuncs::intersectBb
			(
				points[f[fp]],
				points[f[f.fcIndex(fp)]],
				fc,
				cubeBb
			);

			if (triIntersects)
			{
				return true;
			}
		}
	}

	return false;
}


// Check if any point on shape is inside sphere.
template<class PatchType>
bool tnbLib::treeDataPrimitivePatch<PatchType>::overlaps
(
	const label index,
	const point& centre,
	const scalar radiusSqr
) const
{
	// 1. Quick rejection: sphere does not intersect face bb at all
	if (cacheBb_)
	{
		if (!bbs_[index].overlaps(centre, radiusSqr))
		{
			return false;
		}
	}
	else
	{
		if (!calcBb(patch_.points(), patch_[index]).overlaps(centre, radiusSqr))
		{
			return false;
		}
	}

	const pointField& points = patch_.points();
	const face& f = patch_[index];

	pointHit nearHit = f.nearestPoint(centre, points);

	// If the distance to the nearest point on the face from the sphere centres
	// is within the radius, then the sphere touches the face.
	if (sqr(nearHit.distance()) < radiusSqr)
	{
		return true;
	}

	return false;
}


template<class PatchType>
void tnbLib::treeDataPrimitivePatch<PatchType>::findNearestOp::operator()
(
	const labelUList& indices,
	const point& sample,

	scalar& nearestDistSqr,
	label& minIndex,
	point& nearestPoint
	) const
{
	const treeDataPrimitivePatch<PatchType>& shape = tree_.shapes();
	const PatchType& patch = shape.patch();

	const pointField& points = patch.points();

	forAll(indices, i)
	{
		const label index = indices[i];
		const typename PatchType::FaceType& f = patch[index];

		pointHit nearHit = f.nearestPoint(sample, points);
		scalar distSqr = sqr(nearHit.distance());

		if (distSqr < nearestDistSqr)
		{
			nearestDistSqr = distSqr;
			minIndex = index;
			nearestPoint = nearHit.rawPoint();
		}
	}
}


template<class PatchType>
void tnbLib::treeDataPrimitivePatch<PatchType>::findNearestOp::operator()
(
	const labelUList& indices,
	const linePointRef& ln,

	treeBoundBox& tightest,
	label& minIndex,
	point& linePoint,
	point& nearestPoint
	) const
{
	NotImplemented;
}


template<class PatchType>
bool tnbLib::treeDataPrimitivePatch<PatchType>::findIntersectOp::operator()
(
	const label index,
	const point& start,
	const point& end,
	point& intersectionPoint
	) const
{
	return findIntersection(tree_, index, start, end, intersectionPoint);
}


template<class PatchType>
bool tnbLib::treeDataPrimitivePatch<PatchType>::findAllIntersectOp::operator()
(
	const label index,
	const point& start,
	const point& end,
	point& intersectionPoint
	) const
{
	if (!shapeMask_.empty() && findIndex(shapeMask_, index) != -1)
	{
		return false;
	}

	return findIntersection(tree_, index, start, end, intersectionPoint);
}


template<class PatchType>
bool tnbLib::treeDataPrimitivePatch<PatchType>::findSelfIntersectOp::operator()
(
	const label index,
	const point& start,
	const point& end,
	point& intersectionPoint
	) const
{
	if (edgeID_ == -1)
	{
		FatalErrorInFunction
			<< "EdgeID not set. Please set edgeID to the index of"
			<< " the edge you are testing"
			<< exit(FatalError);
	}

	const treeDataPrimitivePatch<PatchType>& shape = tree_.shapes();
	const PatchType& patch = shape.patch();

	const typename PatchType::FaceType& f = patch.localFaces()[index];
	const edge& e = patch.edges()[edgeID_];

	if (findIndex(f, e[0]) == -1 && findIndex(f, e[1]) == -1)
	{
		return findIntersection(tree_, index, start, end, intersectionPoint);
	}
	else
	{
		return false;
	}
}


template<class PatchType>
bool tnbLib::treeDataPrimitivePatch<PatchType>::findIntersection
(
	const indexedOctree<treeDataPrimitivePatch<PatchType>>& tree,
	const label index,
	const point& start,
	const point& end,
	point& intersectionPoint
)
{
	const treeDataPrimitivePatch<PatchType>& shape = tree.shapes();
	const PatchType& patch = shape.patch();

	const pointField& points = patch.points();
	const typename PatchType::FaceType& f = patch[index];

	// Do quick rejection test
	if (shape.cacheBb_)
	{
		const treeBoundBox& faceBb = shape.bbs_[index];

		if ((faceBb.posBits(start) & faceBb.posBits(end)) != 0)
		{
			// start and end in same block outside of faceBb.
			return false;
		}
	}

	const vector dir(end - start);
	pointHit inter;

	if (f.size() == 3)
	{
		inter = triPointRef
		(
			points[f[0]],
			points[f[1]],
			points[f[2]]
		)
			.intersection
			(
				start,
				dir,
				intersection::algorithm::halfRay,
				shape.planarTol_
			);
	}
	else
	{
		const pointField& faceCentres = patch.faceCentres();

		inter = f.intersection
		(
			start,
			dir,
			faceCentres[index],
			points,
			intersection::algorithm::halfRay,
			shape.planarTol_
		);
	}

	if (inter.hit() && inter.distance() <= 1)
	{
		// Note: no extra test on whether intersection is in front of us
		// since using half_ray
		intersectionPoint = inter.hitPoint();

		return true;
	}
	else
	{
		return false;
	}
}


// ************************************************************************* //