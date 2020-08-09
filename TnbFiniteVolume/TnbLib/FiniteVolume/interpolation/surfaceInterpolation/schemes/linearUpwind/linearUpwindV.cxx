#include <linearUpwindV.hxx>

#include <fvMesh.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::tmp<tnbLib::GeometricField<Type, tnbLib::fvsPatchField, tnbLib::surfaceMesh>>
tnbLib::linearUpwindV<Type>::correction
(
	const GeometricField<Type, fvPatchField, volMesh>& vf
) const
{
	const fvMesh& mesh = this->mesh();

	tmp<GeometricField<Type, fvsPatchField, surfaceMesh>> tsfCorr
	(
		new GeometricField<Type, fvsPatchField, surfaceMesh>
		(
			IOobject
			(
				"linearUpwindV::correction(" + vf.name() + ')',
				mesh.time().timeName(),
				mesh,
				IOobject::NO_READ,
				IOobject::NO_WRITE,
				false
			),
			mesh,
			dimensioned<Type>
			(
				vf.name(),
				vf.dimensions(),
				Zero
				)
			)
	);

	GeometricField<Type, fvsPatchField, surfaceMesh>& sfCorr = tsfCorr.ref();

	const surfaceScalarField& faceFlux = this->faceFlux_;
	const surfaceScalarField& w = mesh.weights();

	const labelList& own = mesh.owner();
	const labelList& nei = mesh.neighbour();

	const volVectorField& C = mesh.C();
	const surfaceVectorField& Cf = mesh.Cf();

	tmp
		<
		GeometricField
		<
		typename outerProduct<vector, Type>::type,
		fvPatchField,
		volMesh
		>
		> tgradVf = gradScheme_().grad(vf, gradSchemeName_);

	const GeometricField
		<
		typename outerProduct<vector, Type>::type,
		fvPatchField,
		volMesh
		>& gradVf = tgradVf();

	forAll(faceFlux, facei)
	{
		vector maxCorr;

		if (faceFlux[facei] > 0.0)
		{
			maxCorr =
				(1.0 - w[facei])*(vf[nei[facei]] - vf[own[facei]]);

			sfCorr[facei] =
				(Cf[facei] - C[own[facei]]) & gradVf[own[facei]];
		}
		else
		{
			maxCorr =
				w[facei] * (vf[own[facei]] - vf[nei[facei]]);

			sfCorr[facei] =
				(Cf[facei] - C[nei[facei]]) & gradVf[nei[facei]];
		}

		scalar sfCorrs = magSqr(sfCorr[facei]);
		scalar maxCorrs = sfCorr[facei] & maxCorr;

		if (sfCorrs > 0)
		{
			if (maxCorrs < 0)
			{
				sfCorr[facei] = Zero;
			}
			else if (sfCorrs > maxCorrs)
			{
				sfCorr[facei] *= maxCorrs / (sfCorrs + vSmall);
			}
		}
	}


	typename GeometricField<Type, fvsPatchField, surfaceMesh>::
		Boundary& bSfCorr = sfCorr.boundaryFieldRef();

	forAll(bSfCorr, patchi)
	{
		fvsPatchField<Type>& pSfCorr = bSfCorr[patchi];

		if (pSfCorr.coupled())
		{
			const labelUList& pOwner =
				mesh.boundary()[patchi].faceCells();

			const vectorField& pCf = Cf.boundaryField()[patchi];
			const scalarField& pW = w.boundaryField()[patchi];

			const scalarField& pFaceFlux = faceFlux.boundaryField()[patchi];

			const Field<typename outerProduct<vector, Type>::type> pGradVfNei
			(
				gradVf.boundaryField()[patchi].patchNeighbourField()
			);

			const Field<Type> pVfNei
			(
				vf.boundaryField()[patchi].patchNeighbourField()
			);

			// Build the d-vectors
			vectorField pd(Cf.boundaryField()[patchi].patch().delta());

			forAll(pOwner, facei)
			{
				label own = pOwner[facei];

				vector maxCorr;

				if (pFaceFlux[facei] > 0)
				{
					pSfCorr[facei] = (pCf[facei] - C[own]) & gradVf[own];

					maxCorr = (1.0 - pW[facei])*(pVfNei[facei] - vf[own]);
				}
				else
				{
					pSfCorr[facei] =
						(pCf[facei] - pd[facei] - C[own]) & pGradVfNei[facei];

					maxCorr = pW[facei] * (vf[own] - pVfNei[facei]);
				}

				scalar pSfCorrs = magSqr(pSfCorr[facei]);
				scalar maxCorrs = pSfCorr[facei] & maxCorr;

				if (pSfCorrs > 0)
				{
					if (maxCorrs < 0)
					{
						pSfCorr[facei] = Zero;
					}
					else if (pSfCorrs > maxCorrs)
					{
						pSfCorr[facei] *= maxCorrs / (pSfCorrs + vSmall);
					}
				}
			}
		}
	}

	return tsfCorr;
}


namespace tnbLib
{
	makelimitedSurfaceInterpolationTypeScheme(linearUpwindV, vector)
}


// ************************************************************************* //