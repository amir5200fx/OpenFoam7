#pragma once
#include <volPointInterpolation.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::sampledSurfaces::distanceSurface::sampleField
(
	const GeometricField<Type, fvPatchField, volMesh>& vField
) const
{
	return tmp<Field<Type>>
		(
			new Field<Type>(vField, isoSurfPtr_().meshCells())
			);
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::sampledSurfaces::distanceSurface::interpolateField
(
	const interpolation<Type>& interpolator
) const
{
	const fvMesh& fvm = static_cast<const fvMesh&>(mesh());

	// Get fields to sample. Assume volPointInterpolation!
	const GeometricField<Type, fvPatchField, volMesh>& volFld =
		interpolator.psi();

	tmp<GeometricField<Type, pointPatchField, pointMesh>> pointFld
	(
		volPointInterpolation::New(fvm).interpolate(volFld)
	);

	return isoSurfPtr_().interpolate
	(
		(
			average_
			? pointAverage(pointFld())()
			: volFld
			),
		pointFld()
	);
}


// ************************************************************************* //