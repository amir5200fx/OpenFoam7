#include <sampledCuttingPlane.hxx>

#include <volPointInterpolation.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::sampledSurfaces::cuttingPlane::sampleField
(
	const GeometricField<Type, fvPatchField, volMesh>& vField
) const
{
	return tmp<Field<Type>>(new Field<Type>(vField, surface().meshCells()));
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::sampledSurfaces::cuttingPlane::interpolateField
(
	const interpolation<Type>& interpolator
) const
{
	// Get fields to sample. Assume volPointInterpolation!
	const GeometricField<Type, fvPatchField, volMesh>& volFld =
		interpolator.psi();

	if (subMeshPtr_.valid())
	{
		tmp<GeometricField<Type, fvPatchField, volMesh>> tvolSubFld =
			subMeshPtr_().interpolate(volFld);

		const GeometricField<Type, fvPatchField, volMesh>& volSubFld =
			tvolSubFld();

		tmp<GeometricField<Type, pointPatchField, pointMesh>> tpointSubFld =
			volPointInterpolation::New(volSubFld.mesh()).interpolate(volSubFld);

		// Sample.
		return surface().interpolate
		(
			(
				average_
				? pointAverage(tpointSubFld())()
				: volSubFld
				),
			tpointSubFld()
		);
	}
	else
	{
		tmp<GeometricField<Type, pointPatchField, pointMesh>> tpointFld
		(
			volPointInterpolation::New(volFld.mesh()).interpolate(volFld)
		);

		// Sample.
		return surface().interpolate
		(
			(
				average_
				? pointAverage(tpointFld())()
				: volFld
				),
			tpointFld()
		);
	}
}


// ************************************************************************* //