#include <sampledPatch.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::sampledSurfaces::patch::sampleField
(
	const GeometricField<Type, fvPatchField, volMesh>& vField
) const
{
	// One value per face
	tmp<Field<Type>> tvalues(new Field<Type>(patchFaceLabels_.size()));
	Field<Type>& values = tvalues.ref();
	forAll(patchFaceLabels_, i)
	{
		label patchi = patchIDs_[patchIndex_[i]];
		const Field<Type>& bField = vField.boundaryField()[patchi];
		values[i] = bField[patchFaceLabels_[i]];
	}

	return tvalues;
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::sampledSurfaces::patch::sampleField
(
	const GeometricField<Type, fvsPatchField, surfaceMesh>& sField
) const
{
	// One value per face
	tmp<Field<Type>> tvalues(new Field<Type>(patchFaceLabels_.size()));
	Field<Type>& values = tvalues.ref();

	forAll(patchFaceLabels_, i)
	{
		label patchi = patchIDs_[patchIndex_[i]];
		values[i] = sField.boundaryField()[patchi][patchFaceLabels_[i]];
	}

	return tvalues;
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::sampledSurfaces::patch::interpolateField
(
	const interpolation<Type>& interpolator
) const
{
	// One value per vertex
	tmp<Field<Type>> tvalues(new Field<Type>(points().size()));
	Field<Type>& values = tvalues.ref();

	const labelList& own = mesh().faceOwner();

	boolList pointDone(points().size(), false);

	forAll(faces(), cutFacei)
	{
		label patchi = patchIDs_[patchIndex_[cutFacei]];
		const polyPatch& pp = mesh().boundaryMesh()[patchi];
		label patchFacei = patchFaceLabels()[cutFacei];
		const face& f = faces()[cutFacei];

		forAll(f, faceVertI)
		{
			label pointi = f[faceVertI];

			if (!pointDone[pointi])
			{
				label facei = patchFacei + pp.start();
				label celli = own[facei];

				values[pointi] = interpolator.interpolate
				(
					points()[pointi],
					celli,
					facei
				);
				pointDone[pointi] = true;
			}
		}
	}

	return tvalues;
}


// ************************************************************************* //