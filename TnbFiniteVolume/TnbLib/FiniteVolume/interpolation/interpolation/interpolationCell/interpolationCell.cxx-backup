#include <interpolationCell.hxx>

#include <volFields.hxx>

// * * * * * * * * * * * * * * * * Constructor * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::interpolationCell<Type>::interpolationCell
(
	const GeometricField<Type, fvPatchField, volMesh>& psi
)
	:
	interpolation<Type>(psi)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
Type tnbLib::interpolationCell<Type>::interpolate
(
	const vector&,
	const label celli,
	const label
) const
{
	return this->psi_[celli];
}


// ************************************************************************* //