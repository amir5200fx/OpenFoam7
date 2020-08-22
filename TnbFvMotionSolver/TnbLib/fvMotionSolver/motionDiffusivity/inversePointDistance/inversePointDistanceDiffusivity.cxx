#include <inversePointDistanceDiffusivity.hxx>

#include <surfaceFields.hxx>
#include <HashSet.hxx>
#include <pointEdgePoint.hxx>
#include <PointEdgeWave.hxx>
#include <addToRunTimeSelectionTable.hxx>

#include <Time.hxx>  // added by amir
#include <globalMeshData.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(inversePointDistanceDiffusivity, 0);

	addToRunTimeSelectionTable
	(
		motionDiffusivity,
		inversePointDistanceDiffusivity,
		Istream
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::inversePointDistanceDiffusivity::inversePointDistanceDiffusivity
(
	const fvMesh& mesh,
	Istream& mdData
)
	:
	motionDiffusivity(mesh),
	patchNames_(mdData)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::inversePointDistanceDiffusivity::~inversePointDistanceDiffusivity()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::surfaceScalarField>
tnbLib::inversePointDistanceDiffusivity::operator()() const
{
	tmp<surfaceScalarField> tfaceDiffusivity
	(
		new surfaceScalarField
		(
			tnbLib::IOobject
			(
				"faceDiffusivity",
				mesh().time().timeName(),
				mesh(),
				tnbLib::IOobject::NO_READ,
				tnbLib::IOobject::NO_WRITE
			),
			mesh(),
			dimensionedScalar(dimless, 1.0)
		)
	);

	surfaceScalarField& faceDiffusivity = tfaceDiffusivity.ref();

	const polyBoundaryMesh& bdry = mesh().boundaryMesh();

	const labelHashSet patchSet(bdry.patchSet(patchNames_));

	label nPatchEdges = 0;

	forAllConstIter(labelHashSet, patchSet, iter)
	{
		nPatchEdges += bdry[iter.key()].nEdges();
	}

	// Distance to wall on points and edges.
	List<pointEdgePoint> pointWallDist(mesh().nPoints());
	List<pointEdgePoint> edgeWallDist(mesh().nEdges());

	int dummyTrackData = 0;


	{
		// Seeds
		List<pointEdgePoint> seedInfo(nPatchEdges);
		labelList seedPoints(nPatchEdges);

		nPatchEdges = 0;

		forAllConstIter(labelHashSet, patchSet, iter)
		{
			const polyPatch& patch = bdry[iter.key()];

			const labelList& meshPoints = patch.meshPoints();

			forAll(meshPoints, i)
			{
				const label pointi = meshPoints[i];

				if (!pointWallDist[pointi].valid(dummyTrackData))
				{
					// Not yet seeded
					seedInfo[nPatchEdges] = pointEdgePoint
					(
						mesh().points()[pointi],
						0.0
					);
					seedPoints[nPatchEdges] = pointi;
					pointWallDist[pointi] = seedInfo[nPatchEdges];

					nPatchEdges++;
				}
			}
		}
		seedInfo.setSize(nPatchEdges);
		seedPoints.setSize(nPatchEdges);

		// Do calculations
		PointEdgeWave<pointEdgePoint> waveInfo
		(
			mesh(),
			seedPoints,
			seedInfo,

			pointWallDist,
			edgeWallDist,
			mesh().globalData().nTotalPoints(),// max iterations
			dummyTrackData
		);
	}


	for (label facei = 0; facei < mesh().nInternalFaces(); facei++)
	{
		const face& f = mesh().faces()[facei];

		scalar dist = 0;

		forAll(f, fp)
		{
			dist += sqrt(pointWallDist[f[fp]].distSqr());
		}
		dist /= f.size();

		faceDiffusivity[facei] = 1.0 / dist;
	}


	surfaceScalarField::Boundary& faceDiffusivityBf =
		faceDiffusivity.boundaryFieldRef();

	forAll(faceDiffusivityBf, patchi)
	{
		fvsPatchScalarField& bfld = faceDiffusivityBf[patchi];

		if (patchSet.found(patchi))
		{
			const labelUList& faceCells = bfld.patch().faceCells();

			forAll(bfld, i)
			{
				const cell& ownFaces = mesh().cells()[faceCells[i]];

				labelHashSet cPoints(4 * ownFaces.size());

				scalar dist = 0;

				forAll(ownFaces, ownFacei)
				{
					const face& f = mesh().faces()[ownFaces[ownFacei]];

					forAll(f, fp)
					{
						if (cPoints.insert(f[fp]))
						{
							dist += sqrt(pointWallDist[f[fp]].distSqr());
						}
					}
				}
				dist /= cPoints.size();

				bfld[i] = 1.0 / dist;
			}
		}
		else
		{
			const label start = bfld.patch().start();

			forAll(bfld, i)
			{
				const face& f = mesh().faces()[start + i];

				scalar dist = 0;

				forAll(f, fp)
				{
					dist += sqrt(pointWallDist[f[fp]].distSqr());
				}
				dist /= f.size();

				bfld[i] = 1.0 / dist;
			}
		}
	}

	return tfaceDiffusivity;
}


// ************************************************************************* //