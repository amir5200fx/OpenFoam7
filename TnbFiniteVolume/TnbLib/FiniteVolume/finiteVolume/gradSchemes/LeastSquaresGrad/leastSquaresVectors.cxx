#include <leastSquaresVectors.hxx>

#include <volFields.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(leastSquaresVectors, 0);
}


// * * * * * * * * * * * * * * * * Constructors * * * * * * * * * * * * * * //

tnbLib::leastSquaresVectors::leastSquaresVectors(const fvMesh& mesh)
	:
	MeshObject<fvMesh, tnbLib::MoveableMeshObject, leastSquaresVectors>(mesh),
	pVectors_
	(
		IOobject
		(
			"LeastSquaresP",
			mesh_.pointsInstance(),
			mesh_,
			IOobject::NO_READ,
			IOobject::NO_WRITE,
			false
		),
		mesh_,
		dimensionedVector(dimless / dimLength, Zero)
	),
	nVectors_
	(
		IOobject
		(
			"LeastSquaresN",
			mesh_.pointsInstance(),
			mesh_,
			IOobject::NO_READ,
			IOobject::NO_WRITE,
			false
		),
		mesh_,
		dimensionedVector(dimless / dimLength, Zero)
	)
{
	calcLeastSquaresVectors();
}


// * * * * * * * * * * * * * * * * Destructor * * * * * * * * * * * * * * * //

tnbLib::leastSquaresVectors::~leastSquaresVectors()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::leastSquaresVectors::calcLeastSquaresVectors()
{
	if (debug)
	{
		InfoInFunction << "Calculating least square gradient vectors" << endl;
	}

	const fvMesh& mesh = mesh_;

	// Set local references to mesh data
	const labelUList& owner = mesh_.owner();
	const labelUList& neighbour = mesh_.neighbour();

	const volVectorField& C = mesh.C();
	const surfaceScalarField& w = mesh.weights();
	const surfaceScalarField& magSf = mesh.magSf();


	// Set up temporary storage for the dd tensor (before inversion)
	symmTensorField dd(mesh_.nCells(), Zero);

	forAll(owner, facei)
	{
		label own = owner[facei];
		label nei = neighbour[facei];

		vector d = C[nei] - C[own];
		symmTensor wdd = (magSf[facei] / magSqr(d))*sqr(d);

		dd[own] += (1 - w[facei])*wdd;
		dd[nei] += w[facei] * wdd;
	}


	surfaceVectorField::Boundary& pVectorsBf =
		pVectors_.boundaryFieldRef();

	forAll(pVectorsBf, patchi)
	{
		const fvsPatchScalarField& pw = w.boundaryField()[patchi];
		const fvsPatchScalarField& pMagSf = magSf.boundaryField()[patchi];

		const fvPatch& p = pw.patch();
		const labelUList& faceCells = p.patch().faceCells();

		// Build the d-vectors
		vectorField pd(p.delta());

		if (pw.coupled())
		{
			forAll(pd, patchFacei)
			{
				const vector& d = pd[patchFacei];

				dd[faceCells[patchFacei]] +=
					((1 - pw[patchFacei])*pMagSf[patchFacei] / magSqr(d))*sqr(d);
			}
		}
		else
		{
			forAll(pd, patchFacei)
			{
				const vector& d = pd[patchFacei];

				dd[faceCells[patchFacei]] +=
					(pMagSf[patchFacei] / magSqr(d))*sqr(d);
			}
		}
	}


	// Invert the dd tensor
	const symmTensorField invDd(inv(dd));


	// Revisit all faces and calculate the pVectors_ and nVectors_ vectors
	forAll(owner, facei)
	{
		label own = owner[facei];
		label nei = neighbour[facei];

		vector d = C[nei] - C[own];
		scalar magSfByMagSqrd = magSf[facei] / magSqr(d);

		pVectors_[facei] = (1 - w[facei])*magSfByMagSqrd*(invDd[own] & d);
		nVectors_[facei] = -w[facei] * magSfByMagSqrd*(invDd[nei] & d);
	}

	forAll(pVectorsBf, patchi)
	{
		fvsPatchVectorField& patchLsP = pVectorsBf[patchi];

		const fvsPatchScalarField& pw = w.boundaryField()[patchi];
		const fvsPatchScalarField& pMagSf = magSf.boundaryField()[patchi];

		const fvPatch& p = pw.patch();
		const labelUList& faceCells = p.faceCells();

		// Build the d-vectors
		vectorField pd(p.delta());

		if (pw.coupled())
		{
			forAll(pd, patchFacei)
			{
				const vector& d = pd[patchFacei];

				patchLsP[patchFacei] =
					((1 - pw[patchFacei])*pMagSf[patchFacei] / magSqr(d))
					*(invDd[faceCells[patchFacei]] & d);
			}
		}
		else
		{
			forAll(pd, patchFacei)
			{
				const vector& d = pd[patchFacei];

				patchLsP[patchFacei] =
					pMagSf[patchFacei] * (1.0 / magSqr(d))
					*(invDd[faceCells[patchFacei]] & d);
			}
		}
	}

	if (debug)
	{
		InfoInFunction
			<< "Finished calculating least square gradient vectors" << endl;
	}
}


bool tnbLib::leastSquaresVectors::movePoints()
{
	calcLeastSquaresVectors();
	return true;
}


// ************************************************************************* //