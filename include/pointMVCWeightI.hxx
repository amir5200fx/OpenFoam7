#pragma once
#include <pointFields.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
inline Type tnbLib::pointMVCWeight::interpolate
(
	const GeometricField<Type, pointPatchField, pointMesh>& psip
) const
{
	const labelList& vertices = psip.mesh()().cellPoints()[cellIndex_];

	Type t = Zero;
	forAll(vertices, i)
	{
		t += psip[vertices[i]] * weights_[i];
	}

	return t;
}


// ************************************************************************* //