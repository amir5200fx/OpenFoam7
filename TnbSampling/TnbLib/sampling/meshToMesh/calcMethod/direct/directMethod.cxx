#include <directMethod.hxx>

#include <indexedOctree.hxx>
#include <treeDataCell.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(directMethod, 0);
	addToRunTimeSelectionTable(meshToMeshMethod, directMethod, components);
}

// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

bool tnbLib::directMethod::intersect
(
	const label srcCelli,
	const label tgtCelli
) const
{
	return tgt_.pointInCell
	(
		src_.cellCentres()[srcCelli],
		tgtCelli,
		polyMesh::FACE_PLANES
	);
}


bool tnbLib::directMethod::findInitialSeeds
(
	const labelList& srcCellIDs,
	const boolList& mapFlag,
	const label startSeedI,
	label& srcSeedI,
	label& tgtSeedI
) const
{
	const cellList& srcCells = src_.cells();
	const faceList& srcFaces = src_.faces();
	const pointField& srcPts = src_.points();

	for (label i = startSeedI; i < srcCellIDs.size(); i++)
	{
		label srcI = srcCellIDs[i];

		if (mapFlag[srcI])
		{
			const point srcCtr(srcCells[srcI].centre(srcPts, srcFaces));
			label tgtI = tgt_.cellTree().findInside(srcCtr);

			if (tgtI != -1 && intersect(srcI, tgtI))
			{
				srcSeedI = srcI;
				tgtSeedI = tgtI;

				return true;
			}
		}
	}

	if (debug)
	{
		Pout << "could not find starting seed" << endl;
	}

	return false;
}


void tnbLib::directMethod::calculateAddressing
(
	labelListList& srcToTgtCellAddr,
	scalarListList& srcToTgtCellWght,
	labelListList& tgtToSrcCellAddr,
	scalarListList& tgtToSrcCellWght,
	const label srcSeedI,
	const label tgtSeedI,
	const labelList& srcCellIDs, // not used
	boolList& mapFlag,
	label& startSeedI
)
{
	// store a list of src cells already mapped
	labelList srcTgtSeed(src_.nCells(), -1);

	List<DynamicList<label>> srcToTgt(src_.nCells());
	List<DynamicList<label>> tgtToSrc(tgt_.nCells());

	DynamicList<label> srcSeeds(10);

	const scalarField& srcVc = src_.cellVolumes();
	const scalarField& tgtVc = tgt_.cellVolumes();

	label srcCelli = srcSeedI;
	label tgtCelli = tgtSeedI;

	do
	{
		// store src/tgt cell pair
		srcToTgt[srcCelli].append(tgtCelli);
		tgtToSrc[tgtCelli].append(srcCelli);

		// mark source cell srcSeedI as matched
		mapFlag[srcCelli] = false;

		// accumulate intersection volume
		V_ += srcVc[srcCelli];

		// find new source seed cell
		appendToDirectSeeds
		(
			mapFlag,
			srcTgtSeed,
			srcSeeds,
			srcCelli,
			tgtCelli
		);
	} while (srcCelli >= 0);

	// transfer addressing into persistent storage
	forAll(srcToTgtCellAddr, i)
	{
		srcToTgtCellWght[i] = scalarList(srcToTgt[i].size(), srcVc[i]);
		srcToTgtCellAddr[i].transfer(srcToTgt[i]);
	}

	forAll(tgtToSrcCellAddr, i)
	{
		tgtToSrcCellWght[i] = scalarList(tgtToSrc[i].size(), tgtVc[i]);
		tgtToSrcCellAddr[i].transfer(tgtToSrc[i]);
	}
}


void tnbLib::directMethod::appendToDirectSeeds
(
	boolList& mapFlag,
	labelList& srcTgtSeed,
	DynamicList<label>& srcSeeds,
	label& srcSeedI,
	label& tgtSeedI
) const
{
	const labelList& srcNbr = src_.cellCells()[srcSeedI];
	const labelList& tgtNbr = tgt_.cellCells()[tgtSeedI];

	forAll(srcNbr, i)
	{
		label srcI = srcNbr[i];

		if (mapFlag[srcI] && (srcTgtSeed[srcI] == -1))
		{
			// source cell srcI not yet mapped

			// identfy if target cell exists for source cell srcI
			bool found = false;
			forAll(tgtNbr, j)
			{
				label tgtI = tgtNbr[j];

				if (intersect(srcI, tgtI))
				{
					// new match - append to lists
					found = true;

					srcTgtSeed[srcI] = tgtI;
					srcSeeds.append(srcI);

					break;
				}
			}

			if (!found)
			{
				// no match available for source cell srcI
				mapFlag[srcI] = false;
			}
		}
	}

	if (srcSeeds.size())
	{
		srcSeedI = srcSeeds.remove();
		tgtSeedI = srcTgtSeed[srcSeedI];
	}
	else
	{
		srcSeedI = -1;
		tgtSeedI = -1;
	}
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::directMethod::directMethod
(
	const polyMesh& src,
	const polyMesh& tgt
)
	:
	meshToMeshMethod(src, tgt)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::directMethod::~directMethod()
{}

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::directMethod::calculate
(
	labelListList& srcToTgtAddr,
	scalarListList& srcToTgtWght,
	labelListList& tgtToSrcAddr,
	scalarListList& tgtToSrcWght
)
{
	bool ok = initialise
	(
		srcToTgtAddr,
		srcToTgtWght,
		tgtToSrcAddr,
		tgtToSrcWght
	);

	if (!ok)
	{
		return;
	}

	// (potentially) participating source mesh cells
	const labelList srcCellIDs(maskCells());

	// list to keep track of whether src cell can be mapped
	boolList mapFlag(src_.nCells(), false);
	UIndirectList<bool>(mapFlag, srcCellIDs) = true;

	// find initial point in tgt mesh
	label srcSeedI = -1;
	label tgtSeedI = -1;
	label startSeedI = 0;

	bool startWalk =
		findInitialSeeds
		(
			srcCellIDs,
			mapFlag,
			startSeedI,
			srcSeedI,
			tgtSeedI
		);

	if (startWalk)
	{
		calculateAddressing
		(
			srcToTgtAddr,
			srcToTgtWght,
			tgtToSrcAddr,
			tgtToSrcWght,
			srcSeedI,
			tgtSeedI,
			srcCellIDs,
			mapFlag,
			startSeedI
		);
	}
	else
	{
		// if meshes are collocated, after inflating the source mesh bounding
		// box tgt mesh cells may be transferred, but may still not overlap
		// with the source mesh
		return;
	}
}


// ************************************************************************* //