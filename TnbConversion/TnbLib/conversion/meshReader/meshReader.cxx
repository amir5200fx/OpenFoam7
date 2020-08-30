#include <meshReader.hxx>

#include <Time.hxx>
#include <polyMesh.hxx>
#include <faceSet.hxx>
#include <emptyPolyPatch.hxx>
#include <cellModeller.hxx>
#include <demandDrivenData.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

const tnbLib::cellModel* tnbLib::meshReader::unknownModel = tnbLib::cellModeller::
lookup
(
	"unknown"
);

const tnbLib::cellModel* tnbLib::meshReader::tetModel = tnbLib::cellModeller::
lookup
(
	"tet"
);

const tnbLib::cellModel* tnbLib::meshReader::pyrModel = tnbLib::cellModeller::
lookup
(
	"pyr"
);

const tnbLib::cellModel* tnbLib::meshReader::prismModel = tnbLib::cellModeller::
lookup
(
	"prism"
);

const tnbLib::cellModel* tnbLib::meshReader::hexModel = tnbLib::cellModeller::
lookup
(
	"hex"
);


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::meshReader::addCellZones(polyMesh& mesh) const
{
	cellTable_.addCellZones(mesh, cellTableId_);
	warnDuplicates("cellZones", mesh.cellZones().names());
}


void tnbLib::meshReader::addFaceZones(polyMesh& mesh) const
{
	label nZone = monitoringSets_.size();
	mesh.faceZones().setSize(nZone);

	if (!nZone)
	{
		return;
	}

	nZone = 0;
	for
		(
			HashTable<List<label>, word, string::hash>::const_iterator
			iter = monitoringSets_.begin();
			iter != monitoringSets_.end();
			++iter
			)
	{
		Info << "faceZone " << nZone
			<< " (size: " << iter().size() << ") name: "
			<< iter.key() << endl;

		mesh.faceZones().set
		(
			nZone,
			new faceZone
			(
				iter.key(),
				iter(),
				List<bool>(iter().size(), false),
				nZone,
				mesh.faceZones()
			)
		);

		nZone++;
	}
	mesh.faceZones().writeOpt() = IOobject::AUTO_WRITE;
	warnDuplicates("faceZones", mesh.faceZones().names());
}


tnbLib::autoPtr<tnbLib::polyMesh> tnbLib::meshReader::mesh
(
	const objectRegistry& registry
)
{
	readGeometry();

	Info << "Creating a polyMesh" << endl;
	createPolyCells();

	Info << "Number of internal faces: " << nInternalFaces_ << endl;

	createPolyBoundary();
	clearExtraStorage();

	autoPtr<polyMesh> mesh
	(
		new polyMesh
		(
			IOobject
			(
				polyMesh::defaultRegion,
				registry.time().constant(),
				registry
			),
			move(points_),
			move(meshFaces_),
			move(cellPolys_)
		)
	);

	// adding patches also checks the mesh
	mesh().addPatches(polyBoundaryPatches(mesh));

	warnDuplicates("boundaries", mesh().boundaryMesh().names());

	addCellZones(mesh());
	addFaceZones(mesh());

	return mesh;
}


void tnbLib::meshReader::writeMesh
(
	const polyMesh& mesh,
	IOstream::streamFormat fmt
) const
{
	mesh.removeFiles();

	Info << "Writing polyMesh" << endl;
	mesh.writeObject
	(
		fmt,
		IOstream::currentVersion,
		IOstream::UNCOMPRESSED,
		true
	);
	writeAux(mesh);
}


void tnbLib::meshReader::clearExtraStorage()
{
	cellFaces_.clear();
	baffleFaces_.clear();
	boundaryIds_.clear();
	baffleIds_.clear();

	deleteDemandDrivenData(pointCellsPtr_);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::meshReader::meshReader
(
	const fileName& fileOrPrefix,
	const scalar scaleFactor
)
	:
	pointCellsPtr_(nullptr),
	nInternalFaces_(0),
	patchStarts_(0),
	patchSizes_(0),
	interfaces_(0),
	baffleIds_(0),
	meshFaces_(0),
	cellPolys_(0),
	geometryFile_(fileOrPrefix),
	scaleFactor_(scaleFactor),
	points_(0),
	origCellId_(0),
	boundaryIds_(0),
	patchTypes_(0),
	patchNames_(0),
	patchPhysicalTypes_(0),
	cellFaces_(0),
	baffleFaces_(0),
	cellTableId_(0),
	cellTable_()
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::meshReader::~meshReader()
{
	deleteDemandDrivenData(pointCellsPtr_);
}


// ************************************************************************* //