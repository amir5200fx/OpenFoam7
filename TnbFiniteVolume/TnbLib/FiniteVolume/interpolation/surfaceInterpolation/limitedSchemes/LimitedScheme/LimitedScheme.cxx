#include <LimitedScheme.hxx>

#include <surfaceFields.hxx>
#include <fvcGrad.hxx>
#include <coupledFvsPatchFields.hxx>

// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

template<class Type, class Limiter, template<class> class LimitFunc>
void tnbLib::LimitedScheme<Type, Limiter, LimitFunc>::calcLimiter
(
	const GeometricField<Type, fvPatchField, volMesh>& phi,
	surfaceScalarField& limiterField
) const
{
	const fvMesh& mesh = this->mesh();

	tmp<GeometricField<typename Limiter::phiType, fvPatchField, volMesh>>
		tlPhi = LimitFunc<Type>()(phi);

	const GeometricField<typename Limiter::phiType, fvPatchField, volMesh>&
		lPhi = tlPhi();

	tmp<GeometricField<typename Limiter::gradPhiType, fvPatchField, volMesh>>
		tgradc(fvc::grad(lPhi));
	const GeometricField<typename Limiter::gradPhiType, fvPatchField, volMesh>&
		gradc = tgradc();

	const surfaceScalarField& CDweights = mesh.surfaceInterpolation::weights();

	const labelUList& owner = mesh.owner();
	const labelUList& neighbour = mesh.neighbour();

	const vectorField& C = mesh.C();

	scalarField& pLim = limiterField.primitiveFieldRef();

	forAll(pLim, face)
	{
		label own = owner[face];
		label nei = neighbour[face];

		pLim[face] = Limiter::limiter
		(
			CDweights[face],
			this->faceFlux_[face],
			lPhi[own],
			lPhi[nei],
			gradc[own],
			gradc[nei],
			C[nei] - C[own]
		);
	}

	surfaceScalarField::Boundary& bLim =
		limiterField.boundaryFieldRef();

	forAll(bLim, patchi)
	{
		scalarField& pLim = bLim[patchi];

		if (bLim[patchi].coupled())
		{
			const scalarField& pCDweights = CDweights.boundaryField()[patchi];
			const scalarField& pFaceFlux =
				this->faceFlux_.boundaryField()[patchi];

			const Field<typename Limiter::phiType> plPhiP
			(
				lPhi.boundaryField()[patchi].patchInternalField()
			);
			const Field<typename Limiter::phiType> plPhiN
			(
				lPhi.boundaryField()[patchi].patchNeighbourField()
			);
			const Field<typename Limiter::gradPhiType> pGradcP
			(
				gradc.boundaryField()[patchi].patchInternalField()
			);
			const Field<typename Limiter::gradPhiType> pGradcN
			(
				gradc.boundaryField()[patchi].patchNeighbourField()
			);

			// Build the d-vectors
			vectorField pd(CDweights.boundaryField()[patchi].patch().delta());

			forAll(pLim, face)
			{
				pLim[face] = Limiter::limiter
				(
					pCDweights[face],
					pFaceFlux[face],
					plPhiP[face],
					plPhiN[face],
					pGradcP[face],
					pGradcN[face],
					pd[face]
				);
			}
		}
		else
		{
			pLim = 1.0;
		}
	}
}


// * * * * * * * * * * * * Public Member Functions  * * * * * * * * * * * * //

template<class Type, class Limiter, template<class> class LimitFunc>
tnbLib::tmp<tnbLib::surfaceScalarField>
tnbLib::LimitedScheme<Type, Limiter, LimitFunc>::limiter
(
	const GeometricField<Type, fvPatchField, volMesh>& phi
) const
{
	const fvMesh& mesh = this->mesh();

	const word limiterFieldName(type() + "Limiter(" + phi.name() + ')');

	if (this->mesh().cache("limiter"))
	{
		if (!mesh.foundObject<surfaceScalarField>(limiterFieldName))
		{
			surfaceScalarField* limiterField
			(
				new surfaceScalarField
				(
					IOobject
					(
						limiterFieldName,
						mesh.time().timeName(),
						mesh,
						IOobject::NO_READ,
						IOobject::NO_WRITE
					),
					mesh,
					dimless
				)
			);

			mesh.objectRegistry::store(limiterField);
		}

		surfaceScalarField& limiterField =
			mesh.lookupObjectRef<surfaceScalarField>
			(
				limiterFieldName
				);

		calcLimiter(phi, limiterField);

		return limiterField;
	}
	else
	{
		tmp<surfaceScalarField> tlimiterField
		(
			new surfaceScalarField
			(
				IOobject
				(
					limiterFieldName,
					mesh.time().timeName(),
					mesh
				),
				mesh,
				dimless
			)
		);

		calcLimiter(phi, tlimiterField.ref());

		return tlimiterField;
	}
}


// ************************************************************************* //