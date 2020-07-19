#include <interpolationCellPatchConstrained.hxx>

#include <volFields.hxx>

// * * * * * * * * * * * * * * * * Constructor * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::interpolationCellPatchConstrained<Type>::interpolationCellPatchConstrained
(
	const GeometricField<Type, fvPatchField, volMesh>& psi
)
	:
	interpolation<Type>(psi)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
Type tnbLib::interpolationCellPatchConstrained<Type>::interpolate
(
	const vector& pt,
	const label celli,
	const label facei
) const
{
	if (facei >= 0 && facei >= this->psi_.mesh().nInternalFaces())
	{
		// Use boundary value
		const polyBoundaryMesh& pbm = this->psi_.mesh().boundaryMesh();
		label patchi = pbm.patchID()[facei - this->psi_.mesh().nInternalFaces()];
		label patchFacei = pbm[patchi].whichFace(facei);

		return this->psi_.boundaryField()[patchi][patchFacei];
	}
	else
	{
		return this->psi_[celli];
	}
}


// ************************************************************************* //