#include <regionToFace.hxx>

#include <polyMesh.hxx>
#include <faceSet.hxx>
#include <mappedPatchBase.hxx>
#include <indirectPrimitivePatch.hxx>
#include <PatchTools.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <PatchEdgeFaceWave.hxx>
#include <patchEdgeFaceRegion.hxx>

#include <PstreamCombineReduceOps.hxx>  // added by amir
#include <PstreamReduceOps.hxx> // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(regionToFace, 0);
	addToRunTimeSelectionTable(topoSetSource, regionToFace, word);
	addToRunTimeSelectionTable(topoSetSource, regionToFace, istream);
}


tnbLib::topoSetSource::addToUsageTable tnbLib::regionToFace::usage_
(
	regionToFace::typeName,
	"\n    Usage: regionToFace <faceSet> (x y z)\n\n"
	"    Select all faces in the connected region of the faceSet"
	" starting from the point.\n"
);


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::regionToFace::markZone
(
	const indirectPrimitivePatch& patch,
	const label proci,
	const label facei,
	const label zoneI,
	labelList& faceZone
) const
{
	// Data on all edges and faces
	List<patchEdgeFaceRegion> allEdgeInfo(patch.nEdges());
	List<patchEdgeFaceRegion> allFaceInfo(patch.size());

	DynamicList<label> changedEdges;
	DynamicList<patchEdgeFaceRegion> changedInfo;

	if (Pstream::myProcNo() == proci)
	{
		const labelList& fEdges = patch.faceEdges()[facei];
		forAll(fEdges, i)
		{
			changedEdges.append(fEdges[i]);
			changedInfo.append(zoneI);
		}
	}

	// Walk
	PatchEdgeFaceWave
		<
		indirectPrimitivePatch,
		patchEdgeFaceRegion
		> calc
		(
			mesh_,
			patch,
			changedEdges,
			changedInfo,
			allEdgeInfo,
			allFaceInfo,
			returnReduce(patch.nEdges(), sumOp<label>())
		);

	forAll(allFaceInfo, facei)
	{
		if (allFaceInfo[facei].region() == zoneI)
		{
			faceZone[facei] = zoneI;
		}
	}
}


void tnbLib::regionToFace::combine(topoSet& set, const bool add) const
{
	Info << "    Loading subset " << setName_ << " to delimit search region."
		<< endl;
	faceSet subSet(mesh_, setName_);

	indirectPrimitivePatch patch
	(
		IndirectList<face>(mesh_.faces(), subSet.toc()),
		mesh_.points()
	);

	mappedPatchBase::nearInfo ni
	(
		pointIndexHit(false, Zero, -1),
		Tuple2<scalar, label>
		(
			sqr(great),
			Pstream::myProcNo()
			)
	);

	forAll(patch, i)
	{
		const point& fc = patch.faceCentres()[i];
		scalar d2 = magSqr(fc - nearPoint_);

		if (!ni.first().hit() || d2 < ni.second().first())
		{
			ni.second().first() = d2;
			ni.first().setHit();
			ni.first().setPoint(fc);
			ni.first().setIndex(i);
		}
	}

	// Globally reduce
	combineReduce(ni, mappedPatchBase::nearestEqOp());

	Info << "    Found nearest face at " << ni.first().rawPoint()
		<< " on processor " << ni.second().second()
		<< " face " << ni.first().index()
		<< " distance " << tnbLib::sqrt(ni.second().first()) << endl;

	labelList faceRegion(patch.size(), -1);
	markZone
	(
		patch,
		ni.second().second(),   // proci
		ni.first().index(),     // start face
		0,                      // currentZone
		faceRegion
	);

	forAll(faceRegion, facei)
	{
		if (faceRegion[facei] == 0)
		{
			addOrDelete(set, patch.addressing()[facei], add);
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::regionToFace::regionToFace
(
	const polyMesh& mesh,
	const word& setName,
	const point& nearPoint
)
	:
	topoSetSource(mesh),
	setName_(setName),
	nearPoint_(nearPoint)
{}


tnbLib::regionToFace::regionToFace
(
	const polyMesh& mesh,
	const dictionary& dict
)
	:
	topoSetSource(mesh),
	setName_(dict.lookup("set")),
	nearPoint_(dict.lookup("nearPoint"))
{}


tnbLib::regionToFace::regionToFace
(
	const polyMesh& mesh,
	Istream& is
)
	:
	topoSetSource(mesh),
	setName_(checkIs(is)),
	nearPoint_(checkIs(is))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::regionToFace::~regionToFace()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::regionToFace::applyToSet
(
	const topoSetSource::setAction action,
	topoSet& set
) const
{
	if ((action == topoSetSource::NEW) || (action == topoSetSource::ADD))
	{
		Info << "    Adding all faces of connected region of set "
			<< setName_
			<< " starting from point "
			<< nearPoint_ << " ..." << endl;

		combine(set, true);
	}
	else if (action == topoSetSource::DELETE)
	{
		Info << "    Removing all cells of connected region of set "
			<< setName_
			<< " starting from point "
			<< nearPoint_ << " ..." << endl;

		combine(set, false);
	}
}


// ************************************************************************* //