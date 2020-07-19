#include <CFCCellToCellStencil.hxx>

#include <syncTools.hxx>
#include <SortableList.hxx>
#include <emptyPolyPatch.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::CFCCellToCellStencil::calcFaceBoundaryData
(
	labelList& neiGlobal
) const
{
	const polyBoundaryMesh& patches = mesh().boundaryMesh();
	const label nBnd = mesh().nFaces() - mesh().nInternalFaces();
	const labelList& own = mesh().faceOwner();

	neiGlobal.setSize(nBnd);

	forAll(patches, patchi)
	{
		const polyPatch& pp = patches[patchi];
		label facei = pp.start();

		if (pp.coupled())
		{
			// For coupled faces get the cell on the other side
			forAll(pp, i)
			{
				label bFacei = facei - mesh().nInternalFaces();
				neiGlobal[bFacei] = globalNumbering().toGlobal(own[facei]);
				facei++;
			}
		}
		else if (isA<emptyPolyPatch>(pp))
		{
			forAll(pp, i)
			{
				label bFacei = facei - mesh().nInternalFaces();
				neiGlobal[bFacei] = -1;
				facei++;
			}
		}
		else
		{
			// For noncoupled faces get the boundary face.
			forAll(pp, i)
			{
				label bFacei = facei - mesh().nInternalFaces();
				neiGlobal[bFacei] =
					globalNumbering().toGlobal(mesh().nCells() + bFacei);
				facei++;
			}
		}
	}
	syncTools::swapBoundaryFaceList(mesh(), neiGlobal);
}


void tnbLib::CFCCellToCellStencil::calcCellStencil
(
	labelListList& globalCellCells
) const
{
	const label nBnd = mesh().nFaces() - mesh().nInternalFaces();
	const labelList& own = mesh().faceOwner();
	const labelList& nei = mesh().faceNeighbour();


	// Calculate coupled neighbour (in global numbering)
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	labelList neiGlobal(nBnd);
	calcFaceBoundaryData(neiGlobal);


	// Determine cellCells in global numbering
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	globalCellCells.setSize(mesh().nCells());
	forAll(globalCellCells, celli)
	{
		const cell& cFaces = mesh().cells()[celli];

		labelList& cCells = globalCellCells[celli];

		cCells.setSize(cFaces.size() + 1);

		label nNbr = 0;

		// Myself
		cCells[nNbr++] = globalNumbering().toGlobal(celli);

		// Collect neighbouring cells/faces
		forAll(cFaces, i)
		{
			label facei = cFaces[i];

			if (mesh().isInternalFace(facei))
			{
				label nbrCelli = own[facei];
				if (nbrCelli == celli)
				{
					nbrCelli = nei[facei];
				}
				cCells[nNbr++] = globalNumbering().toGlobal(nbrCelli);
			}
			else
			{
				label nbrCelli = neiGlobal[facei - mesh().nInternalFaces()];
				if (nbrCelli != -1)
				{
					cCells[nNbr++] = nbrCelli;
				}
			}
		}
		cCells.setSize(nNbr);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::CFCCellToCellStencil::CFCCellToCellStencil(const polyMesh& mesh)
	:
	cellToCellStencil(mesh)
{
	// Calculate per cell the (face) connected cells (in global numbering)
	calcCellStencil(*this);
}


// ************************************************************************* //