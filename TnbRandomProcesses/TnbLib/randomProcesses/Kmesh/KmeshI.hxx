#pragma once
inline tnbLib::label tnbLib::Kmesh::index
(
	const label i,
	const label j,
	const label k,
	const labelList& nn
)
{
	return (k + j * nn[2] + i * nn[1] * nn[2]);
}