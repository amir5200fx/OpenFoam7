#pragma once
#include <polyMesh.hxx>
#include <polyBoundaryMesh.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::labelHashSet tnbLib::cellDistFuncs::getPatchIDs() const
{
	const polyBoundaryMesh& bMesh = mesh().boundaryMesh();

	labelHashSet patchIDs(bMesh.size());

	forAll(bMesh, patchi)
	{
		if (isA<Type>(bMesh[patchi]))
		{
			patchIDs.insert(patchi);
		}
	}
	return patchIDs;
}


// ************************************************************************* //