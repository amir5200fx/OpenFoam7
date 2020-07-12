#include <treeDataCell.hxx>

#include <indexedOctree.hxx>
#include <polyMesh.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(treeDataCell, 0);
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

tnbLib::treeBoundBox tnbLib::treeDataCell::calcCellBb(const label celli) const
{
	const cellList& cells = mesh_.cells();
	const faceList& faces = mesh_.faces();
	const pointField& points = mesh_.points();

	treeBoundBox cellBb
	(
		vector(great, great, great),
		vector(-great, -great, -great)
	);

	const cell& cFaces = cells[celli];

	forAll(cFaces, cFacei)
	{
		const face& f = faces[cFaces[cFacei]];
		
		forAll(f, fp)
		{
			const point& p = points[f[fp]];

			cellBb.min() = min(cellBb.min(), p);
			cellBb.max() = max(cellBb.max(), p);
		}
	}
	return cellBb;
}


void tnbLib::treeDataCell::update()
{
	if (cacheBb_)
	{
		bbs_.setSize(cellLabels_.size());

		forAll(cellLabels_, i)
		{
			bbs_[i] = calcCellBb(cellLabels_[i]);
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::treeDataCell::treeDataCell
(
	const bool cacheBb,
	const polyMesh& mesh,
	const labelUList& cellLabels,
	const polyMesh::cellDecomposition decompMode
)
	:
	mesh_(mesh),
	cellLabels_(cellLabels),
	cacheBb_(cacheBb),
	decompMode_(decompMode)
{
	update();
}


tnbLib::treeDataCell::treeDataCell
(
	const bool cacheBb,
	const polyMesh& mesh,
	labelList&& cellLabels,
	const polyMesh::cellDecomposition decompMode
)
	:
	mesh_(mesh),
	cellLabels_(move(cellLabels)),
	cacheBb_(cacheBb),
	decompMode_(decompMode)
{
	update();
}


tnbLib::treeDataCell::treeDataCell
(
	const bool cacheBb,
	const polyMesh& mesh,
	const polyMesh::cellDecomposition decompMode
)
	:
	mesh_(mesh),
	cellLabels_(identity(mesh_.nCells())),
	cacheBb_(cacheBb),
	decompMode_(decompMode)
{
	update();
}


tnbLib::treeDataCell::findNearestOp::findNearestOp
(
	const indexedOctree<treeDataCell>& tree
)
	:
	tree_(tree)
{}


tnbLib::treeDataCell::findIntersectOp::findIntersectOp
(
	const indexedOctree<treeDataCell>& tree
)
	:
	tree_(tree)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::pointField tnbLib::treeDataCell::shapePoints() const
{
	pointField cc(cellLabels_.size());

	forAll(cellLabels_, i)
	{
		cc[i] = mesh_.cellCentres()[cellLabels_[i]];
	}

	return cc;
}


bool tnbLib::treeDataCell::overlaps
(
	const label index,
	const treeBoundBox& cubeBb
) const
{
	if (cacheBb_)
	{
		return cubeBb.overlaps(bbs_[index]);
	}
	else
	{
		return cubeBb.overlaps(calcCellBb(cellLabels_[index]));
	}
}


bool tnbLib::treeDataCell::contains
(
	const label index,
	const point& sample
) const
{
	return mesh_.pointInCell(sample, cellLabels_[index], decompMode_);
}


void tnbLib::treeDataCell::findNearestOp::operator()
(
	const labelUList& indices,
	const point& sample,

	scalar& nearestDistSqr,
	label& minIndex,
	point& nearestPoint
	) const
{
	const treeDataCell& shape = tree_.shapes();

	forAll(indices, i)
	{
		label index = indices[i];
		label celli = shape.cellLabels()[index];
		scalar distSqr = magSqr(sample - shape.mesh().cellCentres()[celli]);

		if (distSqr < nearestDistSqr)
		{
			nearestDistSqr = distSqr;
			minIndex = index;
			nearestPoint = shape.mesh().cellCentres()[celli];
		}
	}
}


void tnbLib::treeDataCell::findNearestOp::operator()
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


bool tnbLib::treeDataCell::findIntersectOp::operator()
(
	const label index,
	const point& start,
	const point& end,
	point& intersectionPoint
	) const
{
	const treeDataCell& shape = tree_.shapes();

	// Do quick rejection test
	if (shape.cacheBb_)
	{
		const treeBoundBox& cellBb = shape.bbs_[index];

		if ((cellBb.posBits(start) & cellBb.posBits(end)) != 0)
		{
			// Start and end in same block outside of cellBb.
			return false;
		}
	}
	else
	{
		const treeBoundBox cellBb = shape.calcCellBb(shape.cellLabels_[index]);

		if ((cellBb.posBits(start) & cellBb.posBits(end)) != 0)
		{
			// Start and end in same block outside of cellBb.
			return false;
		}
	}


	// Do intersection with all faces of cell
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	// Disable picking up intersections behind us.
	scalar oldTol = intersection::setPlanarTol(0.0);

	const cell& cFaces = shape.mesh_.cells()[shape.cellLabels_[index]];

	const vector dir(end - start);
	scalar minDistSqr = magSqr(dir);
	bool hasMin = false;

	forAll(cFaces, i)
	{
		const face& f = shape.mesh_.faces()[cFaces[i]];

		pointHit inter = f.ray
		(
			start,
			dir,
			shape.mesh_.points(),
			intersection::algorithm::halfRay
		);

		if (inter.hit() && sqr(inter.distance()) <= minDistSqr)
		{
			// Note: no extra test on whether intersection is in front of us
			// since using half_ray AND zero tolerance. (note that tolerance
			// is used to look behind us)
			minDistSqr = sqr(inter.distance());
			intersectionPoint = inter.hitPoint();
			hasMin = true;
		}
	}

	// Restore picking tolerance
	intersection::setPlanarTol(oldTol);

	return hasMin;
}


// ************************************************************************* //