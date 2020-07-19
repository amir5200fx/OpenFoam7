#include <FECCellToFaceStencil.hxx>

#include <syncTools.hxx>
#include <emptyPolyPatch.hxx>
#include <dummyTransform.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::FECCellToFaceStencil::calcEdgeBoundaryData
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


void tnbLib::FECCellToFaceStencil::calcFaceStencil
(
	labelListList& faceStencil
) const
{
	const polyBoundaryMesh& patches = mesh().boundaryMesh();
	const label nBnd = mesh().nFaces() - mesh().nInternalFaces();
	const labelList& own = mesh().faceOwner();
	const labelList& nei = mesh().faceNeighbour();



	// Determine neighbouring global cell
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	labelList neiGlobalCell(nBnd);
	forAll(patches, patchi)
	{
		const polyPatch& pp = patches[patchi];

		if (pp.coupled())
		{
			label facei = pp.start();

			forAll(pp, i)
			{
				neiGlobalCell[facei - mesh().nInternalFaces()] =
					globalNumbering().toGlobal(own[facei]);
				facei++;
			}
		}
	}
	syncTools::swapBoundaryFaceList(mesh(), neiGlobalCell);



	// Determine on coupled edges the edge cells on the other side
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	// Calculate edges on coupled patches
	labelList boundaryEdges
	(
		allCoupledFacesPatch()().meshEdges
		(
			mesh().edges(),
			mesh().pointEdges()
		)
	);

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



	// Construct stencil in global numbering
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	faceStencil.setSize(mesh().nFaces());

	// Do coupled edges first

	forAll(boundaryEdges, i)
	{
		label edgeI = boundaryEdges[i];

		const labelList& eGlobals = neiGlobal[mesh().edges()[edgeI]];

		// Distribute to all edgeFaces
		const labelList& eFaces = mesh().edgeFaces(edgeI);

		forAll(eFaces, j)
		{
			label facei = eFaces[j];

			// Insert eGlobals into faceStencil.
			merge(-1, -1, eGlobals, faceStencil[facei]);
		}
	}
	neiGlobal.clear();


	// Do remaining edges by looping over all faces

	// Work arrays
	DynamicList<label> fEdgesSet;
	DynamicList<label> eFacesSet;
	labelHashSet faceStencilSet;

	for (label facei = 0; facei < mesh().nInternalFaces(); facei++)
	{
		label globalOwn = globalNumbering().toGlobal(own[facei]);
		label globalNei = globalNumbering().toGlobal(nei[facei]);

		// Convert any existing faceStencil (from coupled edges) into
		// set and operate on this.

		faceStencilSet.clear();

		// Insert all but global owner and neighbour
		forAll(faceStencil[facei], i)
		{
			label globalI = faceStencil[facei][i];
			if (globalI != globalOwn && globalI != globalNei)
			{
				faceStencilSet.insert(globalI);
			}
		}
		faceStencil[facei].clear();

		// Collect all edge connected (internal) cells
		const labelList& fEdges = mesh().faceEdges(facei, fEdgesSet);

		forAll(fEdges, i)
		{
			label edgeI = fEdges[i];

			insertFaceCells
			(
				globalOwn,
				globalNei,
				isValidBFace,
				mesh().edgeFaces(edgeI, eFacesSet),
				faceStencilSet
			);
		}

		// Extract, guarantee owner first, neighbour second.
		faceStencil[facei].setSize(faceStencilSet.size() + 2);
		label n = 0;
		faceStencil[facei][n++] = globalOwn;
		faceStencil[facei][n++] = globalNei;
		forAllConstIter(labelHashSet, faceStencilSet, iter)
		{
			if (iter.key() == globalOwn || iter.key() == globalNei)
			{
				FatalErrorInFunction
					<< "problem:" << faceStencilSet
					<< abort(FatalError);
			}
			faceStencil[facei][n++] = iter.key();
		}
	}
	forAll(patches, patchi)
	{
		const polyPatch& pp = patches[patchi];
		label facei = pp.start();

		if (pp.coupled())
		{
			forAll(pp, i)
			{
				label globalOwn = globalNumbering().toGlobal(own[facei]);
				label globalNei = neiGlobalCell[facei - mesh().nInternalFaces()];

				// Convert any existing faceStencil (from coupled edges) into
				// set and operate on this.

				faceStencilSet.clear();

				// Insert all but global owner and neighbour
				forAll(faceStencil[facei], i)
				{
					label globalI = faceStencil[facei][i];
					if (globalI != globalOwn && globalI != globalNei)
					{
						faceStencilSet.insert(globalI);
					}
				}
				faceStencil[facei].clear();

				// Collect all edge connected (internal) cells
				const labelList& fEdges = mesh().faceEdges(facei, fEdgesSet);

				forAll(fEdges, i)
				{
					label edgeI = fEdges[i];

					insertFaceCells
					(
						globalOwn,
						globalNei,
						isValidBFace,
						mesh().edgeFaces(edgeI, eFacesSet),
						faceStencilSet
					);
				}

				// Extract, guarantee owner first, neighbour second.
				faceStencil[facei].setSize(faceStencilSet.size() + 2);
				label n = 0;
				faceStencil[facei][n++] = globalOwn;
				faceStencil[facei][n++] = globalNei;
				forAllConstIter(labelHashSet, faceStencilSet, iter)
				{
					if (iter.key() == globalOwn || iter.key() == globalNei)
					{
						FatalErrorInFunction
							<< "problem:" << faceStencilSet
							<< abort(FatalError);
					}
					faceStencil[facei][n++] = iter.key();
				}

				if (n != faceStencil[facei].size())
				{
					FatalErrorInFunction
						<< " size:" << faceStencil[facei].size()
						<< abort(FatalError);
				}

				facei++;
			}
		}
		else if (!isA<emptyPolyPatch>(pp))
		{
			forAll(pp, i)
			{
				label globalOwn = globalNumbering().toGlobal(own[facei]);

				// Convert any existing faceStencil (from coupled edges) into
				// set and operate on this.

				faceStencilSet.clear();

				// Insert all but global owner and neighbour
				forAll(faceStencil[facei], i)
				{
					label globalI = faceStencil[facei][i];
					if (globalI != globalOwn)
					{
						faceStencilSet.insert(globalI);
					}
				}
				faceStencil[facei].clear();

				// Collect all edge connected (internal) cells
				const labelList& fEdges = mesh().faceEdges(facei, fEdgesSet);

				forAll(fEdges, i)
				{
					label edgeI = fEdges[i];

					insertFaceCells
					(
						globalOwn,
						-1,
						isValidBFace,
						mesh().edgeFaces(edgeI, eFacesSet),
						faceStencilSet
					);
				}

				// Extract, guarantee owner first, neighbour second.
				faceStencil[facei].setSize(faceStencilSet.size() + 1);
				label n = 0;
				faceStencil[facei][n++] = globalOwn;
				forAllConstIter(labelHashSet, faceStencilSet, iter)
				{
					if (iter.key() == globalOwn)
					{
						FatalErrorInFunction
							<< "problem:" << faceStencilSet
							<< abort(FatalError);
					}
					faceStencil[facei][n++] = iter.key();
				}

				facei++;
			}
		}
	}


	for (label facei = 0; facei < mesh().nInternalFaces(); facei++)
	{
		label globalOwn = globalNumbering().toGlobal(own[facei]);
		if (faceStencil[facei][0] != globalOwn)
		{
			FatalErrorInFunction
				<< "problem:" << faceStencil[facei]
				<< " globalOwn:" << globalOwn
				<< abort(FatalError);
		}
		label globalNei = globalNumbering().toGlobal(nei[facei]);
		if (faceStencil[facei][1] != globalNei)
		{
			FatalErrorInFunction
				<< "problem:" << faceStencil[facei]
				<< " globalNei:" << globalNei
				<< abort(FatalError);
		}
	}


	forAll(patches, patchi)
	{
		const polyPatch& pp = patches[patchi];

		if (pp.coupled())
		{
			forAll(pp, i)
			{
				label facei = pp.start() + i;

				label globalOwn = globalNumbering().toGlobal(own[facei]);
				if (faceStencil[facei][0] != globalOwn)
				{
					FatalErrorInFunction
						<< "problem:" << faceStencil[facei]
						<< " globalOwn:" << globalOwn
						<< abort(FatalError);
				}
				label globalNei = neiGlobalCell[facei - mesh().nInternalFaces()];
				if (faceStencil[facei][1] != globalNei)
				{
					FatalErrorInFunction
						<< "problem:" << faceStencil[facei]
						<< " globalNei:" << globalNei
						<< abort(FatalError);
				}
			}
		}
		else if (!isA<emptyPolyPatch>(pp))
		{
			forAll(pp, i)
			{
				label facei = pp.start() + i;

				label globalOwn = globalNumbering().toGlobal(own[facei]);
				if (faceStencil[facei][0] != globalOwn)
				{
					FatalErrorInFunction
						<< "problem:" << faceStencil[facei]
						<< " globalOwn:" << globalOwn
						<< abort(FatalError);
				}
			}
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::FECCellToFaceStencil::FECCellToFaceStencil(const polyMesh& mesh)
	:
	cellToFaceStencil(mesh)
{
	// Calculate per face the (edge) connected cells (in global numbering)
	labelListList faceStencil;
	calcFaceStencil(faceStencil);

	// Transfer to *this
	transfer(faceStencil);
}


// ************************************************************************* //