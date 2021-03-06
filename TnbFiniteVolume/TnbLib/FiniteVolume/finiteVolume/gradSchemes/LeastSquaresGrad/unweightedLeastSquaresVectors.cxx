#include <leastSquaresVectors.hxx>

#include <volFields.hxx>
#include <surfaceFields.hxx>  // added by amir

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

	// Set up temporary storage for the dd tensor (before inversion)
	symmTensorField dd(mesh_.nCells(), Zero);

	forAll(owner, facei)
	{
		label own = owner[facei];
		label nei = neighbour[facei];

		symmTensor wdd = sqr(C[nei] - C[own]);
		dd[own] += wdd;
		dd[nei] += wdd;
	}


	/*surfaceVectorField::Boundary& blsP =
		pVectors_.boundaryField();*/

	surfaceVectorField::Boundary& blsP =
		pVectors_.boundaryFieldRef();  // modified by amir

	forAll(blsP, patchi)
	{
		const fvsPatchVectorField& patchLsP = blsP[patchi];

		const fvPatch& p = patchLsP.patch();
		const labelUList& faceCells = p.patch().faceCells();

		// Build the d-vectors
		vectorField pd(p.delta());

		forAll(pd, patchFacei)
		{
			dd[faceCells[patchFacei]] += sqr(pd[patchFacei]);
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

		pVectors_[facei] = (invDd[own] & d);
		nVectors_[facei] = -(invDd[nei] & d);
	}

	forAll(blsP, patchi)
	{
		fvsPatchVectorField& patchLsP = blsP[patchi];

		const fvPatch& p = patchLsP.patch();
		const labelUList& faceCells = p.faceCells();

		// Build the d-vectors
		vectorField pd(p.delta());

		forAll(pd, patchFacei)
		{
			patchLsP[patchFacei] =
				(invDd[faceCells[patchFacei]] & pd[patchFacei]);
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