#include <patchProbes.hxx>

#include <volFields.hxx>
#include <IOmanip.hxx>
#include <mappedPatchBase.hxx>
#include <treeBoundBox.hxx>
#include <treeDataFace.hxx>
#include <addToRunTimeSelectionTable.hxx>

#include <emptyPolyPatch.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(patchProbes, 0);

	addToRunTimeSelectionTable
	(
		functionObject,
		patchProbes,
		dictionary
	);
}

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::patchProbes::findElements(const fvMesh& mesh)
{
	(void)mesh.tetBasePtIs();

	const polyBoundaryMesh& bm = mesh.boundaryMesh();

	label patchi = bm.findPatchID(patchName_);

	if (patchi == -1)
	{
		FatalErrorInFunction
			<< " Unknown patch name "
			<< patchName_ << endl
			<< exit(FatalError);
	}

	// All the info for nearest. Construct to miss
	List<mappedPatchBase::nearInfo> nearest(this->size());

	const polyPatch& pp = bm[patchi];

	if (pp.size() > 0)
	{
		labelList bndFaces(pp.size());
		forAll(bndFaces, i)
		{
			bndFaces[i] = pp.start() + i;
		}

		treeBoundBox overallBb(pp.points());
		overallBb = overallBb.extend(1e-4);

		const indexedOctree<treeDataFace> boundaryTree
		(
			treeDataFace    // all information needed to search faces
			(
				false,                      // do not cache bb
				mesh,
				bndFaces                    // patch faces only
			),
			overallBb,                      // overall search domain
			8,                              // maxLevel
			10,                             // leafsize
			3.0                             // duplicity
		);


		forAll(probeLocations(), probei)
		{
			const point sample = probeLocations()[probei];

			scalar span = boundaryTree.bb().mag();

			pointIndexHit info = boundaryTree.findNearest
			(
				sample,
				tnbLib::sqr(span)
			);

			if (!info.hit())
			{
				info = boundaryTree.findNearest
				(
					sample,
					tnbLib::sqr(great)
				);
			}

			label facei = boundaryTree.shapes().faceLabels()[info.index()];

			const label patchi = bm.whichPatch(facei);

			if (isA<emptyPolyPatch>(bm[patchi]))
			{
				WarningInFunction
					<< " The sample point: " << sample
					<< " belongs to " << patchi
					<< " which is an empty patch. This is not permitted. "
					<< " This sample will not be included "
					<< endl;
			}
			else
			{
				const point& fc = mesh.faceCentres()[facei];

				mappedPatchBase::nearInfo sampleInfo;

				sampleInfo.first() = pointIndexHit
				(
					true,
					fc,
					facei
				);

				sampleInfo.second().first() = magSqr(fc - sample);
				sampleInfo.second().second() = Pstream::myProcNo();

				nearest[probei] = sampleInfo;
			}
		}
	}


	// Find nearest.
	Pstream::listCombineGather(nearest, mappedPatchBase::nearestEqOp());
	Pstream::listCombineScatter(nearest);

	if (debug)
	{
		InfoInFunction << endl;
		forAll(nearest, sampleI)
		{
			label proci = nearest[sampleI].second().second();
			label localI = nearest[sampleI].first().index();

			Info << "    " << sampleI << " coord:" << operator[](sampleI)
				<< " found on processor:" << proci
				<< " in local cell/face:" << localI
				<< " with fc:" << nearest[sampleI].first().rawPoint() << endl;
		}
	}


	// Extract any local faces to sample
	elementList_.setSize(nearest.size(), -1);

	forAll(nearest, sampleI)
	{
		if (nearest[sampleI].second().second() == Pstream::myProcNo())
		{
			// Store the face to sample
			elementList_[sampleI] = nearest[sampleI].first().index();
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::patchProbes::patchProbes
(
	const word& name,
	const Time& t,
	const dictionary& dict
)
	:
	probes(name, t, dict)
{
	// When constructing probes above it will have called the
	// probes::findElements (since the virtual mechanism not yet operating).
	// Not easy to workaround (apart from feeding through flag into constructor)
	// so clear out any cells found for now.
	elementList_.clear();
	faceList_.clear();

	read(dict);
}


tnbLib::patchProbes::patchProbes
(
	const word& name,
	const objectRegistry& obr,
	const dictionary& dict,
	const bool loadFromFiles
)
	:
	probes(name, obr, dict)
{
	// When constructing probes above it will have called the
	// probes::findElements (since the virtual mechanism not yet operating).
	// Not easy to workaround (apart from feeding through flag into constructor)
	// so clear out any cells found for now.
	elementList_.clear();
	faceList_.clear();

	read(dict);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::patchProbes::~patchProbes()
{}


bool tnbLib::patchProbes::write()
{
	if (this->size() && prepare())
	{
		sampleAndWrite(scalarFields_);
		sampleAndWrite(vectorFields_);
		sampleAndWrite(sphericalTensorFields_);
		sampleAndWrite(symmTensorFields_);
		sampleAndWrite(tensorFields_);

		sampleAndWriteSurfaceFields(surfaceScalarFields_);
		sampleAndWriteSurfaceFields(surfaceVectorFields_);
		sampleAndWriteSurfaceFields(surfaceSphericalTensorFields_);
		sampleAndWriteSurfaceFields(surfaceSymmTensorFields_);
		sampleAndWriteSurfaceFields(surfaceTensorFields_);
	}

	return true;
}


bool tnbLib::patchProbes::read(const dictionary& dict)
{
	dict.lookup("patchName") >> patchName_;
	return probes::read(dict);
}


// ************************************************************************* //