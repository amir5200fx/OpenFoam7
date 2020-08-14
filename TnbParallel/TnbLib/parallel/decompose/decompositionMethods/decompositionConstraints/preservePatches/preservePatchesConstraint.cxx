#include <preservePatchesConstraint.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <syncTools.hxx>

#include <PstreamReduceOps.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace decompositionConstraints
	{
		defineTypeName(preservePatchesConstraint);

		addToRunTimeSelectionTable
		(
			decompositionConstraint,
			preservePatchesConstraint,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::decompositionConstraints::preservePatchesConstraint::
preservePatchesConstraint
(
	const dictionary& constraintsDict,
	const word& modelType
)
	:
	decompositionConstraint(constraintsDict, typeName),
	patches_(coeffDict_.lookup("patches"))
{
	if (decompositionConstraint::debug)
	{
		Info << type() << " : adding constraints to keep owner of faces"
			<< " in patches " << patches_
			<< " on same processor. This only makes sense for cyclics." << endl;
	}
}


tnbLib::decompositionConstraints::preservePatchesConstraint::
preservePatchesConstraint
(
	const wordReList& patches
)
	:
	decompositionConstraint(dictionary(), typeName),
	patches_(patches)
{
	if (decompositionConstraint::debug)
	{
		Info << type() << " : adding constraints to keep owner of faces"
			<< " in patches " << patches_
			<< " on same processor. This only makes sense for cyclics." << endl;
	}
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void tnbLib::decompositionConstraints::preservePatchesConstraint::add
(
	const polyMesh& mesh,
	boolList& blockedFace,
	PtrList<labelList>& specifiedProcessorFaces,
	labelList& specifiedProcessor,
	List<labelPair>& explicitConnections
) const
{
	const polyBoundaryMesh& pbm = mesh.boundaryMesh();

	blockedFace.setSize(mesh.nFaces(), true);

	const labelList patchIDs(pbm.patchSet(patches_).sortedToc());

	label nUnblocked = 0;

	forAll(patchIDs, i)
	{
		const polyPatch& pp = pbm[patchIDs[i]];

		forAll(pp, i)
		{
			if (blockedFace[pp.start() + i])
			{
				blockedFace[pp.start() + i] = false;
				nUnblocked++;
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


void tnbLib::decompositionConstraints::preservePatchesConstraint::apply
(
	const polyMesh& mesh,
	const boolList& blockedFace,
	const PtrList<labelList>& specifiedProcessorFaces,
	const labelList& specifiedProcessor,
	const List<labelPair>& explicitConnections,
	labelList& decomposition
) const
{
	// If the decomposition has not enforced the constraint do it over
	// here.

	// Synchronise decomposition on patchIDs
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	const polyBoundaryMesh& pbm = mesh.boundaryMesh();

	labelList destProc(mesh.nFaces() - mesh.nInternalFaces(), labelMax);

	forAll(pbm, patchi)
	{
		const polyPatch& pp = pbm[patchi];

		const labelUList& faceCells = pp.faceCells();

		forAll(faceCells, i)
		{
			label bFaceI = pp.start() + i - mesh.nInternalFaces();
			destProc[bFaceI] = decomposition[faceCells[i]];
		}
	}

	syncTools::syncBoundaryFaceList(mesh, destProc, minEqOp<label>());


	// Override if differing
	// ~~~~~~~~~~~~~~~~~~~~~

	const labelList patchIDs(pbm.patchSet(patches_).sortedToc());

	label nChanged = 0;

	forAll(patchIDs, i)
	{
		const polyPatch& pp = pbm[patchIDs[i]];

		const labelUList& faceCells = pp.faceCells();

		forAll(faceCells, i)
		{
			label bFaceI = pp.start() + i - mesh.nInternalFaces();

			if (decomposition[faceCells[i]] != destProc[bFaceI])
			{
				decomposition[faceCells[i]] = destProc[bFaceI];
				nChanged++;
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