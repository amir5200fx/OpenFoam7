#pragma once
#include <Map.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class FaceList, class PointField>
tnbLib::PrimitivePatch<FaceList, PointField>::PrimitivePatch
(
	const FaceList& faces,
	const Field<PointType>& points
)
	:
	FaceList(faces),
	points_(points),
	edgesPtr_(nullptr),
	nInternalEdges_(-1),
	boundaryPointsPtr_(nullptr),
	faceFacesPtr_(nullptr),
	edgeFacesPtr_(nullptr),
	faceEdgesPtr_(nullptr),
	pointEdgesPtr_(nullptr),
	pointFacesPtr_(nullptr),
	localFacesPtr_(nullptr),
	meshPointsPtr_(nullptr),
	meshPointMapPtr_(nullptr),
	edgeLoopsPtr_(nullptr),
	localPointsPtr_(nullptr),
	localPointOrderPtr_(nullptr),
	faceCentresPtr_(nullptr),
	faceNormalsPtr_(nullptr),
	pointNormalsPtr_(nullptr)
{}


template<class FaceList, class PointField>
tnbLib::PrimitivePatch<FaceList, PointField>::PrimitivePatch
(
	FaceList&& faces,
	Field<PointType>&& points
)
	:
	FaceList(move(faces)),
	points_(move(points)),
	edgesPtr_(nullptr),
	nInternalEdges_(-1),
	boundaryPointsPtr_(nullptr),
	faceFacesPtr_(nullptr),
	edgeFacesPtr_(nullptr),
	faceEdgesPtr_(nullptr),
	pointEdgesPtr_(nullptr),
	pointFacesPtr_(nullptr),
	localFacesPtr_(nullptr),
	meshPointsPtr_(nullptr),
	meshPointMapPtr_(nullptr),
	edgeLoopsPtr_(nullptr),
	localPointsPtr_(nullptr),
	localPointOrderPtr_(nullptr),
	faceCentresPtr_(nullptr),
	faceNormalsPtr_(nullptr),
	pointNormalsPtr_(nullptr)
{}


template<class FaceList, class PointField>
tnbLib::PrimitivePatch<FaceList, PointField>::PrimitivePatch
(
	FaceList&& faces,
	List<PointType>&& points
)
	:
	FaceList(move(faces)),
	points_(move(points)),
	edgesPtr_(nullptr),
	nInternalEdges_(-1),
	boundaryPointsPtr_(nullptr),
	faceFacesPtr_(nullptr),
	edgeFacesPtr_(nullptr),
	faceEdgesPtr_(nullptr),
	pointEdgesPtr_(nullptr),
	pointFacesPtr_(nullptr),
	localFacesPtr_(nullptr),
	meshPointsPtr_(nullptr),
	meshPointMapPtr_(nullptr),
	edgeLoopsPtr_(nullptr),
	localPointsPtr_(nullptr),
	localPointOrderPtr_(nullptr),
	faceCentresPtr_(nullptr),
	faceNormalsPtr_(nullptr),
	pointNormalsPtr_(nullptr)
{}


template<class FaceList, class PointField>
tnbLib::PrimitivePatch<FaceList, PointField>::PrimitivePatch
(
	FaceList& faces,
	Field<PointType>& points,
	const bool reuse
)
	:
	FaceList(faces, reuse),
	points_(points, reuse),
	edgesPtr_(nullptr),
	nInternalEdges_(-1),
	boundaryPointsPtr_(nullptr),
	faceFacesPtr_(nullptr),
	edgeFacesPtr_(nullptr),
	faceEdgesPtr_(nullptr),
	pointEdgesPtr_(nullptr),
	pointFacesPtr_(nullptr),
	localFacesPtr_(nullptr),
	meshPointsPtr_(nullptr),
	meshPointMapPtr_(nullptr),
	edgeLoopsPtr_(nullptr),
	localPointsPtr_(nullptr),
	localPointOrderPtr_(nullptr),
	faceCentresPtr_(nullptr),
	faceNormalsPtr_(nullptr),
	pointNormalsPtr_(nullptr)
{}


template<class FaceList, class PointField>
tnbLib::PrimitivePatch<FaceList, PointField>::PrimitivePatch
(
	const PrimitivePatch<FaceList, PointField>& pp
)
	:
	PrimitivePatchName(),
	FaceList(pp),
	points_(pp.points_),
	edgesPtr_(nullptr),
	nInternalEdges_(-1),
	boundaryPointsPtr_(nullptr),
	faceFacesPtr_(nullptr),
	edgeFacesPtr_(nullptr),
	faceEdgesPtr_(nullptr),
	pointEdgesPtr_(nullptr),
	pointFacesPtr_(nullptr),
	localFacesPtr_(nullptr),
	meshPointsPtr_(nullptr),
	meshPointMapPtr_(nullptr),
	edgeLoopsPtr_(nullptr),
	localPointsPtr_(nullptr),
	localPointOrderPtr_(nullptr),
	faceCentresPtr_(nullptr),
	faceNormalsPtr_(nullptr),
	pointNormalsPtr_(nullptr)
{}


template<class FaceList, class PointField>
tnbLib::PrimitivePatch<FaceList, PointField>::PrimitivePatch
(
	PrimitivePatch<FaceList, PointField>&& pp
)
	:
	PrimitivePatchName(),
	FaceList(move(pp)),
	points_(move(pp.points_)),
	edgesPtr_(nullptr),
	nInternalEdges_(-1),
	boundaryPointsPtr_(nullptr),
	faceFacesPtr_(nullptr),
	edgeFacesPtr_(nullptr),
	faceEdgesPtr_(nullptr),
	pointEdgesPtr_(nullptr),
	pointFacesPtr_(nullptr),
	localFacesPtr_(nullptr),
	meshPointsPtr_(nullptr),
	meshPointMapPtr_(nullptr),
	edgeLoopsPtr_(nullptr),
	localPointsPtr_(nullptr),
	localPointOrderPtr_(nullptr),
	faceCentresPtr_(nullptr),
	faceNormalsPtr_(nullptr),
	pointNormalsPtr_(nullptr)
{}


template<class FaceList, class PointField>
tnbLib::PrimitivePatch<FaceList, PointField>::PrimitivePatch
(
	Istream& is,
	const Field<PointType>& points
)
	:
	FaceList(is),
	points_(points),
	edgesPtr_(nullptr),
	nInternalEdges_(-1),
	boundaryPointsPtr_(nullptr),
	faceFacesPtr_(nullptr),
	edgeFacesPtr_(nullptr),
	faceEdgesPtr_(nullptr),
	pointEdgesPtr_(nullptr),
	pointFacesPtr_(nullptr),
	localFacesPtr_(nullptr),
	meshPointsPtr_(nullptr),
	meshPointMapPtr_(nullptr),
	edgeLoopsPtr_(nullptr),
	localPointsPtr_(nullptr),
	localPointOrderPtr_(nullptr),
	faceCentresPtr_(nullptr),
	faceNormalsPtr_(nullptr),
	pointNormalsPtr_(nullptr)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class FaceList, class PointField>
tnbLib::PrimitivePatch<FaceList, PointField>::~PrimitivePatch()
{
	clearOut();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class FaceList, class PointField>
void tnbLib::PrimitivePatch<FaceList, PointField>::movePoints
(
	const Field<PointType>&
)
{
	if (debug)
	{
		Pout << "PrimitivePatch<FaceList, PointField>::"
			<< "movePoints() : "
			<< "recalculating PrimitivePatch geometry following mesh motion"
			<< endl;
	}

	clearGeom();
}


template<class FaceList, class PointField>
const tnbLib::edgeList& tnbLib::PrimitivePatch<FaceList, PointField>::edges() const
{
	if (!edgesPtr_)
	{
		calcAddressing();
	}

	return *edgesPtr_;
}


template<class FaceList, class PointField>
tnbLib::label tnbLib::PrimitivePatch<FaceList, PointField>::nInternalEdges() const
{
	if (!edgesPtr_)
	{
		calcAddressing();
	}

	return nInternalEdges_;
}


template<class FaceList, class PointField>
const tnbLib::labelList&
tnbLib::PrimitivePatch<FaceList, PointField>::boundaryPoints() const
{
	if (!boundaryPointsPtr_)
	{
		calcBdryPoints();
	}

	return *boundaryPointsPtr_;
}


template<class FaceList, class PointField>
const tnbLib::labelListList&
tnbLib::PrimitivePatch<FaceList, PointField>::
faceFaces() const
{
	if (!faceFacesPtr_)
	{
		calcAddressing();
	}

	return *faceFacesPtr_;
}


template<class FaceList, class PointField>
const tnbLib::labelListList&
tnbLib::PrimitivePatch<FaceList, PointField>::edgeFaces() const
{
	if (!edgeFacesPtr_)
	{
		calcAddressing();
	}

	return *edgeFacesPtr_;
}


template<class FaceList, class PointField>
const tnbLib::labelListList&
tnbLib::PrimitivePatch<FaceList, PointField>::faceEdges() const
{
	if (!faceEdgesPtr_)
	{
		calcAddressing();
	}

	return *faceEdgesPtr_;
}


template<class FaceList, class PointField>
const tnbLib::labelListList&
tnbLib::PrimitivePatch<FaceList, PointField>::pointEdges() const
{
	if (!pointEdgesPtr_)
	{
		calcPointEdges();
	}

	return *pointEdgesPtr_;
}


template<class FaceList, class PointField>
const tnbLib::labelListList&
tnbLib::PrimitivePatch<FaceList, PointField>::pointFaces() const
{
	if (!pointFacesPtr_)
	{
		calcPointFaces();
	}

	return *pointFacesPtr_;
}


template<class FaceList, class PointField>
const tnbLib::List
<
	typename tnbLib::PrimitivePatch<FaceList, PointField>::FaceType
>&
tnbLib::PrimitivePatch<FaceList, PointField>::localFaces() const
{
	if (!localFacesPtr_)
	{
		calcMeshData();
	}

	return *localFacesPtr_;
}


template<class FaceList, class PointField>
const tnbLib::labelList&
tnbLib::PrimitivePatch<FaceList, PointField>::meshPoints() const
{
	if (!meshPointsPtr_)
	{
		calcMeshData();
	}

	return *meshPointsPtr_;
}


template<class FaceList, class PointField>
const tnbLib::Map<tnbLib::label>&
tnbLib::PrimitivePatch<FaceList, PointField>::meshPointMap() const
{
	if (!meshPointMapPtr_)
	{
		calcMeshPointMap();
	}

	return *meshPointMapPtr_;
}


template<class FaceList, class PointField>
const tnbLib::Field
<
	typename tnbLib::PrimitivePatch<FaceList, PointField>::PointType
>&
tnbLib::PrimitivePatch<FaceList, PointField>::localPoints() const
{
	if (!localPointsPtr_)
	{
		calcLocalPoints();
	}

	return *localPointsPtr_;
}


template<class FaceList, class PointField>
const tnbLib::labelList&
tnbLib::PrimitivePatch<FaceList, PointField>::localPointOrder() const
{
	if (!localPointOrderPtr_)
	{
		calcLocalPointOrder();
	}

	return *localPointOrderPtr_;
}


template<class FaceList, class PointField>
tnbLib::label tnbLib::PrimitivePatch<FaceList, PointField>::whichPoint
(
	const label gp
) const
{
	Map<label>::const_iterator fnd = meshPointMap().find(gp);

	if (fnd != meshPointMap().end())
	{
		return fnd();
	}
	else
	{
		// Not found
		return -1;
	}
}


template<class FaceList, class PointField>
const tnbLib::Field
<
	typename tnbLib::PrimitivePatch<FaceList, PointField>::PointType
>&
tnbLib::PrimitivePatch<FaceList, PointField>::faceCentres() const
{
	if (!faceCentresPtr_)
	{
		calcFaceCentres();
	}

	return *faceCentresPtr_;
}


template<class FaceList, class PointField>
const tnbLib::Field
<
	typename tnbLib::PrimitivePatch<FaceList, PointField>::PointType
>&
tnbLib::PrimitivePatch<FaceList, PointField>::faceNormals() const
{
	if (!faceNormalsPtr_)
	{
		calcFaceNormals();
	}

	return *faceNormalsPtr_;
}


template<class FaceList, class PointField>
const tnbLib::Field
<
	typename tnbLib::PrimitivePatch<FaceList, PointField>::PointType
>&
tnbLib::PrimitivePatch<FaceList, PointField>::pointNormals() const
{
	if (!pointNormalsPtr_)
	{
		calcPointNormals();
	}

	return *pointNormalsPtr_;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class FaceList, class PointField>
void tnbLib::PrimitivePatch<FaceList, PointField>::operator=
(
	const PrimitivePatch<FaceList, PointField>& pp
	)
{
	clearOut();

	FaceList::shallowCopy(pp);
}


template<class FaceList, class PointField>
void tnbLib::PrimitivePatch<FaceList, PointField>::operator=
(
	PrimitivePatch<FaceList, PointField>&& pp
	)
{
	clearOut();

	FaceList::operator=(move(pp));

	// This is only valid if PointField is not a reference
	// points_ = move(pp.points_);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //