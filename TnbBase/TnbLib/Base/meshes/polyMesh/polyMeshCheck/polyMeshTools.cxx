#include <polyMeshTools.hxx>

#include <syncTools.hxx>
#include <pyramidPointFaceRef.hxx>
#include <primitiveMeshTools.hxx>
#include <polyMeshTools.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::scalarField> tnbLib::polyMeshTools::faceOrthogonality
(
	const polyMesh& mesh,
	const vectorField& areas,
	const vectorField& cc
)
{
	const labelList& own = mesh.faceOwner();
	const labelList& nei = mesh.faceNeighbour();
	const polyBoundaryMesh& pbm = mesh.boundaryMesh();

	tmp<scalarField> tortho(new scalarField(mesh.nFaces(), 1.0));
	scalarField& ortho = tortho.ref();

	// Internal faces
	forAll(nei, facei)
	{
		ortho[facei] = primitiveMeshTools::faceOrthogonality
		(
			cc[own[facei]],
			cc[nei[facei]],
			areas[facei]
		);
	}


	// Coupled faces

	pointField neighbourCc;
	syncTools::swapBoundaryCellPositions(mesh, cc, neighbourCc);

	forAll(pbm, patchi)
	{
		const polyPatch& pp = pbm[patchi];
		if (pp.coupled())
		{
			forAll(pp, i)
			{
				label facei = pp.start() + i;
				label bFacei = facei - mesh.nInternalFaces();

				ortho[facei] = primitiveMeshTools::faceOrthogonality
				(
					cc[own[facei]],
					neighbourCc[bFacei],
					areas[facei]
				);
			}
		}
	}

	return tortho;
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::polyMeshTools::faceSkewness
(
	const polyMesh& mesh,
	const pointField& p,
	const vectorField& fCtrs,
	const vectorField& fAreas,
	const vectorField& cellCtrs
)
{
	const labelList& own = mesh.faceOwner();
	const labelList& nei = mesh.faceNeighbour();
	const polyBoundaryMesh& pbm = mesh.boundaryMesh();

	tmp<scalarField> tskew(new scalarField(mesh.nFaces()));
	scalarField& skew = tskew.ref();

	forAll(nei, facei)
	{
		skew[facei] = primitiveMeshTools::faceSkewness
		(
			mesh,
			p,
			fCtrs,
			fAreas,

			facei,
			cellCtrs[own[facei]],
			cellCtrs[nei[facei]]
		);
	}


	// Boundary faces: consider them to have only skewness error.
	// (i.e. treat as if mirror cell on other side)

	pointField neighbourCc;
	syncTools::swapBoundaryCellPositions(mesh, cellCtrs, neighbourCc);

	forAll(pbm, patchi)
	{
		const polyPatch& pp = pbm[patchi];
		if (pp.coupled())
		{
			forAll(pp, i)
			{
				label facei = pp.start() + i;
				label bFacei = facei - mesh.nInternalFaces();

				skew[facei] = primitiveMeshTools::faceSkewness
				(
					mesh,
					p,
					fCtrs,
					fAreas,

					facei,
					cellCtrs[own[facei]],
					neighbourCc[bFacei]
				);
			}
		}
		else
		{
			forAll(pp, i)
			{
				label facei = pp.start() + i;

				skew[facei] = primitiveMeshTools::boundaryFaceSkewness
				(
					mesh,
					p,
					fCtrs,
					fAreas,

					facei,
					cellCtrs[own[facei]]
				);
			}
		}
	}

	return tskew;
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::polyMeshTools::faceWeights
(
	const polyMesh& mesh,
	const vectorField& fCtrs,
	const vectorField& fAreas,
	const vectorField& cellCtrs
)
{
	const labelList& own = mesh.faceOwner();
	const labelList& nei = mesh.faceNeighbour();
	const polyBoundaryMesh& pbm = mesh.boundaryMesh();

	tmp<scalarField> tweight(new scalarField(mesh.nFaces(), 1.0));
	scalarField& weight = tweight.ref();

	// Internal faces
	forAll(nei, facei)
	{
		const point& fc = fCtrs[facei];
		const vector& fa = fAreas[facei];

		scalar dOwn = mag(fa & (fc - cellCtrs[own[facei]]));
		scalar dNei = mag(fa & (cellCtrs[nei[facei]] - fc));

		weight[facei] = min(dNei, dOwn) / (dNei + dOwn + vSmall);
	}


	// Coupled faces

	pointField neiCc;
	syncTools::swapBoundaryCellPositions(mesh, cellCtrs, neiCc);

	forAll(pbm, patchi)
	{
		const polyPatch& pp = pbm[patchi];
		if (pp.coupled())
		{
			forAll(pp, i)
			{
				label facei = pp.start() + i;
				label bFacei = facei - mesh.nInternalFaces();

				const point& fc = fCtrs[facei];
				const vector& fa = fAreas[facei];

				scalar dOwn = mag(fa & (fc - cellCtrs[own[facei]]));
				scalar dNei = mag(fa & (neiCc[bFacei] - fc));

				weight[facei] = min(dNei, dOwn) / (dNei + dOwn + vSmall);
			}
		}
	}

	return tweight;
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::polyMeshTools::volRatio
(
	const polyMesh& mesh,
	const scalarField& vol
)
{
	const labelList& own = mesh.faceOwner();
	const labelList& nei = mesh.faceNeighbour();
	const polyBoundaryMesh& pbm = mesh.boundaryMesh();

	tmp<scalarField> tratio(new scalarField(mesh.nFaces(), 1.0));
	scalarField& ratio = tratio.ref();

	// Internal faces
	forAll(nei, facei)
	{
		scalar volOwn = vol[own[facei]];
		scalar volNei = vol[nei[facei]];

		ratio[facei] = min(volOwn, volNei) / (max(volOwn, volNei) + vSmall);
	}


	// Coupled faces

	scalarField neiVol;
	syncTools::swapBoundaryCellList(mesh, vol, neiVol);

	forAll(pbm, patchi)
	{
		const polyPatch& pp = pbm[patchi];
		if (pp.coupled())
		{
			forAll(pp, i)
			{
				label facei = pp.start() + i;
				label bFacei = facei - mesh.nInternalFaces();

				scalar volOwn = vol[own[facei]];
				scalar volNei = neiVol[bFacei];

				ratio[facei] = min(volOwn, volNei) / (max(volOwn, volNei) + vSmall);
			}
		}
	}

	return tratio;
}


// ************************************************************************* //