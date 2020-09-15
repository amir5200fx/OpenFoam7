#include <AMIMethod.hxx>

#include <AMIMethod.hxx>
#include <meshTools.hxx>
#include <mapDistribute.hxx>
#include <unitConversion.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(AMIMethod, 0);
	defineRunTimeSelectionTable(AMIMethod, components);
}


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void tnbLib::AMIMethod::checkPatches() const
{
	if (debug && (!srcPatch_.size() || !tgtPatch_.size()))
	{
		Pout << "AMI: Patches not on processor: Source faces = "
			<< srcPatch_.size() << ", target faces = " << tgtPatch_.size()
			<< endl;
	}


	if (conformal())
	{
		const scalar maxBoundsError = 0.05;

		// check bounds of source and target
		boundBox bbSrc(srcPatch_.points(), srcPatch_.meshPoints(), true);
		boundBox bbTgt(tgtPatch_.points(), tgtPatch_.meshPoints(), true);

		boundBox bbTgtInf(bbTgt);
		bbTgtInf.inflate(maxBoundsError);

		if (!bbTgtInf.contains(bbSrc))
		{
			WarningInFunction
				<< "Source and target patch bounding boxes are not similar"
				<< nl
				<< "    source box span     : " << bbSrc.span() << nl
				<< "    target box span     : " << bbTgt.span() << nl
				<< "    source box          : " << bbSrc << nl
				<< "    target box          : " << bbTgt << nl
				<< "    inflated target box : " << bbTgtInf << endl;
		}
	}
}


bool tnbLib::AMIMethod::initialise
(
	labelListList& srcAddress,
	scalarListList& srcWeights,
	labelListList& tgtAddress,
	scalarListList& tgtWeights,
	label& srcFacei,
	label& tgtFacei
)
{
	checkPatches();

	// set initial sizes for weights and addressing - must be done even if
	// returns false below
	srcAddress.setSize(srcPatch_.size());
	srcWeights.setSize(srcPatch_.size());
	tgtAddress.setSize(tgtPatch_.size());
	tgtWeights.setSize(tgtPatch_.size());

	// check that patch sizes are valid
	if (!srcPatch_.size())
	{
		return false;
	}
	else if (!tgtPatch_.size())
	{
		WarningInFunction
			<< srcPatch_.size() << " source faces but no target faces" << endl;

		return false;
	}

	// reset the octree
	resetTree();

	// find initial face match using brute force/octree search
	if ((srcFacei == -1) || (tgtFacei == -1))
	{
		srcFacei = 0;
		tgtFacei = 0;
		bool foundFace = false;
		forAll(srcPatch_, facei)
		{
			tgtFacei = findTargetFace(facei);
			if (tgtFacei >= 0)
			{
				srcFacei = facei;
				foundFace = true;
				break;
			}
		}

		if (!foundFace)
		{
			if (requireMatch_)
			{
				FatalErrorInFunction
					<< "Unable to find initial target face"
					<< abort(FatalError);
			}

			return false;
		}
	}

	if (debug)
	{
		Pout << "AMI: initial target face = " << tgtFacei << endl;
	}

	return true;
}


void tnbLib::AMIMethod::writeIntersectionOBJ
(
	const scalar area,
	const face& f1,
	const face& f2,
	const pointField& f1Points,
	const pointField& f2Points
) const
{
	static label count = 1;

	const pointField f1pts = f1.points(f1Points);
	const pointField f2pts = f2.points(f2Points);

	Pout << "Face intersection area (" << count << "):" << nl
		<< "    f1 face = " << f1 << nl
		<< "    f1 pts  = " << f1pts << nl
		<< "    f2 face = " << f2 << nl
		<< "    f2 pts  = " << f2pts << nl
		<< "    area    = " << area
		<< endl;

	OFstream os("areas" + name(count) + ".obj");

	forAll(f1pts, i)
	{
		meshTools::writeOBJ(os, f1pts[i]);
	}
	os << "l";
	forAll(f1pts, i)
	{
		os << " " << i + 1;
	}
	os << " 1" << endl;


	forAll(f2pts, i)
	{
		meshTools::writeOBJ(os, f2pts[i]);
	}
	os << "l";
	forAll(f2pts, i)
	{
		os << " " << f1pts.size() + i + 1;
	}
	os << " " << f1pts.size() + 1 << endl;

	count++;
}


void tnbLib::AMIMethod::resetTree()
{
	// Clear the old octree
	treePtr_.clear();

	treeBoundBox bb(tgtPatch_.points(), tgtPatch_.meshPoints());
	bb.inflate(0.01);

	if (!treePtr_.valid())
	{
		treePtr_.reset
		(
			new indexedOctree<treeType>
			(
				treeType
				(
					false,
					tgtPatch_,
					indexedOctree<treeType>::perturbTol()
				),
				bb,                         // overall search domain
				8,                          // maxLevel
				10,                         // leaf size
				3.0                         // duplicity
				)
		);
	}
}


tnbLib::label tnbLib::AMIMethod::findTargetFace
(
	const label srcFacei
) const
{
	label targetFacei = -1;

	const pointField& srcPts = srcPatch_.points();
	const face& srcFace = srcPatch_[srcFacei];
	const point srcPt = srcFace.centre(srcPts);
	const scalar srcFaceArea = srcMagSf_[srcFacei];

	pointIndexHit sample = treePtr_->findNearest(srcPt, 10.0*srcFaceArea);

	if (sample.hit())
	{
		targetFacei = sample.index();

		if (debug)
		{
			Pout << "Source point = " << srcPt << ", Sample point = "
				<< sample.hitPoint() << ", Sample index = " << sample.index()
				<< endl;
		}
	}

	return targetFacei;
}


void tnbLib::AMIMethod::appendNbrFaces
(
	const label facei,
	const primitivePatch& patch,
	const DynamicList<label>& visitedFaces,
	DynamicList<label>& faceIDs
) const
{
	const labelList& nbrFaces = patch.faceFaces()[facei];

	// filter out faces already visited from face neighbours
	forAll(nbrFaces, i)
	{
		label nbrFacei = nbrFaces[i];
		bool valid = true;
		forAll(visitedFaces, j)
		{
			if (nbrFacei == visitedFaces[j])
			{
				valid = false;
				break;
			}
		}

		if (valid)
		{
			forAll(faceIDs, j)
			{
				if (nbrFacei == faceIDs[j])
				{
					valid = false;
					break;
				}
			}
		}

		// prevent addition of face if it is not on the same plane-ish
		if (valid)
		{
			const vector& n1 = patch.faceNormals()[facei];
			const vector& n2 = patch.faceNormals()[nbrFacei];

			scalar cosI = n1 & n2;

			if (cosI > cos(maxWalkAngle()))
			{
				faceIDs.append(nbrFacei);
			}
		}
	}
}


tnbLib::scalar tnbLib::AMIMethod::maxWalkAngle() const
{
	return degToRad(89);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::AMIMethod::AMIMethod
(
	const primitivePatch& srcPatch,
	const primitivePatch& tgtPatch,
	const scalarField& srcMagSf,
	const scalarField& tgtMagSf,
	const faceAreaIntersect::triangulationMode& triMode,
	const bool reverseTarget,
	const bool requireMatch
)
	:
	srcPatch_(srcPatch),
	tgtPatch_(tgtPatch),
	reverseTarget_(reverseTarget),
	requireMatch_(requireMatch),
	srcMagSf_(srcMagSf),
	tgtMagSf_(tgtMagSf),
	srcNonOverlap_(),
	triMode_(triMode)
{}


// * * * * * * * * * * * * * * * * Destructor * * * * * * * * * * * * * * * //

tnbLib::AMIMethod::~AMIMethod()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::AMIMethod::conformal() const
{
	return true;
}


// ************************************************************************* //