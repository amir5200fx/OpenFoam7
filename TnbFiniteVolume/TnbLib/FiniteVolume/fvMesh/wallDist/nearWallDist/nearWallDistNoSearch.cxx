#include <nearWallDistNoSearch.hxx>

#include <fvMesh.hxx>
#include <wallFvPatch.hxx>
#include <surfaceFields.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::nearWallDistNoSearch::doAll()
{
	const volVectorField& cellCentres = mesh_.C();
	const fvPatchList& patches = mesh_.boundary();

	forAll(patches, patchi)
	{
		fvPatchScalarField& ypatch = operator[](patchi);

		if (isA<wallFvPatch>(patches[patchi]))
		{
			const labelUList& faceCells = patches[patchi].faceCells();

			const fvPatchVectorField& patchCentres
				= cellCentres.boundaryField()[patchi];

			const fvsPatchVectorField& Apatch
				= mesh_.Sf().boundaryField()[patchi];

			const fvsPatchScalarField& magApatch
				= mesh_.magSf().boundaryField()[patchi];

			forAll(patchCentres, facei)
			{
				ypatch[facei] =
					(
						Apatch[facei] &
						(
							patchCentres[facei]
							- cellCentres[faceCells[facei]]
							)
						) / magApatch[facei];
			}
		}
		else
		{
			ypatch = 0.0;
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::nearWallDistNoSearch::nearWallDistNoSearch(const tnbLib::fvMesh& mesh)
	:
	volScalarField::Boundary
	(
		mesh.boundary(),
		mesh.V(),           // Dummy internal field
		calculatedFvPatchScalarField::typeName
	),
	mesh_(mesh)
{
	doAll();
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::nearWallDistNoSearch::~nearWallDistNoSearch()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::nearWallDistNoSearch::correct()
{
	if (mesh_.changing())
	{
		// Update size of Boundary
		forAll(mesh_.boundary(), patchi)
		{
			operator[](patchi).setSize(mesh_.boundary()[patchi].size());
		}
	}

	doAll();
}


// ************************************************************************* //