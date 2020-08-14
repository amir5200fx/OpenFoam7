#include <preserveFaceZonesConstraint.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <syncTools.hxx>

#include <PstreamReduceOps.hxx>  // added by amir
#include <stringListOps.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace decompositionConstraints
	{
		defineTypeName(preserveFaceZonesConstraint);

		addToRunTimeSelectionTable
		(
			decompositionConstraint,
			preserveFaceZonesConstraint,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::decompositionConstraints::preserveFaceZonesConstraint::
preserveFaceZonesConstraint
(
	const dictionary& constraintsDict,
	const word& modelType
)
	:
	decompositionConstraint(constraintsDict, typeName),
	zones_(coeffDict_.lookup("zones"))
{
	if (decompositionConstraint::debug)
	{
		Info << type() << " : adding constraints to keep owner and neighbour"
			<< " of faces in zones " << zones_
			<< " on same processor" << endl;
	}
}


tnbLib::decompositionConstraints::preserveFaceZonesConstraint::
preserveFaceZonesConstraint
(
	const wordReList& zones
)
	:
	decompositionConstraint(dictionary(), typeName),
	zones_(zones)
{
	if (decompositionConstraint::debug)
	{
		Info << type() << " : adding constraints to keep owner and neighbour"
			<< " of faces in zones " << zones_
			<< " on same processor" << endl;
	}
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void tnbLib::decompositionConstraints::preserveFaceZonesConstraint::add
(
	const polyMesh& mesh,
	boolList& blockedFace,
	PtrList<labelList>& specifiedProcessorFaces,
	labelList& specifiedProcessor,
	List<labelPair>& explicitConnections
) const
{
	blockedFace.setSize(mesh.nFaces(), true);

	const faceZoneMesh& fZones = mesh.faceZones();

	const labelList zoneIDs = findStrings(zones_, fZones.names());

	label nUnblocked = 0;

	forAll(zoneIDs, i)
	{
		const faceZone& fz = fZones[zoneIDs[i]];

		forAll(fz, i)
		{
			if (blockedFace[fz[i]])
			{
				blockedFace[fz[i]] = false;
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


void tnbLib::decompositionConstraints::preserveFaceZonesConstraint::apply
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


	// Synchronise decomposition on boundary
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

	const faceZoneMesh& fZones = mesh.faceZones();

	const labelList zoneIDs = findStrings(zones_, fZones.names());

	label nChanged = 0;

	forAll(zoneIDs, i)
	{
		const faceZone& fz = fZones[zoneIDs[i]];

		forAll(fz, i)
		{
			label faceI = fz[i];

			label own = mesh.faceOwner()[faceI];

			if (mesh.isInternalFace(faceI))
			{
				label nei = mesh.faceNeighbour()[faceI];
				if (decomposition[own] != decomposition[nei])
				{
					decomposition[nei] = decomposition[own];
					nChanged++;
				}
			}
			else
			{
				label bFaceI = faceI - mesh.nInternalFaces();
				if (decomposition[own] != destProc[bFaceI])
				{
					decomposition[own] = destProc[bFaceI];
					nChanged++;
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