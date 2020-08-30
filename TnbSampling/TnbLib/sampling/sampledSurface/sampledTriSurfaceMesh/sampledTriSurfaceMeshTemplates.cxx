#include <sampledTriSurfaceMesh.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::sampledSurfaces::triSurfaceMesh::sampleField
(
	const GeometricField<Type, fvPatchField, volMesh>& vField
) const
{
	// One value per face
	tmp<Field<Type>> tvalues(new Field<Type>(sampleElements_.size()));
	Field<Type>& values = tvalues.ref();

	if (sampleSource_ == cells || sampleSource_ == insideCells)
	{
		// Sample cells

		forAll(sampleElements_, triI)
		{
			values[triI] = vField[sampleElements_[triI]];
		}
	}
	else
	{
		// Sample boundary faces

		const polyBoundaryMesh& pbm = mesh().boundaryMesh();
		label nBnd = mesh().nFaces() - mesh().nInternalFaces();

		// Create flat boundary field

		Field<Type> bVals(nBnd, Zero);

		forAll(vField.boundaryField(), patchi)
		{
			label bFacei = pbm[patchi].start() - mesh().nInternalFaces();

			SubList<Type>
				(
					bVals,
					vField.boundaryField()[patchi].size(),
					bFacei
					) = vField.boundaryField()[patchi];
		}

		// Sample in flat boundary field

		forAll(sampleElements_, triI)
		{
			label facei = sampleElements_[triI];
			values[triI] = bVals[facei - mesh().nInternalFaces()];
		}
	}

	return tvalues;
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>>
tnbLib::sampledSurfaces::triSurfaceMesh::interpolateField
(
	const interpolation<Type>& interpolator
) const
{
	// One value per vertex
	tmp<Field<Type>> tvalues(new Field<Type>(sampleElements_.size()));
	Field<Type>& values = tvalues.ref();

	if (sampleSource_ == cells || sampleSource_ == insideCells)
	{
		// Sample cells.

		forAll(sampleElements_, pointi)
		{
			values[pointi] = interpolator.interpolate
			(
				samplePoints_[pointi],
				sampleElements_[pointi]
			);
		}
	}
	else
	{
		// Sample boundary faces.

		forAll(samplePoints_, pointi)
		{
			label facei = sampleElements_[pointi];

			values[pointi] = interpolator.interpolate
			(
				samplePoints_[pointi],
				mesh().faceOwner()[facei],
				facei
			);
		}
	}

	return tvalues;
}


// ************************************************************************* //