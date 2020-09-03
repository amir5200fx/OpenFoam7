#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::labelHashSet tnbLib::polyBoundaryMesh::findPatchIDs() const
{
	const polyBoundaryMesh& bm = *this;

	labelHashSet patchIDs(bm.size());

	forAll(bm, patchi)
	{
		if (isA<Type>(bm[patchi]))
		{
			patchIDs.insert(patchi);
		}
	}
	return patchIDs;
}


// ************************************************************************* //