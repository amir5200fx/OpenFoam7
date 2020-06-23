#include <polyMesh.hxx>

#include <Time.hxx>
#include <cellIOList.hxx>
#include <wedgePolyPatch.hxx>
#include <emptyPolyPatch.hxx>
#include <globalMeshData.hxx>
#include <processorPolyPatch.hxx>
#include <polyMeshTetDecomposition.hxx>
#include <indexedOctree.hxx>
#include <treeDataCell.hxx>
#include <MeshObject.hxx>
#include <pointMesh.hxx>

#include <PstreamReduceOps.hxx> // added by amir
#include <SubField.hxx> // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(polyMesh, 0);

	word polyMesh::defaultRegion = "region0";
	word polyMesh::meshSubDir = "polyMesh";
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::polyMesh::calcDirections() const
{
	for (direction cmpt = 0; cmpt < vector::nComponents; cmpt++)
	{
		solutionD_[cmpt] = 1;
	}

	// Knock out empty and wedge directions. Note:they will be present on all
	// domains.

	label nEmptyPatches = 0;
	label nWedgePatches = 0;

	vector emptyDirVec = Zero;
	vector wedgeDirVec = Zero;

	forAll(boundaryMesh(), patchi)
	{
		if (boundaryMesh()[patchi].size())
		{
			if (isA<emptyPolyPatch>(boundaryMesh()[patchi]))
			{
				nEmptyPatches++;
				emptyDirVec += sum(cmptMag(boundaryMesh()[patchi].faceAreas()));
			}
			else if (isA<wedgePolyPatch>(boundaryMesh()[patchi]))
			{
				const wedgePolyPatch& wpp = refCast<const wedgePolyPatch>
					(
						boundaryMesh()[patchi]
						);

				nWedgePatches++;
				wedgeDirVec += cmptMag(wpp.centreNormal());
			}
		}
	}

	reduce(nEmptyPatches, maxOp<label>());
	reduce(nWedgePatches, maxOp<label>());

	if (nEmptyPatches)
	{
		reduce(emptyDirVec, sumOp<vector>());

		emptyDirVec /= mag(emptyDirVec);

		for (direction cmpt = 0; cmpt < vector::nComponents; cmpt++)
		{
			if (emptyDirVec[cmpt] > 1e-6)
			{
				solutionD_[cmpt] = -1;
			}
			else
			{
				solutionD_[cmpt] = 1;
			}
		}
	}


	// Knock out wedge directions

	geometricD_ = solutionD_;

	if (nWedgePatches)
	{
		reduce(wedgeDirVec, sumOp<vector>());

		wedgeDirVec /= mag(wedgeDirVec);

		for (direction cmpt = 0; cmpt < vector::nComponents; cmpt++)
		{
			if (wedgeDirVec[cmpt] > 1e-6)
			{
				geometricD_[cmpt] = -1;
			}
			else
			{
				geometricD_[cmpt] = 1;
			}
		}
	}
}


tnbLib::autoPtr<tnbLib::labelIOList> tnbLib::polyMesh::readTetBasePtIs() const
{
	IOobject io
	(
		"tetBasePtIs",
		instance(),
		meshSubDir,
		*this,
		IOobject::READ_IF_PRESENT,
		IOobject::NO_WRITE
	);

	if (io.typeHeaderOk<labelIOList>())
	{
		return autoPtr<labelIOList>(new labelIOList(io));
	}
	else
	{
		return autoPtr<labelIOList>(nullptr);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::polyMesh::polyMesh(const IOobject& io)
	:
	objectRegistry(io),
	primitiveMesh(),
	points_
	(
		IOobject
		(
			"points",
			time().findInstance(meshDir(), "points"),
			meshSubDir,
			*this,
			IOobject::MUST_READ,
			IOobject::NO_WRITE
		)
	),
	faces_
	(
		IOobject
		(
			"faces",
			time().findInstance(meshDir(), "faces"),
			meshSubDir,
			*this,
			IOobject::MUST_READ,
			IOobject::NO_WRITE
		)
	),
	owner_
	(
		IOobject
		(
			"owner",
			faces_.instance(),
			meshSubDir,
			*this,
			IOobject::READ_IF_PRESENT,
			IOobject::NO_WRITE
		)
	),
	neighbour_
	(
		IOobject
		(
			"neighbour",
			faces_.instance(),
			meshSubDir,
			*this,
			IOobject::READ_IF_PRESENT,
			IOobject::NO_WRITE
		)
	),
	clearedPrimitives_(false),
	boundary_
	(
		IOobject
		(
			"boundary",
			time().findInstance(meshDir(), "boundary"),
			meshSubDir,
			*this,
			IOobject::MUST_READ,
			IOobject::NO_WRITE
		),
		*this
	),
	bounds_(points_),
	comm_(UPstream::worldComm),
	geometricD_(Zero),
	solutionD_(Zero),
	tetBasePtIsPtr_(readTetBasePtIs()),
	cellTreePtr_(nullptr),
	pointZones_
	(
		IOobject
		(
			"pointZones",
			time().findInstance
			(
				meshDir(),
				"pointZones",
				IOobject::READ_IF_PRESENT
			),
			meshSubDir,
			*this,
			IOobject::READ_IF_PRESENT,
			IOobject::NO_WRITE
		),
		*this
	),
	faceZones_
	(
		IOobject
		(
			"faceZones",
			time().findInstance
			(
				meshDir(),
				"faceZones",
				IOobject::READ_IF_PRESENT
			),
			meshSubDir,
			*this,
			IOobject::READ_IF_PRESENT,
			IOobject::NO_WRITE
		),
		*this
	),
	cellZones_
	(
		IOobject
		(
			"cellZones",
			time().findInstance
			(
				meshDir(),
				"cellZones",
				IOobject::READ_IF_PRESENT
			),
			meshSubDir,
			*this,
			IOobject::READ_IF_PRESENT,
			IOobject::NO_WRITE
		),
		*this
	),
	globalMeshDataPtr_(nullptr),
	moving_(false),
	topoChanging_(false),
	curMotionTimeIndex_(-1),
	oldPointsPtr_(nullptr),
	oldCellCentresPtr_(nullptr),
	storeOldCellCentres_(false)
{
	if (!owner_.headerClassName().empty())
	{
		initMesh();
	}
	else
	{
		cellCompactIOList cLst
		(
			IOobject
			(
				"cells",
				time().findInstance(meshDir(), "cells"),
				meshSubDir,
				*this,
				IOobject::MUST_READ,
				IOobject::NO_WRITE
			)
		);

		// Set the primitive mesh
		initMesh(cLst);

		owner_.write();
		neighbour_.write();
	}

	// Calculate topology for the patches (processor-processor comms etc.)
	boundary_.updateMesh();

	// Calculate the geometry for the patches (transformation tensors etc.)
	boundary_.calcGeometry();

	// Warn if global empty mesh
	if (returnReduce(nPoints(), sumOp<label>()) == 0)
	{
		WarningInFunction
			<< "no points in mesh" << endl;
	}
	if (returnReduce(nCells(), sumOp<label>()) == 0)
	{
		WarningInFunction
			<< "no cells in mesh" << endl;
	}

	// Initialise demand-driven data
	calcDirections();
}


tnbLib::polyMesh::polyMesh
(
	const IOobject& io,
	pointField&& points,
	faceList&& faces,
	labelList&& owner,
	labelList&& neighbour,
	const bool syncPar
)
	:
	objectRegistry(io),
	primitiveMesh(),
	points_
	(
		IOobject
		(
			"points",
			instance(),
			meshSubDir,
			*this,
			io.readOpt(),
			IOobject::AUTO_WRITE
		),
		move(points)
	),
	faces_
	(
		IOobject
		(
			"faces",
			instance(),
			meshSubDir,
			*this,
			io.readOpt(),
			IOobject::AUTO_WRITE
		),
		move(faces)
	),
	owner_
	(
		IOobject
		(
			"owner",
			instance(),
			meshSubDir,
			*this,
			io.readOpt(),
			IOobject::AUTO_WRITE
		),
		move(owner)
	),
	neighbour_
	(
		IOobject
		(
			"neighbour",
			instance(),
			meshSubDir,
			*this,
			io.readOpt(),
			IOobject::AUTO_WRITE
		),
		move(neighbour)
	),
	clearedPrimitives_(false),
	boundary_
	(
		IOobject
		(
			"boundary",
			instance(),
			meshSubDir,
			*this,
			io.readOpt(),
			IOobject::AUTO_WRITE
		),
		*this,
		polyPatchList()
	),
	bounds_(points_, syncPar),
	comm_(UPstream::worldComm),
	geometricD_(Zero),
	solutionD_(Zero),
	tetBasePtIsPtr_(readTetBasePtIs()),
	cellTreePtr_(nullptr),
	pointZones_
	(
		IOobject
		(
			"pointZones",
			instance(),
			meshSubDir,
			*this,
			io.readOpt(),
			IOobject::NO_WRITE
		),
		*this,
		PtrList<pointZone>()
	),
	faceZones_
	(
		IOobject
		(
			"faceZones",
			instance(),
			meshSubDir,
			*this,
			io.readOpt(),
			IOobject::NO_WRITE
		),
		*this,
		PtrList<faceZone>()
	),
	cellZones_
	(
		IOobject
		(
			"cellZones",
			instance(),
			meshSubDir,
			*this,
			io.readOpt(),
			IOobject::NO_WRITE
		),
		*this,
		PtrList<cellZone>()
	),
	globalMeshDataPtr_(nullptr),
	moving_(false),
	topoChanging_(false),
	curMotionTimeIndex_(-1),
	oldPointsPtr_(nullptr),
	oldCellCentresPtr_(nullptr),
	storeOldCellCentres_(false)
{
	// Check if the faces and cells are valid
	forAll(faces_, facei)
	{
		const face& curFace = faces_[facei];

		if (min(curFace) < 0 || max(curFace) > points_.size())
		{
			FatalErrorInFunction
				<< "Face " << facei << "contains vertex labels out of range: "
				<< curFace << " Max point index = " << points_.size()
				<< abort(FatalError);
		}
	}

	// Set the primitive mesh
	initMesh();
}



tnbLib::polyMesh::polyMesh
(
	const IOobject& io,
	pointField&& points,
	faceList&& faces,
	cellList&& cells,
	const bool syncPar
)
	:
	objectRegistry(io),
	primitiveMesh(),
	points_
	(
		IOobject
		(
			"points",
			instance(),
			meshSubDir,
			*this,
			IOobject::NO_READ,
			IOobject::AUTO_WRITE
		),
		move(points)
	),
	faces_
	(
		IOobject
		(
			"faces",
			instance(),
			meshSubDir,
			*this,
			IOobject::NO_READ,
			IOobject::AUTO_WRITE
		),
		move(faces)
	),
	owner_
	(
		IOobject
		(
			"owner",
			instance(),
			meshSubDir,
			*this,
			IOobject::NO_READ,
			IOobject::AUTO_WRITE
		),
		0
	),
	neighbour_
	(
		IOobject
		(
			"neighbour",
			instance(),
			meshSubDir,
			*this,
			IOobject::NO_READ,
			IOobject::AUTO_WRITE
		),
		0
	),
	clearedPrimitives_(false),
	boundary_
	(
		IOobject
		(
			"boundary",
			instance(),
			meshSubDir,
			*this,
			IOobject::NO_READ,
			IOobject::AUTO_WRITE
		),
		*this,
		0
	),
	bounds_(points_, syncPar),
	comm_(UPstream::worldComm),
	geometricD_(Zero),
	solutionD_(Zero),
	tetBasePtIsPtr_(readTetBasePtIs()),
	cellTreePtr_(nullptr),
	pointZones_
	(
		IOobject
		(
			"pointZones",
			instance(),
			meshSubDir,
			*this,
			IOobject::NO_READ,
			IOobject::NO_WRITE
		),
		*this,
		0
	),
	faceZones_
	(
		IOobject
		(
			"faceZones",
			instance(),
			meshSubDir,
			*this,
			IOobject::NO_READ,
			IOobject::NO_WRITE
		),
		*this,
		0
	),
	cellZones_
	(
		IOobject
		(
			"cellZones",
			instance(),
			meshSubDir,
			*this,
			IOobject::NO_READ,
			IOobject::NO_WRITE
		),
		*this,
		0
	),
	globalMeshDataPtr_(nullptr),
	moving_(false),
	topoChanging_(false),
	curMotionTimeIndex_(-1),
	oldPointsPtr_(nullptr),
	oldCellCentresPtr_(nullptr),
	storeOldCellCentres_(false)
{
	// Check if faces are valid
	forAll(faces_, facei)
	{
		const face& curFace = faces_[facei];

		if (min(curFace) < 0 || max(curFace) > points_.size())
		{
			FatalErrorInFunction
				<< "Face " << facei << "contains vertex labels out of range: "
				<< curFace << " Max point index = " << points_.size()
				<< abort(FatalError);
		}
	}

	// transfer in cell list
	cellList cLst(move(cells));

	// Check if cells are valid
	forAll(cLst, celli)
	{
		const cell& curCell = cLst[celli];

		if (min(curCell) < 0 || max(curCell) > faces_.size())
		{
			FatalErrorInFunction
				<< "Cell " << celli << "contains face labels out of range: "
				<< curCell << " Max face index = " << faces_.size()
				<< abort(FatalError);
		}
	}

	// Set the primitive mesh
	initMesh(cLst);
}


void tnbLib::polyMesh::resetPrimitives
(
	pointField&& points,
	faceList&& faces,
	labelList&& owner,
	labelList&& neighbour,
	const labelList& patchSizes,
	const labelList& patchStarts,
	const bool validBoundary
)
{
	// Clear addressing. Keep geometric props and updateable props for mapping.
	clearAddressing(true);

	// Take over new primitive data.
	// Optimized to avoid overwriting data at all
	if (notNull(points))
	{
		points_ = move(points);
		bounds_ = boundBox(points_, validBoundary);
	}

	if (notNull(faces))
	{
		faces_ = move(faces);
	}

	if (notNull(owner))
	{
		owner_ = move(owner);
	}

	if (notNull(neighbour))
	{
		neighbour_ = move(neighbour);
	}


	// Reset patch sizes and starts
	forAll(boundary_, patchi)
	{
		boundary_[patchi] = polyPatch
		(
			boundary_[patchi],
			boundary_,
			patchi,
			patchSizes[patchi],
			patchStarts[patchi]
		);
	}


	// Flags the mesh files as being changed
	setInstance(time().timeName());

	// Check if the faces and cells are valid
	forAll(faces_, facei)
	{
		const face& curFace = faces_[facei];

		if (min(curFace) < 0 || max(curFace) > points_.size())
		{
			FatalErrorInFunction
				<< "Face " << facei << " contains vertex labels out of range: "
				<< curFace << " Max point index = " << points_.size()
				<< abort(FatalError);
		}
	}


	// Set the primitive mesh from the owner_, neighbour_.
	// Works out from patch end where the active faces stop.
	initMesh();


	if (validBoundary)
	{
		// Note that we assume that all the patches stay the same and are
		// correct etc. so we can already use the patches to do
		// processor-processor comms.

		// Calculate topology for the patches (processor-processor comms etc.)
		boundary_.updateMesh();

		// Calculate the geometry for the patches (transformation tensors etc.)
		boundary_.calcGeometry();

		// Warn if global empty mesh
		if
			(
			(returnReduce(nPoints(), sumOp<label>()) == 0)
				|| (returnReduce(nCells(), sumOp<label>()) == 0)
				)
		{
			FatalErrorInFunction
				<< "no points or no cells in mesh" << endl;
		}
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::polyMesh::~polyMesh()
{
	clearOut();
	resetMotion();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::fileName& tnbLib::polyMesh::dbDir() const
{
	if (objectRegistry::dbDir() == defaultRegion)
	{
		return parent().dbDir();
	}
	else
	{
		return objectRegistry::dbDir();
	}
}


tnbLib::fileName tnbLib::polyMesh::meshDir() const
{
	return dbDir() / meshSubDir;
}


const tnbLib::fileName& tnbLib::polyMesh::pointsInstance() const
{
	return points_.instance();
}


const tnbLib::fileName& tnbLib::polyMesh::facesInstance() const
{
	return faces_.instance();
}


const tnbLib::Vector<tnbLib::label>& tnbLib::polyMesh::geometricD() const
{
	if (geometricD_.x() == 0)
	{
		calcDirections();
	}

	return geometricD_;
}


tnbLib::label tnbLib::polyMesh::nGeometricD() const
{
	return cmptSum(geometricD() + Vector<label>::one) / 2;
}


const tnbLib::Vector<tnbLib::label>& tnbLib::polyMesh::solutionD() const
{
	if (solutionD_.x() == 0)
	{
		calcDirections();
	}

	return solutionD_;
}


tnbLib::label tnbLib::polyMesh::nSolutionD() const
{
	return cmptSum(solutionD() + Vector<label>::one) / 2;
}


const tnbLib::labelIOList& tnbLib::polyMesh::tetBasePtIs() const
{
	if (tetBasePtIsPtr_.empty())
	{
		if (debug)
		{
			WarningInFunction
				<< "Forcing storage of base points."
				<< endl;
		}

		tetBasePtIsPtr_.reset
		(
			new labelIOList
			(
				IOobject
				(
					"tetBasePtIs",
					instance(),
					meshSubDir,
					*this,
					IOobject::READ_IF_PRESENT,
					IOobject::NO_WRITE
				),
				polyMeshTetDecomposition::findFaceBasePts(*this)
			)
		);
	}

	return tetBasePtIsPtr_();
}


const tnbLib::indexedOctree<tnbLib::treeDataCell>&
tnbLib::polyMesh::cellTree() const
{
	if (cellTreePtr_.empty())
	{
		cellTreePtr_.reset
		(
			new indexedOctree<treeDataCell>
			(
				treeDataCell
				(
					false,      // not cache bb
					*this,
					CELL_TETS   // use tet-decomposition for any inside test
				),
				treeBoundBox(points()).extend(1e-4),
				8,              // maxLevel
				10,             // leafsize
				5.0             // duplicity
				)
		);
	}

	return cellTreePtr_();
}


void tnbLib::polyMesh::addPatches
(
	const List<polyPatch*>& p,
	const bool validBoundary
)
{
	if (boundaryMesh().size())
	{
		FatalErrorInFunction
			<< "boundary already exists"
			<< abort(FatalError);
	}

	// Reset valid directions
	geometricD_ = Zero;
	solutionD_ = Zero;

	boundary_.setSize(p.size());

	// Copy the patch pointers
	forAll(p, pI)
	{
		boundary_.set(pI, p[pI]);
	}

	// parallelData depends on the processorPatch ordering so force
	// recalculation. Problem: should really be done in removeBoundary but
	// there is some info in parallelData which might be interesting in between
	// removeBoundary and addPatches.
	globalMeshDataPtr_.clear();

	if (validBoundary)
	{
		// Calculate topology for the patches (processor-processor comms etc.)
		boundary_.updateMesh();

		// Calculate the geometry for the patches (transformation tensors etc.)
		boundary_.calcGeometry();

		boundary_.checkDefinition();
	}
}


void tnbLib::polyMesh::addZones
(
	const List<pointZone*>& pz,
	const List<faceZone*>& fz,
	const List<cellZone*>& cz
)
{
	if (pointZones().size() || faceZones().size() || cellZones().size())
	{
		FatalErrorInFunction
			<< "point, face or cell zone already exists"
			<< abort(FatalError);
	}

	// Point zones
	if (pz.size())
	{
		pointZones_.setSize(pz.size());

		// Copy the zone pointers
		forAll(pz, pI)
		{
			pointZones_.set(pI, pz[pI]);
		}

		pointZones_.writeOpt() = IOobject::AUTO_WRITE;
	}

	// Face zones
	if (fz.size())
	{
		faceZones_.setSize(fz.size());

		// Copy the zone pointers
		forAll(fz, fI)
		{
			faceZones_.set(fI, fz[fI]);
		}

		faceZones_.writeOpt() = IOobject::AUTO_WRITE;
	}

	// Cell zones
	if (cz.size())
	{
		cellZones_.setSize(cz.size());

		// Copy the zone pointers
		forAll(cz, cI)
		{
			cellZones_.set(cI, cz[cI]);
		}

		cellZones_.writeOpt() = IOobject::AUTO_WRITE;
	}
}


void tnbLib::polyMesh::reorderPatches
(
	const labelUList& newToOld,
	const bool validBoundary
)
{
	// Clear local fields and e.g. polyMesh parallelInfo. Do not clearGeom
	// so we keep PatchMeshObjects intact.
	boundary_.clearGeom();
	clearAddressing(true);
	// Clear all but PatchMeshObjects
	meshObject::clearUpto
		<
		polyMesh,
		TopologicalMeshObject,
		PatchMeshObject
		>
		(
			*this
			);
	meshObject::clearUpto
		<
		pointMesh,
		TopologicalMeshObject,
		PatchMeshObject
		>
		(
			*this
			);

	boundary_.shuffle(newToOld, validBoundary);

	// Warn mesh objects
	meshObject::reorderPatches<polyMesh>(*this, newToOld, validBoundary);
	meshObject::reorderPatches<pointMesh>(*this, newToOld, validBoundary);
}


void tnbLib::polyMesh::addPatch
(
	const label insertPatchi,
	const polyPatch& patch,
	const dictionary& patchFieldDict,
	const word& defaultPatchFieldType,
	const bool validBoundary
)
{
	const label sz = boundary_.size();

	label startFacei = nFaces();
	if (insertPatchi < sz)
	{
		startFacei = boundary_[insertPatchi].start();
	}

	// Create reordering list
	// patches before insert position stay as is
	// patches after insert position move one up
	labelList newToOld(boundary_.size() + 1);
	for (label i = 0; i < insertPatchi; i++)
	{
		newToOld[i] = i;
	}
	for (label i = insertPatchi; i < sz; i++)
	{
		newToOld[i + 1] = i;
	}
	newToOld[insertPatchi] = -1;

	reorderPatches(newToOld, false);

	// Clear local fields and e.g. polyMesh parallelInfo.
	//clearGeom();  // would clear out pointMesh as well
	boundary_.clearGeom();
	clearAddressing(true);

	// Clear all but PatchMeshObjects
	meshObject::clearUpto
		<
		polyMesh,
		TopologicalMeshObject,
		PatchMeshObject
		>
		(
			*this
			);
	meshObject::clearUpto
		<
		pointMesh,
		TopologicalMeshObject,
		PatchMeshObject
		>
		(
			*this
			);


	// Insert polyPatch
	boundary_.set
	(
		insertPatchi,
		patch.clone
		(
			boundary_,
			insertPatchi,   // index
			0,              // size
			startFacei      // start
		)
	);

	if (validBoundary)
	{
		boundary_.updateMesh();
	}

	// Warn mesh objects
	meshObject::addPatch<polyMesh>(*this, insertPatchi);
	meshObject::addPatch<pointMesh>(*this, insertPatchi);
}


const tnbLib::pointField& tnbLib::polyMesh::points() const
{
	if (clearedPrimitives_)
	{
		FatalErrorInFunction
			<< "points deallocated"
			<< abort(FatalError);
	}

	return points_;
}


bool tnbLib::polyMesh::upToDatePoints(const regIOobject& io) const
{
	return io.upToDate(points_);
}


void tnbLib::polyMesh::setUpToDatePoints(regIOobject& io) const
{
	io.eventNo() = points_.eventNo() + 1;
}


const tnbLib::faceList& tnbLib::polyMesh::faces() const
{
	if (clearedPrimitives_)
	{
		FatalErrorInFunction
			<< "faces deallocated"
			<< abort(FatalError);
	}

	return faces_;
}


const tnbLib::labelList& tnbLib::polyMesh::faceOwner() const
{
	return owner_;
}


const tnbLib::labelList& tnbLib::polyMesh::faceNeighbour() const
{
	return neighbour_;
}


const tnbLib::pointField& tnbLib::polyMesh::oldPoints() const
{
	if (!moving_)
	{
		return points_;
	}

	if (oldPointsPtr_.empty())
	{
		FatalErrorInFunction
			<< "Old points have not been stored"
			<< exit(FatalError);
	}

	return oldPointsPtr_();
}


const tnbLib::pointField& tnbLib::polyMesh::oldCellCentres() const
{
	storeOldCellCentres_ = true;

	if (!moving_)
	{
		return cellCentres();
	}

	if (oldCellCentresPtr_.empty())
	{
		FatalErrorInFunction
			<< "Old cell centres have not been stored"
			<< exit(FatalError);
	}

	return oldCellCentresPtr_();
}


tnbLib::IOobject tnbLib::polyMesh::points0IO
(
	const polyMesh& mesh
)
{
	const word instance
	(
		mesh.time().findInstance
		(
			mesh.meshDir(),
			"points0",
			IOobject::READ_IF_PRESENT
		)
	);

	if (instance != mesh.time().constant())
	{
		// Points0 written to a time folder

		return IOobject
		(
			"points0",
			instance,
			polyMesh::meshSubDir,
			mesh,
			IOobject::MUST_READ,
			IOobject::NO_WRITE,
			false
		);
	}
	else
	{
		// Check that points0 are actually in constant directory

		IOobject io
		(
			"points0",
			instance,
			polyMesh::meshSubDir,
			mesh,
			IOobject::MUST_READ,
			IOobject::NO_WRITE,
			false
		);

		if (io.typeHeaderOk<pointIOField>())
		{
			return io;
		}
		else
		{
			// Copy of original mesh points
			return IOobject
			(
				"points",
				instance,
				polyMesh::meshSubDir,
				mesh,
				IOobject::MUST_READ,
				IOobject::NO_WRITE,
				false
			);
		}
	}
}


tnbLib::tmp<tnbLib::scalarField> tnbLib::polyMesh::movePoints
(
	const pointField& newPoints
)
{
	if (debug)
	{
		InfoInFunction
			<< "Moving points for time " << time().value()
			<< " index " << time().timeIndex() << endl;
	}

	moving(true);

	// Pick up old points and cell centres
	if (curMotionTimeIndex_ != time().timeIndex())
	{
		oldPointsPtr_.clear();
		oldPointsPtr_.reset(new pointField(points_));
		if (storeOldCellCentres_)
		{
			oldCellCentresPtr_.clear();
			oldCellCentresPtr_.reset(new pointField(cellCentres()));
		}
		curMotionTimeIndex_ = time().timeIndex();
	}

	points_ = newPoints;

	bool moveError = false;
	if (debug)
	{
		// Check mesh motion
		if (checkMeshMotion(points_, true))
		{
			moveError = true;

			InfoInFunction
				<< "Moving the mesh with given points will "
				<< "invalidate the mesh." << nl
				<< "Mesh motion should not be executed." << endl;
		}
	}

	points_.writeOpt() = IOobject::AUTO_WRITE;
	points_.instance() = time().timeName();
	points_.eventNo() = getEvent();

	if (tetBasePtIsPtr_.valid())
	{
		tetBasePtIsPtr_().writeOpt() = IOobject::AUTO_WRITE;
		tetBasePtIsPtr_().instance() = time().timeName();
		tetBasePtIsPtr_().eventNo() = getEvent();
	}

	tmp<scalarField> sweptVols = primitiveMesh::movePoints
	(
		points_,
		oldPoints()
	);

	// Adjust parallel shared points
	if (globalMeshDataPtr_.valid())
	{
		globalMeshDataPtr_().movePoints(points_);
	}

	// Force recalculation of all geometric data with new points

	bounds_ = boundBox(points_);
	boundary_.movePoints(points_);

	pointZones_.movePoints(points_);
	faceZones_.movePoints(points_);
	cellZones_.movePoints(points_);

	// Cell tree might become invalid
	cellTreePtr_.clear();

	// Reset valid directions (could change with rotation)
	geometricD_ = Zero;
	solutionD_ = Zero;

	meshObject::movePoints<polyMesh>(*this);
	meshObject::movePoints<pointMesh>(*this);

	const_cast<Time&>(time()).functionObjects().movePoints(*this);


	if (debug && moveError)
	{
		// Write mesh to ease debugging. Note we want to avoid calling
		// e.g. fvMesh::write since meshPhi not yet complete.
		polyMesh::write();
	}

	return sweptVols;
}


void tnbLib::polyMesh::resetMotion() const
{
	curMotionTimeIndex_ = -1;
	oldPointsPtr_.clear();
	oldCellCentresPtr_.clear();
}


const tnbLib::globalMeshData& tnbLib::polyMesh::globalData() const
{
	if (globalMeshDataPtr_.empty())
	{
		if (debug)
		{
			Pout << "polyMesh::globalData() const : "
				<< "Constructing parallelData from processor topology"
				<< endl;
		}
		// Construct globalMeshData using processorPatch information only.
		globalMeshDataPtr_.reset(new globalMeshData(*this));
	}

	return globalMeshDataPtr_();
}


tnbLib::label tnbLib::polyMesh::comm() const
{
	return comm_;
}


tnbLib::label& tnbLib::polyMesh::comm()
{
	return comm_;
}


void tnbLib::polyMesh::removeFiles(const fileName& instanceDir) const
{
	fileName meshFilesPath = thisDb().time().path() / instanceDir / meshDir();

	rm(meshFilesPath / "points");
	rm(meshFilesPath / "faces");
	rm(meshFilesPath / "owner");
	rm(meshFilesPath / "neighbour");
	rm(meshFilesPath / "cells");
	rm(meshFilesPath / "boundary");
	rm(meshFilesPath / "pointZones");
	rm(meshFilesPath / "faceZones");
	rm(meshFilesPath / "cellZones");
	rm(meshFilesPath / "meshModifiers");
	rm(meshFilesPath / "parallelData");

	// remove subdirectories
	if (isDir(meshFilesPath / "sets"))
	{
		rmDir(meshFilesPath / "sets");
	}
}


void tnbLib::polyMesh::removeFiles() const
{
	removeFiles(instance());
}


void tnbLib::polyMesh::findCellFacePt
(
	const point& p,
	label& celli,
	label& tetFacei,
	label& tetPti
) const
{
	celli = -1;
	tetFacei = -1;
	tetPti = -1;

	const indexedOctree<treeDataCell>& tree = cellTree();

	// Find point inside cell
	celli = tree.findInside(p);

	if (celli != -1)
	{
		// Check the nearest cell to see if the point is inside.
		findTetFacePt(celli, p, tetFacei, tetPti);
	}
}


void tnbLib::polyMesh::findTetFacePt
(
	const label celli,
	const point& p,
	label& tetFacei,
	label& tetPti
) const
{
	const polyMesh& mesh = *this;

	tetIndices tet(polyMeshTetDecomposition::findTet(mesh, celli, p));
	tetFacei = tet.face();
	tetPti = tet.tetPt();
}


bool tnbLib::polyMesh::pointInCell
(
	const point& p,
	label celli,
	const cellDecomposition decompMode
) const
{
	switch (decompMode)
	{
	case FACE_PLANES:
	{
		return primitiveMesh::pointInCell(p, celli);
	}
	break;

	case FACE_CENTRE_TRIS:
	{
		// only test that point is on inside of plane defined by cell face
		// triangles
		const cell& cFaces = cells()[celli];

		forAll(cFaces, cFacei)
		{
			label facei = cFaces[cFacei];
			const face& f = faces_[facei];
			const point& fc = faceCentres()[facei];
			bool isOwn = (owner_[facei] == celli);

			forAll(f, fp)
			{
				label pointi;
				label nextPointi;

				if (isOwn)
				{
					pointi = f[fp];
					nextPointi = f.nextLabel(fp);
				}
				else
				{
					pointi = f.nextLabel(fp);
					nextPointi = f[fp];
				}

				triPointRef faceTri
				(
					points()[pointi],
					points()[nextPointi],
					fc
				);

				vector proj = p - faceTri.centre();

				if ((faceTri.area() & proj) > 0)
				{
					return false;
				}
			}
		}
		return true;
	}
	break;

	case FACE_DIAG_TRIS:
	{
		// only test that point is on inside of plane defined by cell face
		// triangles
		const cell& cFaces = cells()[celli];

		forAll(cFaces, cFacei)
		{
			label facei = cFaces[cFacei];
			const face& f = faces_[facei];

			for (label tetPti = 1; tetPti < f.size() - 1; tetPti++)
			{
				// Get tetIndices of face triangle
				tetIndices faceTetIs(celli, facei, tetPti);

				triPointRef faceTri = faceTetIs.faceTri(*this);

				vector proj = p - faceTri.centre();

				if ((faceTri.area() & proj) > 0)
				{
					return false;
				}
			}
		}

		return true;
	}
	break;

	case CELL_TETS:
	{
		label tetFacei;
		label tetPti;

		findTetFacePt(celli, p, tetFacei, tetPti);

		return tetFacei != -1;
	}
	break;
	}

	return false;
}


tnbLib::label tnbLib::polyMesh::findCell
(
	const point& p,
	const cellDecomposition decompMode
) const
{
	if
		(
			Pstream::parRun()
			&& (decompMode == FACE_DIAG_TRIS || decompMode == CELL_TETS)
			)
	{
		// Force construction of face-diagonal decomposition before testing
		// for zero cells.
		//
		// If parallel running a local domain might have zero cells so never
		// construct the face-diagonal decomposition which uses parallel
		// transfers.
		(void)tetBasePtIs();
	}

	if (nCells() == 0)
	{
		return -1;
	}

	if (decompMode == CELL_TETS)
	{
		// Advanced search method utilizing an octree
		// and tet-decomposition of the cells

		label celli;
		label tetFacei;
		label tetPti;

		findCellFacePt(p, celli, tetFacei, tetPti);

		return celli;
	}
	else
	{
		// Approximate search avoiding the construction of an octree
		// and cell decomposition

		// Find the nearest cell centre to this location
		label celli = findNearestCell(p);

		// If point is in the nearest cell return
		if (pointInCell(p, celli, decompMode))
		{
			return celli;
		}
		else
		{
			// Point is not in the nearest cell so search all cells

			for (label celli = 0; celli < nCells(); celli++)
			{
				if (pointInCell(p, celli, decompMode))
				{
					return celli;
				}
			}

			return -1;
		}
	}
}


// ************************************************************************* //