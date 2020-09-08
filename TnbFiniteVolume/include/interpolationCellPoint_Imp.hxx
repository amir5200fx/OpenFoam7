#pragma once
#include <volPointInterpolation.hxx>

// * * * * * * * * * * * * * * * * Constructor * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::interpolationCellPoint<Type>::interpolationCellPoint
(
	const GeometricField<Type, fvPatchField, volMesh>& psi
)
	:
	interpolation<Type>(psi),
	psip_
	(
		volPointInterpolation::New(psi.mesh()).interpolate
		(
			psi,
			"volPointInterpolate(" + psi.name() + ')',
			true        // use cache
		)
	)
{
	// Uses cellPointWeight to do interpolation which needs tet decomposition
	(void)psi.mesh().tetBasePtIs();
}


template<class Type>
tnbLib::interpolationCellPoint<Type>::interpolationCellPoint
(
	const GeometricField<Type, fvPatchField, volMesh>& psi,
	tmp<GeometricField<Type, pointPatchField, pointMesh>> psip
)
	:
	interpolation<Type>(psi),
	psip_(psip)
{
	// Uses cellPointWeight to do interpolation which needs tet decomposition
	(void)psi.mesh().tetBasePtIs();
}


// ************************************************************************* //