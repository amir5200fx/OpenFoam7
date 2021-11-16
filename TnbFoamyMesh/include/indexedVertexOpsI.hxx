#pragma once
// * * * * * * * * * * * * * * * Global Functions  * * * * * * * * * * * * * //

template<class VertexType>
tnbLib::scalar CGAL::indexedVertexOps::averageCellSize
(
	const VertexType& vA,
	const VertexType& vB
)
{
	// Arithmetic mean
	// return 0.5*(vA->targetCellSize() + vB->targetCellSize());

	// Geometric mean
	return sqrt(vA->targetCellSize() * vB->targetCellSize());

	// Harmonic mean
	// return
	//     2.0*(vA->targetCellSize()*vB->targetCellSize())
	//    /(vA->targetCellSize() + vB->targetCellSize());
}


template<class VertexType>
inline bool CGAL::indexedVertexOps::uninitialised(const VertexType& v)
{
	return v->type() == tnbLib::indexedVertexEnum::vtUnassigned;
}


// ************************************************************************* //
