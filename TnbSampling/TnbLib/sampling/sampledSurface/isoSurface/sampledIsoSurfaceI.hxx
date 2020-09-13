#pragma once
#include <volPointInterpolation.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::sampledSurfaces::isoSurface::sampleField
(
	const GeometricField<Type, fvPatchField, volMesh>& vField
) const
{
	// Recreate geometry if time has changed
	updateGeometry();

	return tmp<Field<Type>>(new Field<Type>(vField, meshCells_));
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::sampledSurfaces::isoSurface::interpolateField
(
	const interpolation<Type>& interpolator
) const
{
	// Recreate geometry if time has changed
	updateGeometry();

	// One value per point
	tmp<Field<Type>> tvalues(new Field<Type>(points().size()));
	Field<Type>& values = tvalues.ref();

	boolList pointDone(points().size(), false);

	forAll(faces(), cutFacei)
	{
		const face& f = faces()[cutFacei];

		forAll(f, faceVertI)
		{
			label pointi = f[faceVertI];

			if (!pointDone[pointi])
			{
				values[pointi] = interpolator.interpolate
				(
					points()[pointi],
					meshCells_[cutFacei]
				);
				pointDone[pointi] = true;
			}
		}
	}

	return tvalues;
}


// ************************************************************************* //