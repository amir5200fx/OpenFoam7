#include <cellMDLimitedGrad.hxx>

#include <gaussGrad.hxx>
#include <fvMesh.hxx>
#include <volMesh.hxx>
#include <surfaceMesh.hxx>
#include <volFields.hxx>
#include <fixedValueFvPatchFields.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

makeFvGradScheme(cellMDLimitedGrad)

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<>
tnbLib::tmp<tnbLib::volVectorField>
tnbLib::fv::cellMDLimitedGrad<tnbLib::scalar>::calcGrad
(
	const volScalarField& vsf,
	const word& name
) const
{
	const fvMesh& mesh = vsf.mesh();

	tmp<volVectorField> tGrad = basicGradScheme_().calcGrad(vsf, name);

	if (k_ < small)
	{
		return tGrad;
	}

	volVectorField& g = tGrad.ref();

	const labelUList& owner = mesh.owner();
	const labelUList& neighbour = mesh.neighbour();

	const volVectorField& C = mesh.C();
	const surfaceVectorField& Cf = mesh.Cf();

	scalarField maxVsf(vsf.primitiveField());
	scalarField minVsf(vsf.primitiveField());

	forAll(owner, facei)
	{
		label own = owner[facei];
		label nei = neighbour[facei];

		scalar vsfOwn = vsf[own];
		scalar vsfNei = vsf[nei];

		maxVsf[own] = max(maxVsf[own], vsfNei);
		minVsf[own] = min(minVsf[own], vsfNei);

		maxVsf[nei] = max(maxVsf[nei], vsfOwn);
		minVsf[nei] = min(minVsf[nei], vsfOwn);
	}


	const volScalarField::Boundary& bsf = vsf.boundaryField();

	forAll(bsf, patchi)
	{
		const fvPatchScalarField& psf = bsf[patchi];

		const labelUList& pOwner = mesh.boundary()[patchi].faceCells();

		if (psf.coupled())
		{
			const scalarField psfNei(psf.patchNeighbourField());

			forAll(pOwner, pFacei)
			{
				label own = pOwner[pFacei];
				scalar vsfNei = psfNei[pFacei];

				maxVsf[own] = max(maxVsf[own], vsfNei);
				minVsf[own] = min(minVsf[own], vsfNei);
			}
		}
		else
		{
			forAll(pOwner, pFacei)
			{
				label own = pOwner[pFacei];
				scalar vsfNei = psf[pFacei];

				maxVsf[own] = max(maxVsf[own], vsfNei);
				minVsf[own] = min(minVsf[own], vsfNei);
			}
		}
	}

	maxVsf -= vsf;
	minVsf -= vsf;

	if (k_ < 1.0)
	{
		const scalarField maxMinVsf((1.0 / k_ - 1.0)*(maxVsf - minVsf));
		maxVsf += maxMinVsf;
		minVsf -= maxMinVsf;

		// maxVsf *= 1.0/k_;
		// minVsf *= 1.0/k_;
	}


	forAll(owner, facei)
	{
		label own = owner[facei];
		label nei = neighbour[facei];

		// owner side
		limitFace
		(
			g[own],
			maxVsf[own],
			minVsf[own],
			Cf[facei] - C[own]
		);

		// neighbour side
		limitFace
		(
			g[nei],
			maxVsf[nei],
			minVsf[nei],
			Cf[facei] - C[nei]
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
				g[own],
				maxVsf[own],
				minVsf[own],
				pCf[pFacei] - C[own]
			);
		}
	}

	g.correctBoundaryConditions();
	gaussGrad<scalar>::correctBoundaryConditions(vsf, g);

	return tGrad;
}


template<>
tnbLib::tmp<tnbLib::volTensorField>
tnbLib::fv::cellMDLimitedGrad<tnbLib::vector>::calcGrad
(
	const volVectorField& vsf,
	const word& name
) const
{
	const fvMesh& mesh = vsf.mesh();

	tmp<volTensorField> tGrad = basicGradScheme_().calcGrad(vsf, name);

	if (k_ < small)
	{
		return tGrad;
	}

	volTensorField& g = tGrad.ref();

	const labelUList& owner = mesh.owner();
	const labelUList& neighbour = mesh.neighbour();

	const volVectorField& C = mesh.C();
	const surfaceVectorField& Cf = mesh.Cf();

	vectorField maxVsf(vsf.primitiveField());
	vectorField minVsf(vsf.primitiveField());

	forAll(owner, facei)
	{
		label own = owner[facei];
		label nei = neighbour[facei];

		const vector& vsfOwn = vsf[own];
		const vector& vsfNei = vsf[nei];

		maxVsf[own] = max(maxVsf[own], vsfNei);
		minVsf[own] = min(minVsf[own], vsfNei);

		maxVsf[nei] = max(maxVsf[nei], vsfOwn);
		minVsf[nei] = min(minVsf[nei], vsfOwn);
	}


	const volVectorField::Boundary& bsf = vsf.boundaryField();

	forAll(bsf, patchi)
	{
		const fvPatchVectorField& psf = bsf[patchi];
		const labelUList& pOwner = mesh.boundary()[patchi].faceCells();

		if (psf.coupled())
		{
			const vectorField psfNei(psf.patchNeighbourField());

			forAll(pOwner, pFacei)
			{
				label own = pOwner[pFacei];
				const vector& vsfNei = psfNei[pFacei];

				maxVsf[own] = max(maxVsf[own], vsfNei);
				minVsf[own] = min(minVsf[own], vsfNei);
			}
		}
		else
		{
			forAll(pOwner, pFacei)
			{
				label own = pOwner[pFacei];
				const vector& vsfNei = psf[pFacei];

				maxVsf[own] = max(maxVsf[own], vsfNei);
				minVsf[own] = min(minVsf[own], vsfNei);
			}
		}
	}

	maxVsf -= vsf;
	minVsf -= vsf;

	if (k_ < 1.0)
	{
		const vectorField maxMinVsf((1.0 / k_ - 1.0)*(maxVsf - minVsf));
		maxVsf += maxMinVsf;
		minVsf -= maxMinVsf;

		// maxVsf *= 1.0/k_;
		// minVsf *= 1.0/k_;
	}


	forAll(owner, facei)
	{
		label own = owner[facei];
		label nei = neighbour[facei];

		// owner side
		limitFace
		(
			g[own],
			maxVsf[own],
			minVsf[own],
			Cf[facei] - C[own]
		);

		// neighbour side
		limitFace
		(
			g[nei],
			maxVsf[nei],
			minVsf[nei],
			Cf[facei] - C[nei]
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
				g[own],
				maxVsf[own],
				minVsf[own],
				pCf[pFacei] - C[own]
			);
		}
	}

	g.correctBoundaryConditions();
	gaussGrad<vector>::correctBoundaryConditions(vsf, g);

	return tGrad;
}


// ************************************************************************* //