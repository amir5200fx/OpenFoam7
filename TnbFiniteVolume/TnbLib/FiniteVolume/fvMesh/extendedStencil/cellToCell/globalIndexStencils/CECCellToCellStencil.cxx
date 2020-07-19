#include <CECCellToCellStencil.hxx>

#include <syncTools.hxx>
#include <dummyTransform.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::CECCellToCellStencil::calcEdgeBoundaryData
(
	const boolList& isValidBFace,
	const labelList& boundaryEdges,
	EdgeMap<labelList>& neiGlobal
) const
{
	neiGlobal.resize(2 * boundaryEdges.size());

	labelHashSet edgeGlobals;

	forAll(boundaryEdges, i)
	{
		label edgeI = boundaryEdges[i];

		neiGlobal.insert
		(
			mesh().edges()[edgeI],
			calcFaceCells
			(
				isValidBFace,
				mesh().edgeFaces(edgeI),
				edgeGlobals
			)
		);
	}

	syncTools::syncEdgeMap(mesh(), neiGlobal, unionEqOp(), dummyTransform());
}


void tnbLib::CECCellToCellStencil::calcCellStencil
(
	labelListList& globalCellCells
) const
{
	// Calculate edges on coupled patches
	labelList boundaryEdges
	(
		allCoupledFacesPatch()().meshEdges
		(
			mesh().edges(),
			mesh().pointEdges()
		)
	);

	//{
	//    OFstream str(mesh().time().path()/"boundaryEdges.obj");
	//    Pout<< "DUmping boundary edges to " << str.name() << endl;
	//
	//    label vertI = 0;
	//    forAll(boundaryEdges, i)
	//    {
	//        label edgeI = boundaryEdges[i];
	//        const edge& e = mesh().edges()[edgeI];
	//        const point& p0 = mesh().points()[e[0]];
	//        const point& p1 = mesh().points()[e[1]];
	//
	//        Pout<< "boundary edge " << edgeI << " between " << p0 << p1
	//            << endl;
	//
	//        meshTools::writeOBJ(str, p0);
	//        vertI++;
	//        meshTools::writeOBJ(str, p1);
	//        vertI++;
	//        str << "l " << vertI-1 << ' ' << vertI << nl;
	//    }
	//}


	// Mark boundary faces to be included in stencil (i.e. not coupled or empty)
	boolList isValidBFace;
	validBoundaryFaces(isValidBFace);


	// Swap edgeCells for coupled edges. Note: use EdgeMap for now since we've
	// got syncTools::syncEdgeMap for those. Should be replaced with Map and
	// syncTools functionality to handle those.
	EdgeMap<labelList> neiGlobal;
	calcEdgeBoundaryData
	(
		isValidBFace,
		boundaryEdges,
		neiGlobal
	);

	globalCellCells.setSize(mesh().nCells());

	// Do coupled edges first

	forAll(boundaryEdges, i)
	{
		label edgeI = boundaryEdges[i];

		const labelList& eGlobals = neiGlobal[mesh().edges()[edgeI]];

		// Distribute to all edgeCells
		const labelList& eCells = mesh().edgeCells(edgeI);

		forAll(eCells, j)
		{
			label celli = eCells[j];

			// Insert pGlobals into globalCellCells
			merge
			(
				globalNumbering().toGlobal(celli),
				eGlobals,
				globalCellCells[celli]
			);
		}
	}
	neiGlobal.clear();

	// Do remaining edges cells
	labelHashSet edgeGlobals;

	for (label edgeI = 0; edgeI < mesh().nEdges(); edgeI++)
	{
		labelList eGlobals
		(
			calcFaceCells
			(
				isValidBFace,
				mesh().edgeFaces(edgeI),
				edgeGlobals
			)
		);

		const labelList& eCells = mesh().edgeCells(edgeI);

		forAll(eCells, j)
		{
			label celli = eCells[j];

			merge
			(
				globalNumbering().toGlobal(celli),
				eGlobals,
				globalCellCells[celli]
			);
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::CECCellToCellStencil::CECCellToCellStencil(const polyMesh& mesh)
	:
	cellToCellStencil(mesh)
{
	// Calculate per cell the (edge) connected cells (in global numbering)
	calcCellStencil(*this);
}


// ************************************************************************* //