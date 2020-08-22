#pragma once
const tnbLib::polyMesh& tnbLib::meshToMeshMethod::src() const
{
	return src_;
}


const tnbLib::polyMesh& tnbLib::meshToMeshMethod::tgt() const
{
	return tgt_;
}


tnbLib::scalar tnbLib::meshToMeshMethod::V() const
{
	return V_;
}


// ************************************************************************* //