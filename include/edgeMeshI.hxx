#pragma once
// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

inline tnbLib::pointField& tnbLib::edgeMesh::storedPoints()
{
	return points_;
}


inline tnbLib::edgeList& tnbLib::edgeMesh::storedEdges()
{
	return edges_;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline tnbLib::edgeMesh::edgeMesh(const edgeMesh& em)
	:
	fileFormats::edgeMeshFormatsCore(),
	points_(em.points_),
	edges_(em.edges_),
	pointEdgesPtr_(nullptr)
{}


inline tnbLib::edgeMesh::edgeMesh(edgeMesh&& em)
	:
	fileFormats::edgeMeshFormatsCore(),
	points_(move(em.points_)),
	edges_(move(em.edges_)),
	pointEdgesPtr_(nullptr)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline const tnbLib::pointField& tnbLib::edgeMesh::points() const
{
	return points_;
}


inline const tnbLib::edgeList& tnbLib::edgeMesh::edges() const
{
	return edges_;
}


inline const tnbLib::labelListList& tnbLib::edgeMesh::pointEdges() const
{
	if (pointEdgesPtr_.empty())
	{
		calcPointEdges();
	}
	return pointEdgesPtr_();
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

void tnbLib::edgeMesh::operator=(const edgeMesh& rhs)
{
	points_ = rhs.points_;
	edges_ = rhs.edges_;
	pointEdgesPtr_.clear();
}


void tnbLib::edgeMesh::operator=(edgeMesh&& rhs)
{
	points_ = move(rhs.points_);
	edges_ = move(rhs.edges_);
	pointEdgesPtr_.clear();
}


// ************************************************************************* //