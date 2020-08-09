#include <linearUpwind.hxx>

#include <fvMesh.hxx>
#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::tmp<tnbLib::GeometricField<Type, tnbLib::fvsPatchField, tnbLib::surfaceMesh>>
tnbLib::linearUpwind<Type>::correction
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
				"linearUpwind::correction(" + vf.name() + ')',
				mesh.time().timeName(),
				mesh,
				IOobject::NO_READ,
				IOobject::NO_WRITE,
				false
			),
			mesh,
			dimensioned<Type>(vf.name(), vf.dimensions(), Zero)
			)
	);

	GeometricField<Type, fvsPatchField, surfaceMesh>& sfCorr = tsfCorr.ref();

	const surfaceScalarField& faceFlux = this->faceFlux_;

	const labelList& owner = mesh.owner();
	const labelList& neighbour = mesh.neighbour();

	const volVectorField& C = mesh.C();
	const surfaceVectorField& Cf = mesh.Cf();

	tmp<fv::gradScheme<scalar>> gradScheme_
	(
		fv::gradScheme<scalar>::New
		(
			mesh,
			mesh.gradScheme(gradSchemeName_)
		)
	);

	for (direction cmpt = 0; cmpt < pTraits<Type>::nComponents; cmpt++)
	{
		tmp<volVectorField> tgradVf =
			gradScheme_().grad(vf.component(cmpt), gradSchemeName_);

		const volVectorField& gradVf = tgradVf();

		forAll(faceFlux, facei)
		{
			const label celli =
				(faceFlux[facei] > 0) ? owner[facei] : neighbour[facei];

			setComponent(sfCorr[facei], cmpt) =
				(Cf[facei] - C[celli]) & gradVf[celli];
		}

		typename GeometricField<Type, fvsPatchField, surfaceMesh>::
			Boundary& bSfCorr = sfCorr.boundaryFieldRef();

		forAll(bSfCorr, patchi)
		{
			fvsPatchField<Type>& pSfCorr = bSfCorr[patchi];

			if (pSfCorr.coupled())
			{
				const labelUList& pOwner = mesh.boundary()[patchi].faceCells();
				const vectorField& pCf = Cf.boundaryField()[patchi];
				const scalarField& pFaceFlux = faceFlux.boundaryField()[patchi];

				const vectorField pGradVfNei
				(
					gradVf.boundaryField()[patchi].patchNeighbourField()
				);

				// Build the d-vectors
				const vectorField pd
				(
					Cf.boundaryField()[patchi].patch().delta()
				);

				forAll(pOwner, facei)
				{
					label own = pOwner[facei];

					if (pFaceFlux[facei] > 0)
					{
						setComponent(pSfCorr[facei], cmpt) =
							(pCf[facei] - C[own])
							& gradVf[own];
					}
					else
					{
						setComponent(pSfCorr[facei], cmpt) =
							(pCf[facei] - pd[facei] - C[own])
							& pGradVfNei[facei];
					}
				}
			}
		}
	}

	return tsfCorr;
}


template<>
tnbLib::tmp<tnbLib::surfaceVectorField>
tnbLib::linearUpwind<tnbLib::vector>::correction
(
	const volVectorField& vf
) const
{
	const fvMesh& mesh = this->mesh();

	tmp<surfaceVectorField> tsfCorr
	(
		surfaceVectorField::New
		(
			"linearUpwind::correction(" + vf.name() + ')',
			mesh,
			dimensioned<vector>(vf.name(), vf.dimensions(), Zero)
		)
	);

	surfaceVectorField& sfCorr = tsfCorr.ref();

	const surfaceScalarField& faceFlux = this->faceFlux_;

	const labelList& owner = mesh.owner();
	const labelList& neighbour = mesh.neighbour();

	const volVectorField& C = mesh.C();
	const surfaceVectorField& Cf = mesh.Cf();

	tmp<fv::gradScheme<vector>> gradScheme_
	(
		fv::gradScheme<vector>::New
		(
			mesh,
			mesh.gradScheme(gradSchemeName_)
		)
	);

	tmp<volTensorField> tgradVf = gradScheme_().grad(vf, gradSchemeName_);
	const volTensorField& gradVf = tgradVf();

	forAll(faceFlux, facei)
	{
		const label celli =
			(faceFlux[facei] > 0) ? owner[facei] : neighbour[facei];
		sfCorr[facei] = (Cf[facei] - C[celli]) & gradVf[celli];
	}


	typename surfaceVectorField::Boundary& bSfCorr = sfCorr.boundaryFieldRef();

	forAll(bSfCorr, patchi)
	{
		fvsPatchVectorField& pSfCorr = bSfCorr[patchi];

		if (pSfCorr.coupled())
		{
			const labelUList& pOwner = mesh.boundary()[patchi].faceCells();
			const vectorField& pCf = Cf.boundaryField()[patchi];
			const scalarField& pFaceFlux = faceFlux.boundaryField()[patchi];

			const tensorField pGradVfNei
			(
				gradVf.boundaryField()[patchi].patchNeighbourField()
			);

			// Build the d-vectors
			vectorField pd(Cf.boundaryField()[patchi].patch().delta());

			forAll(pOwner, facei)
			{
				label own = pOwner[facei];

				if (pFaceFlux[facei] > 0)
				{
					pSfCorr[facei] = (pCf[facei] - C[own]) & gradVf[own];
				}
				else
				{
					pSfCorr[facei] =
						(pCf[facei] - pd[facei] - C[own]) & pGradVfNei[facei];
				}
			}
		}
	}

	return tsfCorr;
}


namespace tnbLib
{
	makelimitedSurfaceInterpolationScheme(linearUpwind)
}

// ************************************************************************* //