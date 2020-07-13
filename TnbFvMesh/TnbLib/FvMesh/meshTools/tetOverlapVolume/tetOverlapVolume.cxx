#include <tetOverlapVolume.hxx>

#include <polyMesh.hxx>
#include <OFstream.hxx>
#include <treeBoundBox.hxx>
#include <indexedOctree.hxx>
#include <treeDataCell.hxx>
#include <cut.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(tetOverlapVolume, 0);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::tetOverlapVolume::tetOverlapVolume()
{}


// * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * * //

tnbLib::scalar tnbLib::tetOverlapVolume::tetTetOverlapVol
(
	const tetPointRef& tetA,
	const tetPointRef& tetB
) const
{
	// A maximum of three cuts are made (the tets that result from the final cut
	// are not stored), and each cut can create at most three tets. The
	// temporary storage must therefore extend to 3^3 = 27 tets.
	typedef cutTetList<27> tetListType;
	static tetListType cutTetList1, cutTetList2;

	// face 0
	const plane pl0(tetB.b(), tetB.d(), tetB.c());
	const FixedList<point, 4> t({ tetA.a(), tetA.b(), tetA.c(), tetA.d() });
	cutTetList1.clear();
	tetCut(t, pl0, cut::appendOp<tetListType>(cutTetList1), cut::noOp());
	if (cutTetList1.size() == 0)
	{
		return 0;
	}

	// face 1
	const plane pl1(tetB.a(), tetB.c(), tetB.d());
	cutTetList2.clear();
	for (label i = 0; i < cutTetList1.size(); i++)
	{
		const FixedList<point, 4>& t = cutTetList1[i];
		tetCut(t, pl1, cut::appendOp<tetListType>(cutTetList2), cut::noOp());
	}
	if (cutTetList2.size() == 0)
	{
		return 0;
	}

	// face 2
	const plane pl2(tetB.a(), tetB.d(), tetB.b());
	cutTetList1.clear();
	for (label i = 0; i < cutTetList2.size(); i++)
	{
		const FixedList<point, 4>& t = cutTetList2[i];
		tetCut(t, pl2, cut::appendOp<tetListType>(cutTetList1), cut::noOp());
	}
	if (cutTetList1.size() == 0)
	{
		return 0;
	}

	// face 3
	const plane pl3(tetB.a(), tetB.b(), tetB.c());
	scalar v = 0;
	for (label i = 0; i < cutTetList1.size(); i++)
	{
		const FixedList<point, 4>& t = cutTetList1[i];
		v += tetCut(t, pl3, cut::volumeOp(), cut::noOp());
	}

	return v;
}


tnbLib::treeBoundBox tnbLib::tetOverlapVolume::pyrBb
(
	const pointField& points,
	const face& f,
	const point& fc
) const
{
	treeBoundBox bb(fc, fc);
	forAll(f, fp)
	{
		const point& pt = points[f[fp]];
		bb.min() = min(bb.min(), pt);
		bb.max() = max(bb.max(), pt);
	}
	return bb;
}


// * * * * * * * * * * * Public Member Functions  * * * * * * * * * * * * * //

bool tnbLib::tetOverlapVolume::cellCellOverlapMinDecomp
(
	const primitiveMesh& meshA,
	const label cellAI,
	const primitiveMesh& meshB,
	const label cellBI,
	const treeBoundBox& cellBbB,
	const scalar threshold
) const
{
	const cell& cFacesA = meshA.cells()[cellAI];
	const point& ccA = meshA.cellCentres()[cellAI];

	const cell& cFacesB = meshB.cells()[cellBI];
	const point& ccB = meshB.cellCentres()[cellBI];

	scalar vol = 0.0;

	forAll(cFacesA, cFA)
	{
		label faceAI = cFacesA[cFA];

		const face& fA = meshA.faces()[faceAI];
		const treeBoundBox pyrA = pyrBb(meshA.points(), fA, ccA);
		if (!pyrA.overlaps(cellBbB))
		{
			continue;
		}

		bool ownA = (meshA.faceOwner()[faceAI] == cellAI);

		label tetBasePtAI = 0;

		const point& tetBasePtA = meshA.points()[fA[tetBasePtAI]];

		for (label tetPtI = 1; tetPtI < fA.size() - 1; tetPtI++)
		{
			label facePtAI = (tetPtI + tetBasePtAI) % fA.size();
			label otherFacePtAI = fA.fcIndex(facePtAI);

			label pt0I = -1;
			label pt1I = -1;

			if (ownA)
			{
				pt0I = fA[facePtAI];
				pt1I = fA[otherFacePtAI];
			}
			else
			{
				pt0I = fA[otherFacePtAI];
				pt1I = fA[facePtAI];
			}

			const tetPointRef tetA
			(
				ccA,
				tetBasePtA,
				meshA.points()[pt0I],
				meshA.points()[pt1I]
			);
			const treeBoundBox tetABb(tetA.bounds());


			// Loop over tets of cellB
			forAll(cFacesB, cFB)
			{
				label faceBI = cFacesB[cFB];

				const face& fB = meshB.faces()[faceBI];
				const treeBoundBox pyrB = pyrBb(meshB.points(), fB, ccB);
				if (!pyrB.overlaps(pyrA))
				{
					continue;
				}

				bool ownB = (meshB.faceOwner()[faceBI] == cellBI);

				label tetBasePtBI = 0;

				const point& tetBasePtB = meshB.points()[fB[tetBasePtBI]];

				for (label tetPtI = 1; tetPtI < fB.size() - 1; tetPtI++)
				{
					label facePtBI = (tetPtI + tetBasePtBI) % fB.size();
					label otherFacePtBI = fB.fcIndex(facePtBI);

					label pt0I = -1;
					label pt1I = -1;

					if (ownB)
					{
						pt0I = fB[facePtBI];
						pt1I = fB[otherFacePtBI];
					}
					else
					{
						pt0I = fB[otherFacePtBI];
						pt1I = fB[facePtBI];
					}

					const tetPointRef tetB
					(
						ccB,
						tetBasePtB,
						meshB.points()[pt0I],
						meshB.points()[pt1I]
					);

					if (!tetB.bounds().overlaps(tetABb))
					{
						continue;
					}

					vol += tetTetOverlapVol(tetA, tetB);

					if (vol > threshold)
					{
						return true;
					}
				}
			}
		}
	}

	return false;
}


tnbLib::scalar tnbLib::tetOverlapVolume::cellCellOverlapVolumeMinDecomp
(
	const primitiveMesh& meshA,
	const label cellAI,
	const primitiveMesh& meshB,
	const label cellBI,
	const treeBoundBox& cellBbB
) const
{
	const cell& cFacesA = meshA.cells()[cellAI];
	const point& ccA = meshA.cellCentres()[cellAI];

	const cell& cFacesB = meshB.cells()[cellBI];
	const point& ccB = meshB.cellCentres()[cellBI];

	scalar vol = 0.0;

	forAll(cFacesA, cFA)
	{
		label faceAI = cFacesA[cFA];

		const face& fA = meshA.faces()[faceAI];
		const treeBoundBox pyrA = pyrBb(meshA.points(), fA, ccA);
		if (!pyrA.overlaps(cellBbB))
		{
			continue;
		}

		bool ownA = (meshA.faceOwner()[faceAI] == cellAI);

		label tetBasePtAI = 0;

		const point& tetBasePtA = meshA.points()[fA[tetBasePtAI]];

		for (label tetPtI = 1; tetPtI < fA.size() - 1; tetPtI++)
		{
			label facePtAI = (tetPtI + tetBasePtAI) % fA.size();
			label otherFacePtAI = fA.fcIndex(facePtAI);

			label pt0I = -1;
			label pt1I = -1;

			if (ownA)
			{
				pt0I = fA[facePtAI];
				pt1I = fA[otherFacePtAI];
			}
			else
			{
				pt0I = fA[otherFacePtAI];
				pt1I = fA[facePtAI];
			}

			const tetPointRef tetA
			(
				ccA,
				tetBasePtA,
				meshA.points()[pt0I],
				meshA.points()[pt1I]
			);
			const treeBoundBox tetABb(tetA.bounds());


			// Loop over tets of cellB
			forAll(cFacesB, cFB)
			{
				label faceBI = cFacesB[cFB];

				const face& fB = meshB.faces()[faceBI];
				const treeBoundBox pyrB = pyrBb(meshB.points(), fB, ccB);
				if (!pyrB.overlaps(pyrA))
				{
					continue;
				}

				bool ownB = (meshB.faceOwner()[faceBI] == cellBI);

				label tetBasePtBI = 0;

				const point& tetBasePtB = meshB.points()[fB[tetBasePtBI]];

				for (label tetPtI = 1; tetPtI < fB.size() - 1; tetPtI++)
				{
					label facePtBI = (tetPtI + tetBasePtBI) % fB.size();
					label otherFacePtBI = fB.fcIndex(facePtBI);

					label pt0I = -1;
					label pt1I = -1;

					if (ownB)
					{
						pt0I = fB[facePtBI];
						pt1I = fB[otherFacePtBI];
					}
					else
					{
						pt0I = fB[otherFacePtBI];
						pt1I = fB[facePtBI];
					}

					const tetPointRef tetB
					(
						ccB,
						tetBasePtB,
						meshB.points()[pt0I],
						meshB.points()[pt1I]
					);
					if (!tetB.bounds().overlaps(tetABb))
					{
						continue;
					}

					vol += tetTetOverlapVol(tetA, tetB);
				}
			}
		}
	}

	return vol;
}


tnbLib::labelList tnbLib::tetOverlapVolume::overlappingCells
(
	const polyMesh& fromMesh,
	const polyMesh& toMesh,
	const label iTo
) const
{
	const indexedOctree<treeDataCell>& treeA = fromMesh.cellTree();

	treeBoundBox bbB(toMesh.points(), toMesh.cellPoints()[iTo]);

	return treeA.findBox(bbB);
}


// ************************************************************************* //