#include <inverseFaceDistanceDiffusivity.hxx>

#include <surfaceFields.hxx>
#include <HashSet.hxx>
#include <wallPoint.hxx>
#include <MeshWave.hxx>
#include <addToRunTimeSelectionTable.hxx>

#include <Time.hxx>  // added by amir
#include <globalMeshData.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(inverseFaceDistanceDiffusivity, 0);

	addToRunTimeSelectionTable
	(
		motionDiffusivity,
		inverseFaceDistanceDiffusivity,
		Istream
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::inverseFaceDistanceDiffusivity::inverseFaceDistanceDiffusivity
(
	const fvMesh& mesh,
	Istream& mdData
)
	:
	motionDiffusivity(mesh),
	patchNames_(mdData)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::inverseFaceDistanceDiffusivity::~inverseFaceDistanceDiffusivity()
{}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::surfaceScalarField>
tnbLib::inverseFaceDistanceDiffusivity::operator()() const
{
	tmp<surfaceScalarField> tfaceDiffusivity
	(
		new surfaceScalarField
		(
			IOobject
			(
				"faceDiffusivity",
				mesh().time().timeName(),
				mesh(),
				IOobject::NO_READ,
				IOobject::NO_WRITE
			),
			mesh(),
			dimensionedScalar(dimless, 1.0)
		)
	);

	surfaceScalarField& faceDiffusivity = tfaceDiffusivity.ref();

	const polyBoundaryMesh& bdry = mesh().boundaryMesh();

	labelHashSet patchSet(bdry.size());

	label nPatchFaces = 0;

	forAll(patchNames_, i)
	{
		const label pID = bdry.findPatchID(patchNames_[i]);

		if (pID > -1)
		{
			patchSet.insert(pID);
			nPatchFaces += bdry[pID].size();
		}
	}

	List<wallPoint> faceDist(nPatchFaces);
	labelList changedFaces(nPatchFaces);

	nPatchFaces = 0;

	forAllConstIter(labelHashSet, patchSet, iter)
	{
		const polyPatch& patch = bdry[iter.key()];

		const vectorField::subField fc(patch.faceCentres());

		forAll(fc, patchFacei)
		{
			changedFaces[nPatchFaces] = patch.start() + patchFacei;

			faceDist[nPatchFaces] = wallPoint(fc[patchFacei], 0);

			nPatchFaces++;
		}
	}
	faceDist.setSize(nPatchFaces);
	changedFaces.setSize(nPatchFaces);

	MeshWave<wallPoint> waveInfo
	(
		mesh(),
		changedFaces,
		faceDist,
		mesh().globalData().nTotalCells() + 1   // max iterations
	);

	const List<wallPoint>& faceInfo = waveInfo.allFaceInfo();
	const List<wallPoint>& cellInfo = waveInfo.allCellInfo();

	for (label facei = 0; facei < mesh().nInternalFaces(); facei++)
	{
		const scalar dist = faceInfo[facei].distSqr();

		faceDiffusivity[facei] = 1.0 / sqrt(dist);
	}

	surfaceScalarField::Boundary& faceDiffusivityBf =
		faceDiffusivity.boundaryFieldRef();

	forAll(faceDiffusivityBf, patchi)
	{
		fvsPatchScalarField& bfld = faceDiffusivityBf[patchi];

		const labelUList& faceCells = bfld.patch().faceCells();

		if (patchSet.found(patchi))
		{
			forAll(bfld, i)
			{
				const scalar dist = cellInfo[faceCells[i]].distSqr();
				bfld[i] = 1.0 / sqrt(dist);
			}
		}
		else
		{
			const label start = bfld.patch().start();

			forAll(bfld, i)
			{
				const scalar dist = faceInfo[start + i].distSqr();
				bfld[i] = 1.0 / sqrt(dist);
			}
		}
	}

	return tfaceDiffusivity;
}


// ************************************************************************* //