#include <preserveBafflesConstraint.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <syncTools.hxx>
#include <localPointRegion.hxx>
#include <PstreamReduceOps.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace decompositionConstraints
	{
		defineTypeName(preserveBafflesConstraint);

		addToRunTimeSelectionTable
		(
			decompositionConstraint,
			preserveBafflesConstraint,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::decompositionConstraints::preserveBafflesConstraint::
preserveBafflesConstraint
(
	const dictionary& constraintsDict,
	const word& modelType
)
	:
	decompositionConstraint(constraintsDict, typeName)
{
	if (decompositionConstraint::debug)
	{
		Info << type() << " : setting constraints to preserve baffles"
			//<< returnReduce(bafflePairs.size(), sumOp<label>())
			<< endl;
	}
}


tnbLib::decompositionConstraints::preserveBafflesConstraint::
preserveBafflesConstraint()
	:
	decompositionConstraint(dictionary(), typeName)
{
	if (decompositionConstraint::debug)
	{
		Info << type() << " : setting constraints to preserve baffles"
			//<< returnReduce(bafflePairs.size(), sumOp<label>())
			<< endl;
	}
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void tnbLib::decompositionConstraints::preserveBafflesConstraint::add
(
	const polyMesh& mesh,
	boolList& blockedFace,
	PtrList<labelList>& specifiedProcessorFaces,
	labelList& specifiedProcessor,
	List<labelPair>& explicitConnections
) const
{
	const labelPairList bafflePairs
	(
		localPointRegion::findDuplicateFacePairs(mesh)
	);

	if (decompositionConstraint::debug & 2)
	{
		Info << type() << " : setting constraints to preserve "
			<< returnReduce(bafflePairs.size(), sumOp<label>())
			<< " baffles" << endl;
	}


	// Merge into explicitConnections
	{
		// Convert into face-to-face addressing
		labelList faceToFace(mesh.nFaces(), -1);
		forAll(explicitConnections, i)
		{
			const labelPair& p = explicitConnections[i];
			faceToFace[p[0]] = p[1];
			faceToFace[p[1]] = p[0];
		}

		// Merge in bafflePairs
		forAll(bafflePairs, i)
		{
			const labelPair& p = bafflePairs[i];

			if (faceToFace[p[0]] == -1 && faceToFace[p[1]] == -1)
			{
				faceToFace[p[0]] = p[1];
				faceToFace[p[1]] = p[0];
			}
			else if (labelPair::compare(p, labelPair(p[0], faceToFace[p[0]])))
			{
				// Connection already present
			}
			else
			{
				label p0Slave = faceToFace[p[0]];
				label p1Slave = faceToFace[p[1]];
				IOWarningInFunction(coeffDict_)
					<< "When adding baffle between faces "
					<< p[0] << " at " << mesh.faceCentres()[p[0]]
					<< " and "
					<< p[1] << " at " << mesh.faceCentres()[p[1]]
					<< " : face " << p[0] << " already is connected to face "
					<< p0Slave << " at " << mesh.faceCentres()[p0Slave]
					<< " and face " << p[1] << " already is connected to face "
					<< p1Slave << " at " << mesh.faceCentres()[p1Slave]
					<< endl;
			}
		}

		// Convert back into labelPairList
		label n = 0;
		forAll(faceToFace, faceI)
		{
			label otherFaceI = faceToFace[faceI];
			if (otherFaceI != -1 && faceI < otherFaceI)
			{
				// I am master of slave
				n++;
			}
		}
		explicitConnections.setSize(n);
		n = 0;
		forAll(faceToFace, faceI)
		{
			label otherFaceI = faceToFace[faceI];
			if (otherFaceI != -1 && faceI < otherFaceI)
			{
				explicitConnections[n++] = labelPair(faceI, otherFaceI);
			}
		}
	}

	// Make sure blockedFace is uptodate
	blockedFace.setSize(mesh.nFaces(), true);
	forAll(explicitConnections, i)
	{
		blockedFace[explicitConnections[i].first()] = false;
		blockedFace[explicitConnections[i].second()] = false;
	}
	syncTools::syncFaceList(mesh, blockedFace, andEqOp<bool>());
}


void tnbLib::decompositionConstraints::preserveBafflesConstraint::apply
(
	const polyMesh& mesh,
	const boolList& blockedFace,
	const PtrList<labelList>& specifiedProcessorFaces,
	const labelList& specifiedProcessor,
	const List<labelPair>& explicitConnections,
	labelList& decomposition
) const
{
	const labelPairList bafflePairs
	(
		localPointRegion::findDuplicateFacePairs(mesh)
	);

	label nChanged = 0;

	forAll(bafflePairs, i)
	{
		const labelPair& baffle = bafflePairs[i];
		label f0 = baffle.first();
		label f1 = baffle.second();

		const label procI = decomposition[mesh.faceOwner()[f0]];

		if (mesh.isInternalFace(f0))
		{
			label nei0 = mesh.faceNeighbour()[f0];
			if (decomposition[nei0] != procI)
			{
				decomposition[nei0] = procI;
				nChanged++;
			}
		}

		label own1 = mesh.faceOwner()[f1];
		if (decomposition[own1] != procI)
		{
			decomposition[own1] = procI;
			nChanged++;
		}
		if (mesh.isInternalFace(f1))
		{
			label nei1 = mesh.faceNeighbour()[f1];
			if (decomposition[nei1] != procI)
			{
				decomposition[nei1] = procI;
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