#include <leastSquaresGrad.hxx>

#include <leastSquaresVectors.hxx>
#include <gaussGrad.hxx>
#include <fvMesh.hxx>
#include <volMesh.hxx>
#include <surfaceMesh.hxx>
#include <GeometricField.hxx>
#include <extrapolatedCalculatedFvPatchField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::tmp
<
	tnbLib::GeometricField
	<
	typename tnbLib::outerProduct<tnbLib::vector, Type>::type,
	tnbLib::fvPatchField,
	tnbLib::volMesh
	>
>
tnbLib::fv::leastSquaresGrad<Type>::calcGrad
(
	const GeometricField<Type, fvPatchField, volMesh>& vsf,
	const word& name
) const
{
	typedef typename outerProduct<vector, Type>::type GradType;

	const fvMesh& mesh = vsf.mesh();

	tmp<GeometricField<GradType, fvPatchField, volMesh>> tlsGrad
	(
		new GeometricField<GradType, fvPatchField, volMesh>
		(
			IOobject
			(
				name,
				vsf.instance(),
				mesh,
				IOobject::NO_READ,
				IOobject::NO_WRITE
			),
			mesh,
			dimensioned<GradType>
			(
				"zero",
				vsf.dimensions() / dimLength,
				Zero
				),
			extrapolatedCalculatedFvPatchField<GradType>::typeName
			)
	);
	GeometricField<GradType, fvPatchField, volMesh>& lsGrad = tlsGrad.ref();

	// Get reference to least square vectors
	const leastSquaresVectors& lsv = leastSquaresVectors::New(mesh);

	const surfaceVectorField& ownLs = lsv.pVectors();
	const surfaceVectorField& neiLs = lsv.nVectors();

	const labelUList& own = mesh.owner();
	const labelUList& nei = mesh.neighbour();

	forAll(own, facei)
	{
		label ownFacei = own[facei];
		label neiFacei = nei[facei];

		Type deltaVsf = vsf[neiFacei] - vsf[ownFacei];

		lsGrad[ownFacei] += ownLs[facei] * deltaVsf;
		lsGrad[neiFacei] -= neiLs[facei] * deltaVsf;
	}

	// Boundary faces
	forAll(vsf.boundaryField(), patchi)
	{
		const fvsPatchVectorField& patchOwnLs = ownLs.boundaryField()[patchi];

		const labelUList& faceCells =
			vsf.boundaryField()[patchi].patch().faceCells();

		if (vsf.boundaryField()[patchi].coupled())
		{
			const Field<Type> neiVsf
			(
				vsf.boundaryField()[patchi].patchNeighbourField()
			);

			forAll(neiVsf, patchFacei)
			{
				lsGrad[faceCells[patchFacei]] +=
					patchOwnLs[patchFacei]
					* (neiVsf[patchFacei] - vsf[faceCells[patchFacei]]);
			}
		}
		else
		{
			const fvPatchField<Type>& patchVsf = vsf.boundaryField()[patchi];

			forAll(patchVsf, patchFacei)
			{
				lsGrad[faceCells[patchFacei]] +=
					patchOwnLs[patchFacei]
					* (patchVsf[patchFacei] - vsf[faceCells[patchFacei]]);
			}
		}
	}


	lsGrad.correctBoundaryConditions();
	gaussGrad<Type>::correctBoundaryConditions(vsf, lsGrad);

	return tlsGrad;
}


// ************************************************************************* //