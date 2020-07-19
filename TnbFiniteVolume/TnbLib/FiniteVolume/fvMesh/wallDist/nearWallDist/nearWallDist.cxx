#include <nearWallDist.hxx>

#include <fvMesh.hxx>
#include <cellDistFuncs.hxx>
#include <wallFvPatch.hxx>
#include <surfaceFields.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::nearWallDist::calculate()
{
	cellDistFuncs wallUtils(mesh_);

	// Get patch ids of walls
	labelHashSet wallPatchIDs(wallUtils.getPatchIDs<wallPolyPatch>());

	// Size neighbours array for maximum possible

	labelList neighbours(wallUtils.maxPatchSize(wallPatchIDs));


	// Correct all cells with face on wall

	const volVectorField& cellCentres = mesh_.C();

	forAll(mesh_.boundary(), patchi)
	{
		fvPatchScalarField& ypatch = operator[](patchi);

		const fvPatch& patch = mesh_.boundary()[patchi];

		if (isA<wallFvPatch>(patch))
		{
			const polyPatch& pPatch = patch.patch();

			const labelUList& faceCells = patch.faceCells();

			// Check cells with face on wall
			forAll(patch, patchFacei)
			{
				label nNeighbours = wallUtils.getPointNeighbours
				(
					pPatch,
					patchFacei,
					neighbours
				);

				label minFacei = -1;

				ypatch[patchFacei] = wallUtils.smallestDist
				(
					cellCentres[faceCells[patchFacei]],
					pPatch,
					nNeighbours,
					neighbours,
					minFacei
				);
			}
		}
		else
		{
			ypatch = 0.0;
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::nearWallDist::nearWallDist(const tnbLib::fvMesh& mesh)
	:
	volScalarField::Boundary
	(
		mesh.boundary(),
		mesh.V(),           // Dummy internal field,
		calculatedFvPatchScalarField::typeName
	),
	mesh_(mesh)
{
	calculate();
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::nearWallDist::~nearWallDist()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::nearWallDist::correct()
{
	if (mesh_.topoChanging())
	{
		const DimensionedField<scalar, volMesh>& V = mesh_.V();
		const fvBoundaryMesh& bnd = mesh_.boundary();

		this->setSize(bnd.size());
		forAll(*this, patchi)
		{
			this->set
			(
				patchi,
				fvPatchField<scalar>::New
				(
					calculatedFvPatchScalarField::typeName,
					bnd[patchi],
					V
				)
			);
		}
	}

	calculate();
}


// ************************************************************************* //