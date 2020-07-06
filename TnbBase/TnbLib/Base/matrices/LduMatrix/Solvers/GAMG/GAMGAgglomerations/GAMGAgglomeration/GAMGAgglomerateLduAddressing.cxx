#include <GAMGAgglomeration.hxx>

#include <GAMGInterface.hxx>
#include <processorGAMGInterface.hxx>

// added by amir
#include <globalIndex.hxx>
#include <IOstreams.hxx>
#include <SubList.hxx>
#include <Map.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::GAMGAgglomeration::agglomerateLduAddressing
(
	const label fineLevelIndex
)
{
	const lduMesh& fineMesh = meshLevel(fineLevelIndex);
	const lduAddressing& fineMeshAddr = fineMesh.lduAddr();

	const labelUList& upperAddr = fineMeshAddr.upperAddr();
	const labelUList& lowerAddr = fineMeshAddr.lowerAddr();

	label nFineFaces = upperAddr.size();

	// Get restriction map for current level
	const labelField& restrictMap = restrictAddressing(fineLevelIndex);

	if (min(restrictMap) == -1)
	{
		FatalErrorInFunction
			<< "min(restrictMap) == -1" << exit(FatalError);
	}

	if (restrictMap.size() != fineMeshAddr.size())
	{
		FatalErrorInFunction
			<< "restrict map does not correspond to fine level. " << endl
			<< " Sizes: restrictMap: " << restrictMap.size()
			<< " nEqns: " << fineMeshAddr.size()
			<< abort(FatalError);
	}


	// Get the number of coarse cells
	const label nCoarseCells = nCells_[fineLevelIndex];

	// Storage for coarse cell neighbours and coefficients

	// Guess initial maximum number of neighbours in coarse cell
	label maxNnbrs = 10;

	// Number of faces for each coarse-cell
	labelList cCellnFaces(nCoarseCells, 0);

	// Setup initial packed storage for coarse-cell faces
	labelList cCellFaces(maxNnbrs*nCoarseCells);

	// Create face-restriction addressing
	faceRestrictAddressing_.set(fineLevelIndex, new labelList(nFineFaces));
	labelList& faceRestrictAddr = faceRestrictAddressing_[fineLevelIndex];

	// Initial neighbour array (not in upper-triangle order)
	labelList initCoarseNeighb(nFineFaces);

	// Counter for coarse faces
	label& nCoarseFaces = nFaces_[fineLevelIndex];
	nCoarseFaces = 0;

	// Loop through all fine faces
	forAll(upperAddr, fineFacei)
	{
		label rmUpperAddr = restrictMap[upperAddr[fineFacei]];
		label rmLowerAddr = restrictMap[lowerAddr[fineFacei]];

		if (rmUpperAddr == rmLowerAddr)
		{
			// For each fine face inside of a coarse cell keep the address
			// of the cell corresponding to the face in the faceRestrictAddr
			// as a negative index
			faceRestrictAddr[fineFacei] = -(rmUpperAddr + 1);
		}
		else
		{
			// this face is a part of a coarse face

			label cOwn = rmUpperAddr;
			label cNei = rmLowerAddr;

			// get coarse owner and neighbour
			if (rmUpperAddr > rmLowerAddr)
			{
				cOwn = rmLowerAddr;
				cNei = rmUpperAddr;
			}

			// check the neighbour to see if this face has already been found
			label* ccFaces = &cCellFaces[maxNnbrs*cOwn];

			bool nbrFound = false;
			label& ccnFaces = cCellnFaces[cOwn];

			for (int i = 0; i < ccnFaces; i++)
			{
				if (initCoarseNeighb[ccFaces[i]] == cNei)
				{
					nbrFound = true;
					faceRestrictAddr[fineFacei] = ccFaces[i];
					break;
				}
			}

			if (!nbrFound)
			{
				if (ccnFaces >= maxNnbrs)
				{
					label oldMaxNnbrs = maxNnbrs;
					maxNnbrs *= 2;

					cCellFaces.setSize(maxNnbrs*nCoarseCells);

					forAllReverse(cCellnFaces, i)
					{
						label* oldCcNbrs = &cCellFaces[oldMaxNnbrs*i];
						label* newCcNbrs = &cCellFaces[maxNnbrs*i];

						for (int j = 0; j < cCellnFaces[i]; j++)
						{
							newCcNbrs[j] = oldCcNbrs[j];
						}
					}

					ccFaces = &cCellFaces[maxNnbrs*cOwn];
				}

				ccFaces[ccnFaces] = nCoarseFaces;
				initCoarseNeighb[nCoarseFaces] = cNei;
				faceRestrictAddr[fineFacei] = nCoarseFaces;
				ccnFaces++;

				// new coarse face created
				nCoarseFaces++;
			}
		}
	} // end for all fine faces


	// Renumber into upper-triangular order

	// All coarse owner-neighbour storage
	labelList coarseOwner(nCoarseFaces);
	labelList coarseNeighbour(nCoarseFaces);
	labelList coarseFaceMap(nCoarseFaces);

	label coarseFacei = 0;

	forAll(cCellnFaces, cci)
	{
		label* cFaces = &cCellFaces[maxNnbrs*cci];
		label ccnFaces = cCellnFaces[cci];

		for (int i = 0; i < ccnFaces; i++)
		{
			coarseOwner[coarseFacei] = cci;
			coarseNeighbour[coarseFacei] = initCoarseNeighb[cFaces[i]];
			coarseFaceMap[cFaces[i]] = coarseFacei;
			coarseFacei++;
		}
	}

	forAll(faceRestrictAddr, fineFacei)
	{
		if (faceRestrictAddr[fineFacei] >= 0)
		{
			faceRestrictAddr[fineFacei] =
				coarseFaceMap[faceRestrictAddr[fineFacei]];
		}
	}


	// Create face-flip status
	faceFlipMap_.set(fineLevelIndex, new boolList(nFineFaces, false));
	boolList& faceFlipMap = faceFlipMap_[fineLevelIndex];


	label nFlipped = 0;
	label nDissapear = 0;

	forAll(faceRestrictAddr, fineFacei)
	{
		label coarseFacei = faceRestrictAddr[fineFacei];

		if (coarseFacei >= 0)
		{
			// Maps to coarse face
			label cOwn = coarseOwner[coarseFacei];
			label cNei = coarseNeighbour[coarseFacei];

			label rmUpperAddr = restrictMap[upperAddr[fineFacei]];
			label rmLowerAddr = restrictMap[lowerAddr[fineFacei]];

			if (cOwn == rmUpperAddr && cNei == rmLowerAddr)
			{
				faceFlipMap[fineFacei] = true;
				nFlipped++;
			}
			else if (cOwn == rmLowerAddr && cNei == rmUpperAddr)
			{
				// faceFlipMap[fineFacei] = false;
			}
			else
			{
				FatalErrorInFunction
					<< "problem."
					<< " fineFacei:" << fineFacei
					<< " rmUpperAddr:" << rmUpperAddr
					<< " rmLowerAddr:" << rmLowerAddr
					<< " coarseFacei:" << coarseFacei
					<< " cOwn:" << cOwn
					<< " cNei:" << cNei
					<< exit(FatalError);
			}
		}
		else
		{
			nDissapear++;
		}
	}



	// Clear the temporary storage for the coarse cell data
	cCellnFaces.setSize(0);
	cCellFaces.setSize(0);
	initCoarseNeighb.setSize(0);
	coarseFaceMap.setSize(0);


	// Create coarse-level interfaces

	// Get reference to fine-level interfaces
	const lduInterfacePtrsList& fineInterfaces = interfaceLevel(fineLevelIndex);

	nPatchFaces_.set(fineLevelIndex, new labelList(fineInterfaces.size(), 0));
	labelList& nPatchFaces = nPatchFaces_[fineLevelIndex];

	patchFaceRestrictAddressing_.set
	(
		fineLevelIndex,
		new labelListList(fineInterfaces.size())
	);
	labelListList& patchFineToCoarse =
		patchFaceRestrictAddressing_[fineLevelIndex];


	// Initialise transfer of restrict addressing on the interface
	forAll(fineInterfaces, inti)
	{
		if (fineInterfaces.set(inti))
		{
			fineInterfaces[inti].initInternalFieldTransfer
			(
				Pstream::commsTypes::nonBlocking,
				restrictMap
			);
		}
	}

	if (Pstream::parRun())
	{
		Pstream::waitRequests();
	}


	// Add the coarse level
	meshLevels_.set
	(
		fineLevelIndex,
		new lduPrimitiveMesh
		(
			nCoarseCells,
			coarseOwner,
			coarseNeighbour,
			fineMesh.comm(),
			true
		)
	);

	lduInterfacePtrsList coarseInterfaces(fineInterfaces.size());

	forAll(fineInterfaces, inti)
	{
		if (fineInterfaces.set(inti))
		{
			coarseInterfaces.set
			(
				inti,
				GAMGInterface::New
				(
					inti,
					meshLevels_[fineLevelIndex].rawInterfaces(),
					fineInterfaces[inti],
					fineInterfaces[inti].interfaceInternalField(restrictMap),
					fineInterfaces[inti].internalFieldTransfer
					(
						Pstream::commsTypes::nonBlocking,
						restrictMap
					),
					fineLevelIndex,
					fineMesh.comm()
				).ptr()
			);

			nPatchFaces[inti] = coarseInterfaces[inti].faceCells().size();
			patchFineToCoarse[inti] = refCast<const GAMGInterface>
				(
					coarseInterfaces[inti]
					).faceRestrictAddressing();
		}
	}

	meshLevels_[fineLevelIndex].addInterfaces
	(
		coarseInterfaces,
		lduPrimitiveMesh::nonBlockingSchedule<processorGAMGInterface>
		(
			coarseInterfaces
			)
	);


	if (debug & 2)
	{
		Pout << "GAMGAgglomeration :"
			<< " agglomerated level " << fineLevelIndex
			<< " from nCells:" << fineMeshAddr.size()
			<< " nFaces:" << upperAddr.size()
			<< " to nCells:" << nCoarseCells
			<< " nFaces:" << nCoarseFaces
			<< endl;
	}
}


void tnbLib::GAMGAgglomeration::procAgglomerateLduAddressing
(
	const label meshComm,
	const labelList& procAgglomMap,
	const labelList& procIDs,
	const label allMeshComm,

	const label levelIndex
)
{
	const lduMesh& myMesh = meshLevels_[levelIndex - 1];


	procAgglomMap_.set(levelIndex, new labelList(procAgglomMap));
	agglomProcIDs_.set(levelIndex, new labelList(procIDs));
	procCommunicator_[levelIndex] = allMeshComm;

	// These could only be set on the master procs but it is
	// quite convenient to also have them on the slaves
	procCellOffsets_.set(levelIndex, new labelList(0));
	procFaceMap_.set(levelIndex, new labelListList(0));
	procBoundaryMap_.set(levelIndex, new labelListList(0));
	procBoundaryFaceMap_.set(levelIndex, new labelListListList(0));


	// Collect meshes
	PtrList<lduPrimitiveMesh> otherMeshes;
	lduPrimitiveMesh::gather(meshComm, myMesh, procIDs, otherMeshes);

	if (Pstream::myProcNo(meshComm) == procIDs[0])
	{
		// Combine all addressing

		labelList procFaceOffsets;
		meshLevels_.set
		(
			levelIndex - 1,
			new lduPrimitiveMesh
			(
				allMeshComm,
				procAgglomMap,

				procIDs,
				myMesh,
				otherMeshes,

				procCellOffsets_[levelIndex],
				procFaceOffsets,
				procFaceMap_[levelIndex],
				procBoundaryMap_[levelIndex],
				procBoundaryFaceMap_[levelIndex]
			)
		);
	}


	// Combine restrict addressing
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~

	procAgglomerateRestrictAddressing
	(
		meshComm,
		procIDs,
		levelIndex
	);

	if (Pstream::myProcNo(meshComm) != procIDs[0])
	{
		clearLevel(levelIndex);
	}
}


void tnbLib::GAMGAgglomeration::procAgglomerateRestrictAddressing
(
	const label comm,
	const labelList& procIDs,
	const label levelIndex
)
{
	// Collect number of cells
	labelList nFineCells;
	gatherList
	(
		comm,
		procIDs,
		restrictAddressing_[levelIndex].size(),
		nFineCells
	);

	labelList offsets(nFineCells.size() + 1);
	{
		offsets[0] = 0;
		forAll(nFineCells, i)
		{
			offsets[i + 1] = offsets[i] + nFineCells[i];
		}
	}

	// Combine and renumber nCoarseCells
	labelList nCoarseCells;
	gatherList
	(
		comm,
		procIDs,
		nCells_[levelIndex],
		nCoarseCells
	);

	// (cell)restrictAddressing
	const globalIndex cellOffsetter(offsets);

	labelList procRestrictAddressing;
	cellOffsetter.gather
	(
		comm,
		procIDs,
		restrictAddressing_[levelIndex],
		procRestrictAddressing,

		UPstream::msgType(),
		Pstream::commsTypes::nonBlocking    // Pstream::commsTypes::scheduled
	);


	if (Pstream::myProcNo(comm) == procIDs[0])
	{
		labelList coarseCellOffsets(procIDs.size() + 1);
		{
			coarseCellOffsets[0] = 0;
			forAll(procIDs, i)
			{
				coarseCellOffsets[i + 1] = coarseCellOffsets[i] + nCoarseCells[i];
			}
		}

		nCells_[levelIndex] = coarseCellOffsets.last();

		// Renumber consecutively
		for (label proci = 1; proci < procIDs.size(); proci++)
		{
			SubList<label> procSlot
			(
				procRestrictAddressing,
				offsets[proci + 1] - offsets[proci],
				offsets[proci]
			);
			forAll(procSlot, i)
			{
				procSlot[i] += coarseCellOffsets[proci];
			}
		}

		restrictAddressing_[levelIndex].transfer(procRestrictAddressing);
	}
}


void tnbLib::GAMGAgglomeration::combineLevels(const label curLevel)
{
	label prevLevel = curLevel - 1;

	// Set the previous level nCells to the current
	nCells_[prevLevel] = nCells_[curLevel];
	nFaces_[prevLevel] = nFaces_[curLevel];

	// Map the restrictAddressing from the coarser level into the previous
	// finer level

	const labelList& curResAddr = restrictAddressing_[curLevel];
	labelList& prevResAddr = restrictAddressing_[prevLevel];

	const labelList& curFaceResAddr = faceRestrictAddressing_[curLevel];
	labelList& prevFaceResAddr = faceRestrictAddressing_[prevLevel];
	const boolList& curFaceFlipMap = faceFlipMap_[curLevel];
	boolList& prevFaceFlipMap = faceFlipMap_[prevLevel];

	forAll(prevFaceResAddr, i)
	{
		if (prevFaceResAddr[i] >= 0)
		{
			label fineFacei = prevFaceResAddr[i];
			prevFaceResAddr[i] = curFaceResAddr[fineFacei];
			prevFaceFlipMap[i] = curFaceFlipMap[fineFacei];
		}
		else
		{
			label fineFacei = -prevFaceResAddr[i] - 1;
			prevFaceResAddr[i] = -curResAddr[fineFacei] - 1;
			prevFaceFlipMap[i] = curFaceFlipMap[fineFacei];
		}
	}

	// Delete the restrictAddressing for the coarser level
	faceRestrictAddressing_.set(curLevel, nullptr);
	faceFlipMap_.set(curLevel, nullptr);

	forAll(prevResAddr, i)
	{
		prevResAddr[i] = curResAddr[prevResAddr[i]];
	}

	const labelListList& curPatchFaceResAddr =
		patchFaceRestrictAddressing_[curLevel];
	labelListList& prevPatchFaceResAddr =
		patchFaceRestrictAddressing_[prevLevel];

	forAll(prevPatchFaceResAddr, inti)
	{
		const labelList& curResAddr = curPatchFaceResAddr[inti];
		labelList& prevResAddr = prevPatchFaceResAddr[inti];
		forAll(prevResAddr, i)
		{
			label fineFacei = prevResAddr[i];
			prevResAddr[i] = curResAddr[fineFacei];
		}
	}

	// Delete the restrictAddressing for the coarser level
	restrictAddressing_.set(curLevel, nullptr);

	// Patch faces
	nPatchFaces_[prevLevel] = nPatchFaces_[curLevel];



	// Adapt the restrict addressing for the patches
	const lduInterfacePtrsList& curInterLevel =
		meshLevels_[curLevel].rawInterfaces();
	const lduInterfacePtrsList& prevInterLevel =
		meshLevels_[prevLevel].rawInterfaces();

	forAll(prevInterLevel, inti)
	{
		if (prevInterLevel.set(inti))
		{
			GAMGInterface& prevInt = refCast<GAMGInterface>
				(
					const_cast<lduInterface&>
					(
						prevInterLevel[inti]
						)
					);
			const GAMGInterface& curInt = refCast<const GAMGInterface>
				(
					curInterLevel[inti]
					);
			prevInt.combine(curInt);
		}
	}

	// Delete the matrix addressing and coefficients from the previous level
	// and replace with the corresponding entry from the coarser level
	meshLevels_.set(prevLevel, meshLevels_.set(curLevel, nullptr));
}


//void tnbLib::GAMGAgglomeration::gatherList
//(
//    const label comm,
//    const labelList& procIDs,
//
//    const label myVal,
//    labelList& vals,
//    const int tag
//)
//{
//    vals.setSize(procIDs.size());
//
//    if (Pstream::myProcNo(comm) == procIDs[0])
//    {
//        vals[0] = myVal;
//
//        for (label i=1; i<procIDs.size(); i++)
//        {
//            label& slaveVal = vals[i];
//            IPstream::read
//            (
//                Pstream::commsTypes::scheduled,
//                procIDs[i],
//                reinterpret_cast<char*>(&slaveVal),
//                sizeof(slaveVal),
//                tag,
//                comm
//            );
//        }
//    }
//    else
//    {
//        OPstream::write
//        (
//            Pstream::commsTypes::scheduled,
//            procIDs[0],
//            reinterpret_cast<const char*>(&myVal),
//            sizeof(myVal),
//            tag,
//            comm
//        );
//    }
//}


void tnbLib::GAMGAgglomeration::calculateRegionMaster
(
	const label comm,
	const labelList& procAgglomMap,
	labelList& masterProcs,
	List<label>& agglomProcIDs
)
{
	// Determine the master processors
	Map<label> agglomToMaster(procAgglomMap.size());

	forAll(procAgglomMap, proci)
	{
		label coarseI = procAgglomMap[proci];

		Map<label>::iterator fnd = agglomToMaster.find(coarseI);
		if (fnd == agglomToMaster.end())
		{
			agglomToMaster.insert(coarseI, proci);
		}
		else
		{
			fnd() = min(fnd(), proci);
		}
	}

	masterProcs.setSize(agglomToMaster.size());
	forAllConstIter(Map<label>, agglomToMaster, iter)
	{
		masterProcs[iter.key()] = iter();
	}


	// Collect all the processors in my agglomeration
	label myProcID = Pstream::myProcNo(comm);
	label myAgglom = procAgglomMap[myProcID];

	// Get all processors agglomerating to the same coarse
	// processor
	agglomProcIDs = findIndices(procAgglomMap, myAgglom);
	// Make sure the master is the first element.
	label index = findIndex
	(
		agglomProcIDs,
		agglomToMaster[myAgglom]
	);
	Swap(agglomProcIDs[0], agglomProcIDs[index]);
}


// ************************************************************************* //