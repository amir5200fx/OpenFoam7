#pragma once
// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

// Transfer contents of DynamicList to List
template<class T>
void tnbLib::surfaceIntersection::transfer
(
	List<DynamicList<T>>& srcLst,
	List<List<T>>& dstLst
)
{
	dstLst.setSize(srcLst.size());

	forAll(srcLst, elemI)
	{
		dstLst[elemI].transfer(srcLst[elemI]);
	}
}


// ************************************************************************* //