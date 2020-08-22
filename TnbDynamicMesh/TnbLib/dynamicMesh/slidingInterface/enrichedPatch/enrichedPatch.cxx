#include <enrichedPatch.hxx>

#include <demandDrivenData.hxx>
#include <OFstream.hxx>
#include <meshTools.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(enrichedPatch, 0);
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::enrichedPatch::calcMeshPoints() const
{
	if (meshPointsPtr_)
	{
		FatalErrorInFunction
			<< "Mesh points already calculated."
			<< abort(FatalError);
	}

	meshPointsPtr_ = new labelList(pointMap().toc());
	labelList& mp = *meshPointsPtr_;

	sort(mp);
}


void tnbLib::enrichedPatch::calcLocalFaces() const
{
	if (localFacesPtr_)
	{
		FatalErrorInFunction
			<< "Local faces already calculated."
			<< abort(FatalError);
	}

	// Invert mesh points and renumber faces using it
	const labelList& mp = meshPoints();

	Map<label> mpLookup(2 * mp.size());

	forAll(mp, mpI)
	{
		mpLookup.insert(mp[mpI], mpI);
	}

	const faceList& faces = enrichedFaces();

	localFacesPtr_ = new faceList(faces.size());
	faceList& lf = *localFacesPtr_;

	forAll(faces, facei)
	{
		const face& f = faces[facei];

		face& curlf = lf[facei];

		curlf.setSize(f.size());

		forAll(f, pointi)
		{
			curlf[pointi] = mpLookup.find(f[pointi])();
		}
	}
}


void tnbLib::enrichedPatch::calcLocalPoints() const
{
	if (localPointsPtr_)
	{
		FatalErrorInFunction
			<< "Local points already calculated."
			<< abort(FatalError);
	}

	const labelList& mp = meshPoints();

	localPointsPtr_ = new pointField(mp.size());
	pointField& lp = *localPointsPtr_;

	forAll(lp, i)
	{
		lp[i] = pointMap().find(mp[i])();
	}
}


void tnbLib::enrichedPatch::clearOut()
{
	deleteDemandDrivenData(enrichedFacesPtr_);

	deleteDemandDrivenData(meshPointsPtr_);
	deleteDemandDrivenData(localFacesPtr_);
	deleteDemandDrivenData(localPointsPtr_);
	deleteDemandDrivenData(pointPointsPtr_);
	deleteDemandDrivenData(masterPointFacesPtr_);

	clearCutFaces();
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Construct from components
tnbLib::enrichedPatch::enrichedPatch
(
	const primitiveFacePatch& masterPatch,
	const primitiveFacePatch& slavePatch,
	const labelList& slavePointPointHits,
	const labelList& slavePointEdgeHits,
	const List<objectHit>& slavePointFaceHits
)
	:
	masterPatch_(masterPatch),
	slavePatch_(slavePatch),
	pointMap_
	(
		masterPatch_.meshPoints().size()
		+ slavePatch_.meshPoints().size()
	),
	pointMapComplete_(false),
	pointMergeMap_(2 * slavePatch_.meshPoints().size()),
	slavePointPointHits_(slavePointPointHits),
	slavePointEdgeHits_(slavePointEdgeHits),
	slavePointFaceHits_(slavePointFaceHits),
	enrichedFacesPtr_(nullptr),
	meshPointsPtr_(nullptr),
	localFacesPtr_(nullptr),
	localPointsPtr_(nullptr),
	pointPointsPtr_(nullptr),
	masterPointFacesPtr_(nullptr),
	cutFacesPtr_(nullptr),
	cutFaceMasterPtr_(nullptr),
	cutFaceSlavePtr_(nullptr)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::enrichedPatch::~enrichedPatch()
{
	clearOut();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::labelList& tnbLib::enrichedPatch::meshPoints() const
{
	if (!meshPointsPtr_)
	{
		calcMeshPoints();
	}

	return *meshPointsPtr_;
}


const tnbLib::faceList& tnbLib::enrichedPatch::localFaces() const
{
	if (!localFacesPtr_)
	{
		calcLocalFaces();
	}

	return *localFacesPtr_;
}


const tnbLib::pointField& tnbLib::enrichedPatch::localPoints() const
{
	if (!localPointsPtr_)
	{
		calcLocalPoints();
	}

	return *localPointsPtr_;
}


const tnbLib::labelListList& tnbLib::enrichedPatch::pointPoints() const
{
	if (!pointPointsPtr_)
	{
		calcPointPoints();
	}

	return *pointPointsPtr_;
}


bool tnbLib::enrichedPatch::checkSupport() const
{
	const faceList& faces = enrichedFaces();

	bool error = false;

	forAll(faces, facei)
	{
		const face& curFace = faces[facei];

		forAll(curFace, pointi)
		{
			if (!pointMap().found(curFace[pointi]))
			{
				WarningInFunction
					<< "Point " << pointi << " of face " << facei
					<< " global point index: " << curFace[pointi]
					<< " not supported in point map.  This is not allowed."
					<< endl;

				error = true;
			}
		}
	}

	return error;
}


void tnbLib::enrichedPatch::writeOBJ(const fileName& fName) const
{
	OFstream str(fName);

	const pointField& lp = localPoints();

	forAll(lp, pointi)
	{
		meshTools::writeOBJ(str, lp[pointi]);
	}

	const faceList& faces = localFaces();

	forAll(faces, facei)
	{
		const face& f = faces[facei];

		str << 'f';
		forAll(f, fp)
		{
			str << ' ' << f[fp] + 1;
		}
		str << nl;
	}
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //


// * * * * * * * * * * * * * * * Friend Functions  * * * * * * * * * * * * * //


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //


// ************************************************************************* //