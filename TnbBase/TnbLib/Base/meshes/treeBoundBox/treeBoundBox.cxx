#include <treeBoundBox.hxx>

#include <ListOps.hxx>
#include <OFstream.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

const tnbLib::scalar tnbLib::treeBoundBox::great(great);

const tnbLib::treeBoundBox tnbLib::treeBoundBox::greatBox
(
	vector(-great, -great, -great),
	vector(great, great, great)
);


const tnbLib::treeBoundBox tnbLib::treeBoundBox::invertedBox
(
	vector(great, great, great),
	vector(-great, -great, -great)
);


//! \cond ignoreDocumentation
//- Skip documentation : local scope only
const tnbLib::label facesArray[6][4] =
{
	{0, 4, 6, 2}, // left
	{1, 3, 7, 5}, // right
	{0, 1, 5, 4}, // bottom
	{2, 6, 7, 3}, // top
	{0, 2, 3, 1}, // back
	{4, 5, 7, 6}  // front
};
//! \endcond


const tnbLib::faceList tnbLib::treeBoundBox::faces
(
	initListList<face, label, 6, 4>(facesArray)
);


//! \cond  ignoreDocumentation
//- Skip documentation : local scope only
const tnbLib::label edgesArray[12][2] =
{
	{0, 1}, // 0
	{1, 3},
	{2, 3}, // 2
	{0, 2},
	{4, 5}, // 4
	{5, 7},
	{6, 7}, // 6
	{4, 6},
	{0, 4}, // 8
	{1, 5},
	{3, 7}, // 10
	{2, 6}
};
//! \endcond


const tnbLib::edgeList tnbLib::treeBoundBox::edges
(
	// initListList<edge, label, 12, 2>(edgesArray)
	calcEdges(edgesArray)
);


const tnbLib::FixedList<tnbLib::vector, 6> tnbLib::treeBoundBox::faceNormals
(
	calcFaceNormals()
);


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

tnbLib::edgeList tnbLib::treeBoundBox::calcEdges(const label edgesArray[12][2])
{
	edgeList edges(12);
	forAll(edges, edgeI)
	{
		edges[edgeI][0] = edgesArray[edgeI][0];
		edges[edgeI][1] = edgesArray[edgeI][1];
	}
	return edges;
}


tnbLib::FixedList<tnbLib::vector, 6> tnbLib::treeBoundBox::calcFaceNormals()
{
	FixedList<vector, 6> normals;
	normals[faceId::left] = vector(-1, 0, 0);
	normals[faceId::right] = vector(1, 0, 0);
	normals[faceId::bottom] = vector(0, -1, 0);
	normals[faceId::top] = vector(0, 1, 0);
	normals[faceId::back] = vector(0, 0, -1);
	normals[faceId::front] = vector(0, 0, 1);
	return normals;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::treeBoundBox::treeBoundBox(const UList<point>& points)
	:
	boundBox(points, false)
{
	if (points.empty())
	{
		WarningInFunction
			<< "cannot find bounding box for zero-sized pointField, "
			<< "returning zero" << endl;

		return;
	}
}


tnbLib::treeBoundBox::treeBoundBox
(
	const UList<point>& points,
	const labelUList& indices
)
	:
	boundBox(points, indices, false)
{
	if (points.empty() || indices.empty())
	{
		WarningInFunction
			<< "cannot find bounding box for zero-sized pointField, "
			<< "returning zero" << endl;

		return;
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::pointField> tnbLib::treeBoundBox::points() const
{
	tmp<pointField> tPts = tmp<pointField>(new pointField(8));
	pointField& points = tPts.ref();

	forAll(points, octant)
	{
		points[octant] = corner(octant);
	}

	return tPts;
}


tnbLib::treeBoundBox tnbLib::treeBoundBox::subBbox(const direction octant) const
{
	return subBbox(midpoint(), octant);
}


tnbLib::treeBoundBox tnbLib::treeBoundBox::subBbox
(
	const point& mid,
	const direction octant
) const
{
	if (octant > 7)
	{
		FatalErrorInFunction
			<< "octant should be [0..7]"
			<< abort(FatalError);
	}

	// start with a copy of this bounding box and adjust limits accordingly
	treeBoundBox subBb(*this);
	point& bbMin = subBb.min();
	point& bbMax = subBb.max();

	if (octant & octantBit::rightHalf)
	{
		bbMin.x() = mid.x();    // mid -> max
	}
	else
	{
		bbMax.x() = mid.x();    // min -> mid
	}

	if (octant & octantBit::topHalf)
	{
		bbMin.y() = mid.y();    // mid -> max
	}
	else
	{
		bbMax.y() = mid.y();    // min -> mid
	}

	if (octant & octantBit::frontHalf)
	{
		bbMin.z() = mid.z();    // mid -> max
	}
	else
	{
		bbMax.z() = mid.z();    // min -> mid
	}

	return subBb;
}


bool tnbLib::treeBoundBox::intersects
(
	const point& overallStart,
	const vector& overallVec,
	const point& start,
	const point& end,
	point& pt,
	direction& ptOnFaces
) const
{
	// Sutherlands algorithm:
	//   loop
	//     - start = intersection of line with one of the planes bounding
	//       the bounding box
	//     - stop if start inside bb (return true)
	//     - stop if start and end in same 'half' (e.g. both above bb)
	//       (return false)
	//
	// Uses posBits to efficiently determine 'half' in which start and end
	// point are.
	//
	// Note:
	//   - sets coordinate to exact position: e.g. pt.x() = min().x()
	//     since plane intersect routine might have truncation error.
	//     This makes sure that posBits tests 'inside'

	const direction endBits = posBits(end);
	pt = start;

	// Allow maximum of 3 clips.
	for (label i = 0; i < 4; ++i)
	{
		direction ptBits = posBits(pt);

		if (ptBits == 0)
		{
			// pt inside bb
			ptOnFaces = faceBits(pt);
			return true;
		}

		if ((ptBits & endBits) != 0)
		{
			// pt and end in same block outside of bb
			ptOnFaces = faceBits(pt);
			return false;
		}

		if (ptBits & faceBit::left)
		{
			// Intersect with plane V=min, n=-1,0,0
			if (tnbLib::mag(overallVec.x()) > vSmall)
			{
				scalar s = (min().x() - overallStart.x()) / overallVec.x();
				pt.x() = min().x();
				pt.y() = overallStart.y() + overallVec.y()*s;
				pt.z() = overallStart.z() + overallVec.z()*s;
			}
			else
			{
				// Vector not in x-direction. But still intersecting bb planes.
				// So must be close - just snap to bb.
				pt.x() = min().x();
			}
		}
		else if (ptBits & faceBit::right)
		{
			// Intersect with plane V=max, n=1,0,0
			if (tnbLib::mag(overallVec.x()) > vSmall)
			{
				scalar s = (max().x() - overallStart.x()) / overallVec.x();
				pt.x() = max().x();
				pt.y() = overallStart.y() + overallVec.y()*s;
				pt.z() = overallStart.z() + overallVec.z()*s;
			}
			else
			{
				pt.x() = max().x();
			}
		}
		else if (ptBits & faceBit::bottom)
		{
			// Intersect with plane V=min, n=0,-1,0
			if (tnbLib::mag(overallVec.y()) > vSmall)
			{
				scalar s = (min().y() - overallStart.y()) / overallVec.y();
				pt.x() = overallStart.x() + overallVec.x()*s;
				pt.y() = min().y();
				pt.z() = overallStart.z() + overallVec.z()*s;
			}
			else
			{
				pt.x() = min().y();
			}
		}
		else if (ptBits & faceBit::top)
		{
			// Intersect with plane V=max, n=0,1,0
			if (tnbLib::mag(overallVec.y()) > vSmall)
			{
				scalar s = (max().y() - overallStart.y()) / overallVec.y();
				pt.x() = overallStart.x() + overallVec.x()*s;
				pt.y() = max().y();
				pt.z() = overallStart.z() + overallVec.z()*s;
			}
			else
			{
				pt.y() = max().y();
			}
		}
		else if (ptBits & faceBit::back)
		{
			// Intersect with plane V=min, n=0,0,-1
			if (tnbLib::mag(overallVec.z()) > vSmall)
			{
				scalar s = (min().z() - overallStart.z()) / overallVec.z();
				pt.x() = overallStart.x() + overallVec.x()*s;
				pt.y() = overallStart.y() + overallVec.y()*s;
				pt.z() = min().z();
			}
			else
			{
				pt.z() = min().z();
			}
		}
		else if (ptBits & faceBit::front)
		{
			// Intersect with plane V=max, n=0,0,1
			if (tnbLib::mag(overallVec.z()) > vSmall)
			{
				scalar s = (max().z() - overallStart.z()) / overallVec.z();
				pt.x() = overallStart.x() + overallVec.x()*s;
				pt.y() = overallStart.y() + overallVec.y()*s;
				pt.z() = max().z();
			}
			else
			{
				pt.z() = max().z();
			}
		}
	}

	// Can end up here if the end point is on the edge of the boundBox
	return true;
}


bool tnbLib::treeBoundBox::intersects
(
	const point& start,
	const point& end,
	point& pt
) const
{
	direction ptBits;
	return intersects(start, end - start, start, end, pt, ptBits);
}


bool tnbLib::treeBoundBox::contains(const vector& dir, const point& pt) const
{
	// Compare all components against min and max of bb

	for (direction cmpt = 0; cmpt < 3; cmpt++)
	{
		if (pt[cmpt] < min()[cmpt])
		{
			return false;
		}
		else if (pt[cmpt] == min()[cmpt])
		{
			// On edge. Outside if direction points outwards.
			if (dir[cmpt] < 0)
			{
				return false;
			}
		}

		if (pt[cmpt] > max()[cmpt])
		{
			return false;
		}
		else if (pt[cmpt] == max()[cmpt])
		{
			// On edge. Outside if direction points outwards.
			if (dir[cmpt] > 0)
			{
				return false;
			}
		}
	}

	// All components inside bb
	return true;
}


tnbLib::direction tnbLib::treeBoundBox::faceBits(const point& pt) const
{
	direction faceBits = 0;
	if (pt.x() == min().x())
	{
		faceBits |= faceBit::left;
	}
	else if (pt.x() == max().x())
	{
		faceBits |= faceBit::right;
	}

	if (pt.y() == min().y())
	{
		faceBits |= faceBit::bottom;
	}
	else if (pt.y() == max().y())
	{
		faceBits |= faceBit::top;
	}

	if (pt.z() == min().z())
	{
		faceBits |= faceBit::back;
	}
	else if (pt.z() == max().z())
	{
		faceBits |= faceBit::front;
	}
	return faceBits;
}


tnbLib::direction tnbLib::treeBoundBox::posBits(const point& pt) const
{
	direction posBits = 0;

	if (pt.x() < min().x())
	{
		posBits |= faceBit::left;
	}
	else if (pt.x() > max().x())
	{
		posBits |= faceBit::right;
	}

	if (pt.y() < min().y())
	{
		posBits |= faceBit::bottom;
	}
	else if (pt.y() > max().y())
	{
		posBits |= faceBit::top;
	}

	if (pt.z() < min().z())
	{
		posBits |= faceBit::back;
	}
	else if (pt.z() > max().z())
	{
		posBits |= faceBit::front;
	}
	return posBits;
}


void tnbLib::treeBoundBox::calcExtremities
(
	const point& pt,
	point& nearest,
	point& furthest
) const
{
	scalar nearX, nearY, nearZ;
	scalar farX, farY, farZ;

	if (tnbLib::mag(min().x() - pt.x()) < tnbLib::mag(max().x() - pt.x()))
	{
		nearX = min().x();
		farX = max().x();
	}
	else
	{
		nearX = max().x();
		farX = min().x();
	}

	if (tnbLib::mag(min().y() - pt.y()) < tnbLib::mag(max().y() - pt.y()))
	{
		nearY = min().y();
		farY = max().y();
	}
	else
	{
		nearY = max().y();
		farY = min().y();
	}

	if (tnbLib::mag(min().z() - pt.z()) < tnbLib::mag(max().z() - pt.z()))
	{
		nearZ = min().z();
		farZ = max().z();
	}
	else
	{
		nearZ = max().z();
		farZ = min().z();
	}

	nearest = point(nearX, nearY, nearZ);
	furthest = point(farX, farY, farZ);
}


tnbLib::scalar tnbLib::treeBoundBox::maxDist(const point& pt) const
{
	point near, far;
	calcExtremities(pt, near, far);

	return tnbLib::mag(far - pt);
}


tnbLib::label tnbLib::treeBoundBox::distanceCmp
(
	const point& pt,
	const treeBoundBox& other
) const
{
	//
	// Distance point <-> nearest and furthest away vertex of this
	//

	point nearThis, farThis;

	// get nearest and furthest away vertex
	calcExtremities(pt, nearThis, farThis);

	const scalar minDistThis =
		sqr(nearThis.x() - pt.x())
		+ sqr(nearThis.y() - pt.y())
		+ sqr(nearThis.z() - pt.z());
	const scalar maxDistThis =
		sqr(farThis.x() - pt.x())
		+ sqr(farThis.y() - pt.y())
		+ sqr(farThis.z() - pt.z());

	//
	// Distance point <-> other
	//

	point nearOther, farOther;

	// get nearest and furthest away vertex
	other.calcExtremities(pt, nearOther, farOther);

	const scalar minDistOther =
		sqr(nearOther.x() - pt.x())
		+ sqr(nearOther.y() - pt.y())
		+ sqr(nearOther.z() - pt.z());
	const scalar maxDistOther =
		sqr(farOther.x() - pt.x())
		+ sqr(farOther.y() - pt.y())
		+ sqr(farOther.z() - pt.z());

	//
	// Categorize
	//
	if (maxDistThis < minDistOther)
	{
		// All vertices of this are nearer to point than any vertex of other
		return -1;
	}
	else if (minDistThis > maxDistOther)
	{
		// All vertices of this are further from point than any vertex of other
		return 1;
	}
	else
	{
		// Mixed bag
		return 0;
	}
}


void tnbLib::treeBoundBox::writeOBJ(const fileName& fName) const
{
	OFstream str(fName);

	Info << "Dumping bounding box " << *this << " as lines to obj file "
		<< str.name() << endl;

	pointField bbPoints(points());

	forAll(bbPoints, i)
	{
		const point& pt = bbPoints[i];

		str << "v " << pt.x() << ' ' << pt.y() << ' ' << pt.z() << endl;
	}

	forAll(treeBoundBox::edges, i)
	{
		const edge& e = treeBoundBox::edges[i];

		str << "l " << e[0] + 1 << ' ' << e[1] + 1 << nl;
	}
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

bool tnbLib::operator==(const treeBoundBox& a, const treeBoundBox& b)
{
	return operator==
		(
			static_cast<const boundBox&>(a),
			static_cast<const boundBox&>(b)
			);
}


bool tnbLib::operator!=(const treeBoundBox& a, const treeBoundBox& b)
{
	return !(a == b);
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const treeBoundBox& bb)
{
	return os << static_cast<const boundBox&>(bb);
}


tnbLib::Istream& tnbLib::operator>>(Istream& is, treeBoundBox& bb)
{
	return is >> static_cast<boundBox&>(bb);
}


// ************************************************************************* //