#include <processorMeshes.hxx>

#include <Time.hxx>
#include <primitiveMesh.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::processorMeshes::read()
{
	// Make sure to clear (and hence unregister) any previously loaded meshes
	// and fields
	forAll(databases_, proci)
	{
		boundaryProcAddressing_.set(proci, nullptr);
		cellProcAddressing_.set(proci, nullptr);
		faceProcAddressing_.set(proci, nullptr);
		pointProcAddressing_.set(proci, nullptr);
		meshes_.set(proci, nullptr);
	}

	forAll(databases_, proci)
	{
		meshes_.set
		(
			proci,
			new fvMesh
			(
				IOobject
				(
					meshName_,
					databases_[proci].timeName(),
					databases_[proci]
				)
			)
		);

		pointProcAddressing_.set
		(
			proci,
			new labelIOList
			(
				IOobject
				(
					"pointProcAddressing",
					meshes_[proci].facesInstance(),
					meshes_[proci].meshSubDir,
					meshes_[proci],
					IOobject::MUST_READ,
					IOobject::NO_WRITE
				)
			)
		);

		faceProcAddressing_.set
		(
			proci,
			new labelIOList
			(
				IOobject
				(
					"faceProcAddressing",
					meshes_[proci].facesInstance(),
					meshes_[proci].meshSubDir,
					meshes_[proci],
					IOobject::MUST_READ,
					IOobject::NO_WRITE
				)
			)
		);

		cellProcAddressing_.set
		(
			proci,
			new labelIOList
			(
				IOobject
				(
					"cellProcAddressing",
					meshes_[proci].facesInstance(),
					meshes_[proci].meshSubDir,
					meshes_[proci],
					IOobject::MUST_READ,
					IOobject::NO_WRITE
				)
			)
		);

		boundaryProcAddressing_.set
		(
			proci,
			new labelIOList
			(
				IOobject
				(
					"boundaryProcAddressing",
					meshes_[proci].facesInstance(),
					meshes_[proci].meshSubDir,
					meshes_[proci],
					IOobject::MUST_READ,
					IOobject::NO_WRITE
				)
			)
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::processorMeshes::processorMeshes
(
	PtrList<Time>& databases,
	const word& meshName
)
	:
	meshName_(meshName),
	databases_(databases),
	meshes_(databases.size()),
	pointProcAddressing_(databases.size()),
	faceProcAddressing_(databases.size()),
	cellProcAddressing_(databases.size()),
	boundaryProcAddressing_(databases.size())
{
	read();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::fvMesh::readUpdateState tnbLib::processorMeshes::readUpdate()
{
	fvMesh::readUpdateState stat = fvMesh::UNCHANGED;

	forAll(databases_, proci)
	{
		// Check if any new meshes need to be read.
		fvMesh::readUpdateState procStat = meshes_[proci].readUpdate();

		/*
		if (procStat != fvMesh::UNCHANGED)
		{
			Info<< "Processor " << proci
				<< " at time " << databases_[proci].timeName()
				<< " detected mesh change " << procStat
				<< endl;
		}
		*/

		// Combine into overall mesh change status
		if (stat == fvMesh::UNCHANGED)
		{
			stat = procStat;
		}
		else if (stat != procStat)
		{
			FatalErrorInFunction
				<< "Processor " << proci
				<< " has a different polyMesh at time "
				<< databases_[proci].timeName()
				<< " compared to any previous processors." << nl
				<< "Please check time " << databases_[proci].timeName()
				<< " directories on all processors for consistent"
				<< " mesh files."
				<< exit(FatalError);
		}
	}

	if
		(
			stat == fvMesh::TOPO_CHANGE
			|| stat == fvMesh::TOPO_PATCH_CHANGE
			)
	{
		// Reread all meshes and addressing
		read();
	}
	return stat;
}


void tnbLib::processorMeshes::reconstructPoints(fvMesh& mesh)
{
	// Read the field for all the processors
	PtrList<pointIOField> procsPoints(meshes_.size());

	forAll(meshes_, proci)
	{
		procsPoints.set
		(
			proci,
			new pointIOField
			(
				IOobject
				(
					"points",
					meshes_[proci].time().timeName(),
					polyMesh::meshSubDir,
					meshes_[proci],
					IOobject::MUST_READ,
					IOobject::NO_WRITE,
					false
				)
			)
		);
	}

	// Create the new points
	vectorField newPoints(mesh.nPoints());

	forAll(meshes_, proci)
	{
		const vectorField& procPoints = procsPoints[proci];

		// Set the cell values in the reconstructed field

		const labelList& pointProcAddressingI = pointProcAddressing_[proci];

		if (pointProcAddressingI.size() != procPoints.size())
		{
			FatalErrorInFunction
				<< "problem :"
				<< " pointProcAddressingI:" << pointProcAddressingI.size()
				<< " procPoints:" << procPoints.size()
				<< abort(FatalError);
		}

		forAll(pointProcAddressingI, pointi)
		{
			newPoints[pointProcAddressingI[pointi]] = procPoints[pointi];
		}
	}

	mesh.movePoints(newPoints);
	mesh.moving(false);
	mesh.write();
}


// ************************************************************************* //