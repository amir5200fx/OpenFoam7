#include <singleProcessorFaceSetsConstraint.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <syncTools.hxx>
#include <faceSet.hxx>

#include <PstreamReduceOps.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace decompositionConstraints
	{
		defineTypeName(singleProcessorFaceSetsConstraint);

		addToRunTimeSelectionTable
		(
			decompositionConstraint,
			singleProcessorFaceSetsConstraint,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::decompositionConstraints::singleProcessorFaceSetsConstraint::
singleProcessorFaceSetsConstraint
(
	const dictionary& constraintsDict,
	const word& modelType
)
	:
	decompositionConstraint(constraintsDict, typeName),
	setNameAndProcs_(coeffDict_.lookup("singleProcessorFaceSets"))
{
	if (decompositionConstraint::debug)
	{
		Info << type()
			<< " : adding constraints to keep" << endl;

		forAll(setNameAndProcs_, setI)
		{
			Info << "    all cells connected to faceSet "
				<< setNameAndProcs_[setI].first()
				<< " on processor " << setNameAndProcs_[setI].second() << endl;
		}
	}
}


tnbLib::decompositionConstraints::singleProcessorFaceSetsConstraint::
singleProcessorFaceSetsConstraint
(
	const List<Tuple2<word, label>>& setNameAndProcs
)
	:
	decompositionConstraint(dictionary(), typeName),
	setNameAndProcs_(setNameAndProcs)
{
	if (decompositionConstraint::debug)
	{
		Info << type()
			<< " : adding constraints to keep" << endl;

		forAll(setNameAndProcs_, setI)
		{
			Info << "    all cells connected to faceSet "
				<< setNameAndProcs_[setI].first()
				<< " on processor " << setNameAndProcs_[setI].second() << endl;
		}
	}
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void tnbLib::decompositionConstraints::singleProcessorFaceSetsConstraint::add
(
	const polyMesh& mesh,
	boolList& blockedFace,
	PtrList<labelList>& specifiedProcessorFaces,
	labelList& specifiedProcessor,
	List<labelPair>& explicitConnections
) const
{
	blockedFace.setSize(mesh.nFaces(), true);

	// Mark faces already in set
	labelList faceToSet(mesh.nFaces(), -1);
	forAll(specifiedProcessorFaces, setI)
	{
		const labelList& faceLabels = specifiedProcessorFaces[setI];
		forAll(faceLabels, i)
		{
			faceToSet[faceLabels[i]] = setI;
		}
	}


	forAll(setNameAndProcs_, setI)
	{
		// Info<< "Keeping all cells connected to faceSet "
		//    << setNameAndProcs_[setI].first()
		//    << " on processor " << setNameAndProcs_[setI].second() << endl;

		const label destProcI = setNameAndProcs_[setI].second();

		// Read faceSet
		const faceSet fz(mesh, setNameAndProcs_[setI].first());

		// Check that it does not overlap with existing specifiedProcessorFaces
		labelList nMatch(specifiedProcessorFaces.size(), 0);
		forAllConstIter(faceSet, fz, iter)
		{
			label setI = faceToSet[iter.key()];
			if (setI != -1)
			{
				nMatch[setI]++;
			}
		}


		// Only store if all faces are not yet in specifiedProcessorFaces
		// (on all processors)
		bool store = true;

		forAll(nMatch, setI)
		{
			if (nMatch[setI] == fz.size())
			{
				// full match
				store = false;
				break;
			}
			else if (nMatch[setI] > 0)
			{
				// partial match
				store = false;
				break;
			}
		}

		reduce(store, andOp<bool>());


		if (store)
		{
			specifiedProcessorFaces.append(new labelList(fz.sortedToc()));
			specifiedProcessor.append(destProcI);
		}
	}


	// Unblock all point connected faces
	// 1. Mark all points on specifiedProcessorFaces
	boolList procFacePoint(mesh.nPoints(), false);
	forAll(specifiedProcessorFaces, setI)
	{
		const labelList& set = specifiedProcessorFaces[setI];
		forAll(set, fI)
		{
			const face& f = mesh.faces()[set[fI]];
			forAll(f, fp)
			{
				procFacePoint[f[fp]] = true;
			}
		}
	}
	syncTools::syncPointList(mesh, procFacePoint, orEqOp<bool>(), false);

	// 2. Unblock all faces on procFacePoint

	label nUnblocked = 0;

	forAll(procFacePoint, pointi)
	{
		if (procFacePoint[pointi])
		{
			const labelList& pFaces = mesh.pointFaces()[pointi];
			forAll(pFaces, i)
			{
				if (blockedFace[pFaces[i]])
				{
					blockedFace[pFaces[i]] = false;
					nUnblocked++;
				}
			}
		}
	}

	if (decompositionConstraint::debug & 2)
	{
		reduce(nUnblocked, sumOp<label>());
		Info << type() << " : unblocked " << nUnblocked << " faces" << endl;
	}

	syncTools::syncFaceList(mesh, blockedFace, andEqOp<bool>());
}


void tnbLib::decompositionConstraints::singleProcessorFaceSetsConstraint::apply
(
	const polyMesh& mesh,
	const boolList& blockedFace,
	const PtrList<labelList>& specifiedProcessorFaces,
	const labelList& specifiedProcessor,
	const List<labelPair>& explicitConnections,
	labelList& decomposition
) const
{
	// For specifiedProcessorFaces rework the cellToProc to enforce
	// all on one processor since we can't guarantee that the input
	// to regionSplit was a single region.
	// E.g. faceSet 'a' with the cells split into two regions
	// by a notch formed by two walls
	//
	//          \   /
	//           \ /
	//    ---a----+-----a-----
	//
	//
	// Note that reworking the cellToProc might make the decomposition
	// unbalanced.
	label nChanged = 0;

	forAll(specifiedProcessorFaces, setI)
	{
		const labelList& set = specifiedProcessorFaces[setI];

		// Get the processor to use for the set
		label procI = specifiedProcessor[setI];
		if (procI == -1)
		{
			// If no processor specified use the one from the
			// 0th element
			if (set.size())
			{
				procI = decomposition[mesh.faceOwner()[set[0]]];
			}
			reduce(procI, maxOp<label>());
		}

		// Get all points on the sets
		boolList procFacePoint(mesh.nPoints(), false);
		forAll(set, fI)
		{
			const face& f = mesh.faces()[set[fI]];
			forAll(f, fp)
			{
				procFacePoint[f[fp]] = true;
			}
		}
		syncTools::syncPointList(mesh, procFacePoint, orEqOp<bool>(), false);

		// 2. Unblock all faces on procFacePoint
		forAll(procFacePoint, pointi)
		{
			if (procFacePoint[pointi])
			{
				const labelList& pFaces = mesh.pointFaces()[pointi];
				forAll(pFaces, i)
				{
					label faceI = pFaces[i];

					label own = mesh.faceOwner()[faceI];
					if (decomposition[own] != procI)
					{
						decomposition[own] = procI;
						nChanged++;
					}
					if (mesh.isInternalFace(faceI))
					{
						label nei = mesh.faceNeighbour()[faceI];
						if (decomposition[nei] != procI)
						{
							decomposition[nei] = procI;
							nChanged++;
						}
					}
				}
			}
		}
	}

	if (decompositionConstraint::debug & 2)
	{
		reduce(nChanged, sumOp<label>());
		Info << type() << " : changed decomposition on " << nChanged
			<< " cells" << endl;
	}
}


// ************************************************************************* //