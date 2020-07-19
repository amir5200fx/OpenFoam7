#include <CPCCellToCellStencil.hxx>

#include <syncTools.hxx>
#include <dummyTransform.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::CPCCellToCellStencil::calcPointBoundaryData
(
	const boolList& isValidBFace,
	const labelList& boundaryPoints,
	Map<labelList>& neiGlobal
) const
{
	neiGlobal.resize(2 * boundaryPoints.size());

	labelHashSet pointGlobals;

	forAll(boundaryPoints, i)
	{
		label pointi = boundaryPoints[i];

		neiGlobal.insert
		(
			pointi,
			calcFaceCells
			(
				isValidBFace,
				mesh().pointFaces()[pointi],
				pointGlobals
			)
		);
	}

	syncTools::syncPointMap
	(
		mesh(),
		neiGlobal,
		unionEqOp(),
		tnbLib::dummyTransform()      // dummy transformation
	);
}


void tnbLib::CPCCellToCellStencil::calcCellStencil
(
	labelListList& globalCellCells
) const
{
	// Calculate points on coupled patches
	labelList boundaryPoints(allCoupledFacesPatch()().meshPoints());


	// Mark boundary faces to be included in stencil (i.e. not coupled or empty)
	boolList isValidBFace;
	validBoundaryFaces(isValidBFace);


	// Swap pointCells for coupled points
	Map<labelList> neiGlobal;
	calcPointBoundaryData
	(
		isValidBFace,
		boundaryPoints,
		neiGlobal
	);

	globalCellCells.setSize(mesh().nCells());

	// Do coupled points first

	forAll(boundaryPoints, i)
	{
		label pointi = boundaryPoints[i];

		const labelList& pGlobals = neiGlobal[pointi];

		// Distribute to all pointCells
		const labelList& pCells = mesh().pointCells(pointi);

		forAll(pCells, j)
		{
			label celli = pCells[j];

			// Insert pGlobals into globalCellCells
			merge
			(
				globalNumbering().toGlobal(celli),
				pGlobals,
				globalCellCells[celli]
			);
		}
	}
	neiGlobal.clear();

	// Do remaining points cells
	labelHashSet pointGlobals;

	for (label pointi = 0; pointi < mesh().nPoints(); pointi++)
	{
		labelList pGlobals
		(
			calcFaceCells
			(
				isValidBFace,
				mesh().pointFaces()[pointi],
				pointGlobals
			)
		);

		const labelList& pCells = mesh().pointCells(pointi);

		forAll(pCells, j)
		{
			label celli = pCells[j];

			merge
			(
				globalNumbering().toGlobal(celli),
				pGlobals,
				globalCellCells[celli]
			);
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::CPCCellToCellStencil::CPCCellToCellStencil(const polyMesh& mesh)
	:
	cellToCellStencil(mesh)
{
	// Calculate per cell the (point) connected cells (in global numbering)
	labelListList globalCellCells;
	calcCellStencil(*this);
}


// ************************************************************************* //