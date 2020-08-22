#pragma once
// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

inline const tnbLib::polyMesh& tnbLib::meshToMesh::srcRegion() const
{
	return srcRegion_;
}


inline const tnbLib::polyMesh& tnbLib::meshToMesh::tgtRegion() const
{
	return tgtRegion_;
}


inline const tnbLib::labelListList&
tnbLib::meshToMesh::srcToTgtCellAddr() const
{
	return srcToTgtCellAddr_;
}


inline const tnbLib::labelListList&
tnbLib::meshToMesh::tgtToSrcCellAddr() const
{
	return tgtToSrcCellAddr_;
}


inline const tnbLib::scalarListList&
tnbLib::meshToMesh::srcToTgtCellWght() const
{
	return srcToTgtCellWght_;
}


inline const tnbLib::scalarListList&
tnbLib::meshToMesh::tgtToSrcCellWght() const
{
	return tgtToSrcCellWght_;
}


inline tnbLib::scalar tnbLib::meshToMesh::V() const
{
	return V_;
}


inline const tnbLib::PtrList<tnbLib::AMIInterpolation>&
tnbLib::meshToMesh::patchAMIs() const
{
	return patchAMIs_;
}


// ************************************************************************* //