#include <boundaryRandom.hxx>

#include <sampledSet.hxx>
#include <meshSearch.hxx>
#include <DynamicList.hxx>
#include <polyMesh.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <word.hxx>
#include <Random.hxx>
#include <SubField.hxx>
#include <barycentric2D.hxx>
#include <triPointRef.hxx>

#include <Pstream.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace sampledSets
	{
		defineTypeNameAndDebug(boundaryRandom, 0);
		addToRunTimeSelectionTable(sampledSet, boundaryRandom, word);
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::sampledSets::boundaryRandom::calcSamples
(
	DynamicList<point>& samplingPts,
	DynamicList<label>& samplingCells,
	DynamicList<label>& samplingFaces,
	DynamicList<label>& samplingSegments,
	DynamicList<scalar>& samplingCurveDist
) const
{
	// Triangulate the patches
	List<DynamicList<face>> trisDyn(patches_.size());
	List<DynamicList<label>> trisFaceiDyn(patches_.size());
	forAll(patches_, patchi)
	{
		const polyPatch& patch = mesh().boundaryMesh()[patchi];

		forAll(patch, patchFacei)
		{
			const face& f = patch[patchFacei];
			const label facei = patchFacei + patch.start();

			DynamicList<face> faceTris(f.nTriangles());
			f.triangles(patch.points(), faceTris);

			trisDyn[patchi].append(faceTris);
			trisFaceiDyn[patchi].append(labelList(f.nTriangles(), facei));
		}
	}

	List<faceList> tris(patches_.size());
	List<labelList> trisFacei(patches_.size());
	forAll(patches_, patchi)
	{
		tris[patchi].transfer(trisDyn[patchi]);
		trisFacei[patchi].transfer(trisFaceiDyn[patchi]);
	}

	// Generate the fractions which select the processor, patch and triangle
	List<scalarField> trisFraction(patches_.size());
	forAll(patches_, patchi)
	{
		const polyPatch& patch = mesh().boundaryMesh()[patchi];
		const pointField& points = patch.points();

		trisFraction[patchi] = scalarField(tris[patchi].size() + 1, 0);
		forAll(tris[patchi], patchTrii)
		{
			trisFraction[patchi][patchTrii + 1] =
				trisFraction[patchi][patchTrii]
				+ tris[patchi][patchTrii].mag(points);
		}
	}

	scalarField patchesFraction(patches_.size() + 1, 0);
	forAll(patches_, patchi)
	{
		patchesFraction[patchi + 1] =
			patchesFraction[patchi] + trisFraction[patchi].last();
	}

	scalarField procsArea(Pstream::nProcs(), 0);
	procsArea[Pstream::myProcNo()] = patchesFraction.last();
	Pstream::listCombineGather(procsArea, maxEqOp<scalar>());
	Pstream::listCombineScatter(procsArea);
	scalarField procsFraction(Pstream::nProcs() + 1, 0);
	for (label proci = 0; proci < Pstream::nProcs(); ++proci)
	{
		procsFraction[proci + 1] = procsFraction[proci] + procsArea[proci];
	}

	bool anyTris = false;
	forAll(patches_, patchi)
	{
		if (tris[patchi].size())
		{
			trisFraction[patchi] /= trisFraction[patchi].last();
			anyTris = true;
		}
	}

	if (anyTris)
	{
		patchesFraction /= patchesFraction.last();
	}

	procsFraction /= procsFraction.last();

	// Generate the samples
	Random rndGen(261782);
	const label proci = Pstream::myProcNo();
	for (label i = 0; i < nPoints_; ++i)
	{
		// Request all random numbers simultaneously on all processors so that
		// the generator state stays consistent

		const scalar rProc = rndGen.scalar01();
		const scalar rPatch = rndGen.scalar01();
		const scalar rTri = rndGen.scalar01();
		const barycentric2D r = barycentric2D01(rndGen);

		if (procsFraction[proci] < rProc && rProc <= procsFraction[proci + 1])
		{
			label patchi = 0;
			while (rPatch > patchesFraction[patchi + 1])
			{
				++patchi;
			}

			label trii = 0;
			while (rTri > trisFraction[patchi][trii + 1])
			{
				++trii;
			}

			const polyPatch& patch = mesh().boundaryMesh()[patchi];
			const pointField& points = patch.points();
			const face& tf = tris[patchi][trii];
			const triPointRef tt(points[tf[0]], points[tf[1]], points[tf[2]]);

			samplingPts.append(tt.barycentricToPoint(r));
			samplingCells.append(mesh().faceOwner()[trisFacei[patchi][trii]]);
			samplingFaces.append(trisFacei[patchi][trii]);
			samplingSegments.append(0);
			samplingCurveDist.append(scalar(i));
		}
	}
}


void tnbLib::sampledSets::boundaryRandom::genSamples()
{
	// Storage for sample points
	DynamicList<point> samplingPts;
	DynamicList<label> samplingCells;
	DynamicList<label> samplingFaces;
	DynamicList<label> samplingSegments;
	DynamicList<scalar> samplingCurveDist;

	calcSamples
	(
		samplingPts,
		samplingCells,
		samplingFaces,
		samplingSegments,
		samplingCurveDist
	);

	samplingPts.shrink();
	samplingCells.shrink();
	samplingFaces.shrink();
	samplingSegments.shrink();
	samplingCurveDist.shrink();

	setSamples
	(
		samplingPts,
		samplingCells,
		samplingFaces,
		samplingSegments,
		samplingCurveDist
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::sampledSets::boundaryRandom::boundaryRandom
(
	const word& name,
	const polyMesh& mesh,
	const meshSearch& searchEngine,
	const dictionary& dict
)
	:
	sampledSet(name, mesh, searchEngine, dict),
	patches_
	(
		mesh.boundaryMesh().patchSet
		(
			wordReList(dict.lookup("patches"))
		)
	),
	nPoints_(readLabel(dict.lookup("nPoints")))
{
	genSamples();

	if (debug)
	{
		write(Info);
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::sampledSets::boundaryRandom::~boundaryRandom()
{}


// ************************************************************************* //