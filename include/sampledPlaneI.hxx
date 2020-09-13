#pragma once
// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::sampledSurfaces::plane::sampleField
(
	const GeometricField<Type, fvPatchField, volMesh>& vField
) const
{
	return tmp<Field<Type>>(new Field<Type>(vField, meshCells()));
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::sampledSurfaces::plane::interpolateField
(
	const interpolation<Type>& interpolator
) const
{
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
					meshCells()[cutFacei]
				);
				pointDone[pointi] = true;
			}
		}
	}

	return tvalues;
}


// ************************************************************************* //