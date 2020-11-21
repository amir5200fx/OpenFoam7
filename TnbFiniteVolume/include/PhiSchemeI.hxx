#pragma once
#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <fvcGrad.hxx>
#include <coupledFvPatchFields.hxx>
#include <surfaceInterpolate.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type, class PhiLimiter>
tnbLib::tmp<tnbLib::surfaceScalarField>
tnbLib::PhiScheme<Type, PhiLimiter>::limiter
(
	const GeometricField<Type, fvPatchField, volMesh>& phi
) const
{
	const fvMesh& mesh = this->mesh();

	tmp<surfaceScalarField> tLimiter
	(
		surfaceScalarField::New
		(
			"PhiLimiter",
			mesh,
			dimless
		)
	);
	surfaceScalarField& Limiter = tLimiter.ref();

	const surfaceScalarField& CDweights = mesh.surfaceInterpolation::weights();

	const surfaceVectorField& Sf = mesh.Sf();
	const surfaceScalarField& magSf = mesh.magSf();

	const labelUList& owner = mesh.owner();
	const labelUList& neighbour = mesh.neighbour();

	tmp<surfaceScalarField> tUflux = this->faceFlux_;

	if (this->faceFlux_.dimensions() == dimDensity * dimVelocity*dimArea)
	{
		const volScalarField& rho =
			phi.db().objectRegistry::template lookupObject<volScalarField>
			("rho");

		tUflux = this->faceFlux_ / fvc::interpolate(rho);
	}
	else if (this->faceFlux_.dimensions() != dimVelocity * dimArea)
	{
		FatalErrorInFunction
			<< "dimensions of faceFlux are not correct"
			<< exit(FatalError);
	}

	const surfaceScalarField& Uflux = tUflux();

	scalarField& pLimiter = Limiter.primitiveFieldRef();

	forAll(pLimiter, face)
	{
		pLimiter[face] = PhiLimiter::limiter
		(
			CDweights[face],
			Uflux[face],
			phi[owner[face]],
			phi[neighbour[face]],
			Sf[face],
			magSf[face]
		);
	}


	surfaceScalarField::Boundary& bLimiter =
		Limiter.boundaryFieldRef();

	forAll(bLimiter, patchi)
	{
		scalarField& pLimiter = bLimiter[patchi];

		if (bLimiter[patchi].coupled())
		{
			const scalarField& pCDweights = CDweights.boundaryField()[patchi];
			const vectorField& pSf = Sf.boundaryField()[patchi];
			const scalarField& pmagSf = magSf.boundaryField()[patchi];
			const scalarField& pFaceFlux = Uflux.boundaryField()[patchi];

			const Field<Type> pphiP
			(
				phi.boundaryField()[patchi].patchInternalField()
			);
			const Field<Type> pphiN
			(
				phi.boundaryField()[patchi].patchNeighbourField()
			);

			forAll(pLimiter, face)
			{
				pLimiter[face] = PhiLimiter::limiter
				(
					pCDweights[face],
					pFaceFlux[face],
					pphiP[face],
					pphiN[face],
					pSf[face],
					pmagSf[face]
				);
			}
		}
		else
		{
			pLimiter = 1.0;
		}
	}

	return tLimiter;
}


// ************************************************************************* //