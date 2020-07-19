#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
inline Type tnbLib::interpolationCellPoint<Type>::interpolate
(
	const cellPointWeight& cpw
) const
{
	const barycentric& weights = cpw.weights();
	const triFace& faceVertices = cpw.faceVertices();

	Type t = this->psi_[cpw.cell()] * weights[0];
	t += psip_[faceVertices[0]] * weights[1];
	t += psip_[faceVertices[1]] * weights[2];
	t += psip_[faceVertices[2]] * weights[3];

	return t;
}


template<class Type>
inline Type tnbLib::interpolationCellPoint<Type>::interpolate
(
	const vector& position,
	const label celli,
	const label facei
) const
{
	return interpolate(cellPointWeight(this->pMesh_, position, celli, facei));
}


template<class Type>
inline Type tnbLib::interpolationCellPoint<Type>::interpolate
(
	const barycentric& coordinates,
	const tetIndices& tetIs,
	const label facei
) const
{
	// Assumes that the position is consistent with the supplied
	// tetIndices.  Does not pay attention to whether or not facei is
	// supplied or not - the result will be essentially the same.
	// Performs a consistency check, however.

	if (facei >= 0)
	{
		if (facei != tetIs.face())
		{
			FatalErrorInFunction
				<< "specified face " << facei << " inconsistent with the face "
				<< "stored by tetIndices: " << tetIs.face()
				<< exit(FatalError);
		}
	}

	const triFace triIs = tetIs.faceTriIs(this->pMesh_);

	return
		this->psi_[tetIs.cell()] * coordinates[0]
		+ psip_[triIs[0]] * coordinates[1]
		+ psip_[triIs[1]] * coordinates[2]
		+ psip_[triIs[2]] * coordinates[3];
}


// ************************************************************************* //