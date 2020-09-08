#pragma once
#include <gaussGrad.hxx>
#include <surfaceMesh.hxx>  // added by amir
#include <fvBoundaryMesh.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type, class Limiter>
void tnbLib::fv::cellLimitedGrad<Type, Limiter>::limitGradient
(
	const Field<scalar>& limiter,
	Field<vector>& gIf
) const
{
	gIf *= limiter;
}


template<class Type, class Limiter>
void tnbLib::fv::cellLimitedGrad<Type, Limiter>::limitGradient
(
	const Field<vector>& limiter,
	Field<tensor>& gIf
) const
{
	forAll(gIf, celli)
	{
		gIf[celli] = tensor
		(
			cmptMultiply(limiter[celli], gIf[celli].x()),
			cmptMultiply(limiter[celli], gIf[celli].y()),
			cmptMultiply(limiter[celli], gIf[celli].z())
		);
	}
}


template<class Type, class Limiter>
tnbLib::tmp
<
	tnbLib::GeometricField
	<
	typename tnbLib::outerProduct<tnbLib::vector, Type>::type,
	tnbLib::fvPatchField,
	tnbLib::volMesh
	>
>
tnbLib::fv::cellLimitedGrad<Type, Limiter>::calcGrad
(
	const GeometricField<Type, fvPatchField, volMesh>& vsf,
	const word& name
) const
{
	const fvMesh& mesh = vsf.mesh();

	tmp
		<
		GeometricField
		<typename outerProduct<vector, Type>::type, fvPatchField, volMesh>
		> tGrad = basicGradScheme_().calcGrad(vsf, name);

	if (k_ < small)
	{
		return tGrad;
	}

	GeometricField
		<
		typename outerProduct<vector, Type>::type,
		fvPatchField,
		volMesh
		>& g = tGrad.ref();

	const labelUList& owner = mesh.owner();
	const labelUList& neighbour = mesh.neighbour();

	const volVectorField& C = mesh.C();
	const surfaceVectorField& Cf = mesh.Cf();

	Field<Type> maxVsf(vsf.primitiveField());
	Field<Type> minVsf(vsf.primitiveField());

	forAll(owner, facei)
	{
		label own = owner[facei];
		label nei = neighbour[facei];

		const Type& vsfOwn = vsf[own];
		const Type& vsfNei = vsf[nei];

		maxVsf[own] = max(maxVsf[own], vsfNei);
		minVsf[own] = min(minVsf[own], vsfNei);

		maxVsf[nei] = max(maxVsf[nei], vsfOwn);
		minVsf[nei] = min(minVsf[nei], vsfOwn);
	}


	const typename GeometricField<Type, fvPatchField, volMesh>::Boundary& bsf =
		vsf.boundaryField();

	forAll(bsf, patchi)
	{
		const fvPatchField<Type>& psf = bsf[patchi];
		const labelUList& pOwner = mesh.boundary()[patchi].faceCells();

		if (psf.coupled())
		{
			const Field<Type> psfNei(psf.patchNeighbourField());

			forAll(pOwner, pFacei)
			{
				label own = pOwner[pFacei];
				const Type& vsfNei = psfNei[pFacei];

				maxVsf[own] = max(maxVsf[own], vsfNei);
				minVsf[own] = min(minVsf[own], vsfNei);
			}
		}
		else
		{
			forAll(pOwner, pFacei)
			{
				label own = pOwner[pFacei];
				const Type& vsfNei = psf[pFacei];

				maxVsf[own] = max(maxVsf[own], vsfNei);
				minVsf[own] = min(minVsf[own], vsfNei);
			}
		}
	}

	maxVsf -= vsf;
	minVsf -= vsf;

	if (k_ < 1.0)
	{
		const Field<Type> maxMinVsf((1.0 / k_ - 1.0)*(maxVsf - minVsf));
		maxVsf += maxMinVsf;
		minVsf -= maxMinVsf;
	}


	// Create limiter initialized to 1
	// Note: the limiter is not permitted to be > 1
	Field<Type> limiter(vsf.primitiveField().size(), pTraits<Type>::one);

	forAll(owner, facei)
	{
		label own = owner[facei];
		label nei = neighbour[facei];

		// owner side
		limitFace
		(
			limiter[own],
			maxVsf[own],
			minVsf[own],
			(Cf[facei] - C[own]) & g[own]
		);

		// neighbour side
		limitFace
		(
			limiter[nei],
			maxVsf[nei],
			minVsf[nei],
			(Cf[facei] - C[nei]) & g[nei]
		);
	}

	forAll(bsf, patchi)
	{
		const labelUList& pOwner = mesh.boundary()[patchi].faceCells();
		const vectorField& pCf = Cf.boundaryField()[patchi];

		forAll(pOwner, pFacei)
		{
			label own = pOwner[pFacei];

			limitFace
			(
				limiter[own],
				maxVsf[own],
				minVsf[own],
				((pCf[pFacei] - C[own]) & g[own])
			);
		}
	}

	if (fv::debug)
	{
		Info << "gradient limiter for: " << vsf.name()
			<< " max = " << gMax(limiter)
			<< " min = " << gMin(limiter)
			<< " average: " << gAverage(limiter) << endl;
	}

	limitGradient(limiter, g);
	g.correctBoundaryConditions();
	gaussGrad<Type>::correctBoundaryConditions(vsf, g);

	return tGrad;
}


// ************************************************************************* //