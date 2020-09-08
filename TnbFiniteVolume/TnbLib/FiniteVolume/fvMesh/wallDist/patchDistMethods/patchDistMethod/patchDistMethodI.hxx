#pragma once
#include <fvMesh.hxx>  // added by amir

// * * * * * * * * * * * * * * * Static Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::wordList tnbLib::patchDistMethod::patchTypes
(
	const fvMesh& mesh,
	const labelHashSet& patchIDs
)
{
	wordList yTypes
	(
		mesh.boundary().size(),
		zeroGradientFvPatchField<Type>::typeName
	);

	forAllConstIter(labelHashSet, patchIDs, iter)
	{
		yTypes[iter.key()] = fixedValueFvPatchField<Type>::typeName;
	}

	return yTypes;
}


// ************************************************************************* //
