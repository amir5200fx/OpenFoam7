#include <surfMesh.hxx>

#include <Time.hxx>
#include <OSspecific.hxx>
#include <MeshedSurface.hxx>
#include <demandDrivenData.hxx>

#include <MeshedSurfaceProxy.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(surfMesh, 0);
}


tnbLib::word tnbLib::surfMesh::meshSubDir = "surfMesh";

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

// void tnbLib::surfMesh::oneZone()
// {
//     word zoneName;
//
//     surfZoneList& zones = Allocator::storedIOZones();
//     if (zones.size())
//     {
//         zoneName = zones[0].name();
//     }
//     if (zoneName.empty())
//     {
//         zoneName = "zone0";
//     }
//
//     // set single default zone
//     zones.setSize(1);
//     zones[0] = surfZone
//     (
//         zoneName,
//         nFaces(),       // zone size
//         0,              // zone start
//         0               // zone index
//     );
// }


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void tnbLib::surfMesh::updatePointsRef()
{
	// Assign the reference to the points (this is truly ugly)
	reinterpret_cast<SubField<point>&>
		(
			const_cast<Field<point>&>(MeshReference::points())
			) = reinterpret_cast<SubField<point>&>(this->storedPoints());
}


void tnbLib::surfMesh::updateFacesRef()
{
	// Assign the reference to the faces
	shallowCopy(this->storedFaces());
}


void tnbLib::surfMesh::updateRefs()
{
	this->updatePointsRef();
	this->updateFacesRef();
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::surfMesh::surfMesh(const IOobject& io, const word& surfName)
	:
	surfaceRegistry(io.db(), (surfName.size() ? surfName : io.name())),
	Allocator
	(
		IOobject
		(
			"points",
			time().findInstance(meshDir(), "points"),
			meshSubDir,
			*this,
			IOobject::MUST_READ,
			IOobject::NO_WRITE
		),
		IOobject
		(
			"faces",
			time().findInstance(meshDir(), "faces"),
			meshSubDir,
			*this,
			IOobject::MUST_READ,
			IOobject::NO_WRITE
		),
		IOobject
		(
			"surfZones",
			time().findInstance(meshDir(), "surfZones"),
			meshSubDir,
			*this,
			IOobject::MUST_READ,
			IOobject::NO_WRITE
		)
	),
	MeshReference(this->storedIOFaces(), this->storedIOPoints())
{}


tnbLib::surfMesh::surfMesh
(
	const IOobject& io,
	pointField&& pointLst,
	faceList&& faceLst,
	const word& surfName
)
	:
	surfaceRegistry(io.db(), (surfName.size() ? surfName : io.name())),
	Allocator
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
		move(pointLst),
		IOobject
		(
			"faces",
			instance(),
			meshSubDir,
			*this,
			IOobject::NO_READ,
			IOobject::AUTO_WRITE
		),
		move(faceLst),
		IOobject
		(
			"surfZones",
			instance(),
			meshSubDir,
			*this,
			IOobject::NO_READ,
			IOobject::AUTO_WRITE
		),
		surfZoneList()
	),
	MeshReference(this->storedIOFaces(), this->storedIOPoints())
{}


tnbLib::surfMesh::surfMesh
(
	const IOobject& io,
	MeshedSurface<face>&& surf,
	const word& surfName
)
	:
	surfaceRegistry(io.db(), (surfName.size() ? surfName : io.name())),
	Allocator
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
		pointField(),
		IOobject
		(
			"faces",
			instance(),
			meshSubDir,
			*this,
			IOobject::NO_READ,
			IOobject::AUTO_WRITE
		),
		faceList(),
		IOobject
		(
			"surfZones",
			instance(),
			meshSubDir,
			*this,
			IOobject::NO_READ,
			IOobject::AUTO_WRITE
		),
		surfZoneList()
	),
	MeshReference(this->storedIOFaces(), this->storedIOPoints())
{
	if (debug)
	{
		Info << "IOobject: " << io.path() << nl
			<< " name: " << io.name()
			<< " instance: " << io.instance()
			<< " local: " << io.local()
			<< " dbDir: " << io.db().dbDir() << endl;
		Info << "creating surfMesh at instance " << instance() << endl;
		Info << "timeName: " << instance() << endl;
	}

	// We can also send null just to initialize without allocating
	if (notNull(surf))
	{
		transfer(surf);
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::surfMesh::~surfMesh()
{
	// clearOut();
	// resetMotion();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::surfMesh::resetPrimitives
(
	pointField&& points,
	faceList&& faces,
	surfZoneList&& zones,
	const bool validate
)
{
	// Clear addressing.
	MeshReference::clearGeom();

	Allocator::reset(move(points), move(faces), move(zones));
	this->updateRefs();

	if (validate)
	{
		checkZones();
	}
}


void tnbLib::surfMesh::transfer
(
	MeshedSurface<face>& surf
)
{
	// Clear addressing.
	MeshReference::clearGeom();

	this->storedIOPoints().transfer(surf.storedPoints());
	this->storedIOFaces().transfer(surf.storedFaces());
	this->storedIOZones().transfer(surf.storedZones());

	this->updateRefs();
}


tnbLib::fileName tnbLib::surfMesh::meshDir() const
{
	return dbDir() / meshSubDir;
}


const tnbLib::fileName& tnbLib::surfMesh::pointsInstance() const
{
	return this->storedIOPoints().instance();
}


const tnbLib::fileName& tnbLib::surfMesh::facesInstance() const
{
	return this->storedIOFaces().instance();
}


tnbLib::label tnbLib::surfMesh::nPoints() const
{
	return this->points().size();
}


tnbLib::label tnbLib::surfMesh::nFaces() const
{
	return this->faces().size();
}


const tnbLib::pointField& tnbLib::surfMesh::points() const
{
	return this->storedIOPoints();
}


const tnbLib::faceList& tnbLib::surfMesh::faces() const
{
	return this->storedIOFaces();
}


void tnbLib::surfMesh::checkZones()
{
	// extra safety, ensure we have at some zones
	// and they cover all the faces - fix start silently
	surfZoneList& zones = Allocator::storedIOZones();

	if (zones.size() <= 1)
	{
		removeZones();
	}
	else
	{
		label count = 0;
		forAll(zones, zoneI)
		{
			zones[zoneI].start() = count;
			count += zones[zoneI].size();
		}

		if (count < nFaces())
		{
			WarningInFunction
				<< "more faces " << nFaces() << " than zones " << count
				<< " ... extending final zone"
				<< endl;

			zones.last().size() += count - nFaces();
		}
		else if (count > size())
		{
			FatalErrorInFunction
				<< "more zones " << count << " than faces " << nFaces()
				<< exit(FatalError);
		}
	}
}


// Add boundary patches. Constructor helper
void tnbLib::surfMesh::addZones
(
	const surfZoneList& srfZones,
	const bool validate
)
{
	surfZoneList& zones = Allocator::storedIOZones();

	forAll(zones, zoneI)
	{
		zones[zoneI] = surfZone(srfZones[zoneI], zoneI);
	}

	if (validate)
	{
		checkZones();
	}
}


// Remove all files and some subdirs (eg, sets)
void tnbLib::surfMesh::removeFiles(const fileName& instanceDir) const
{
	fileName meshFilesPath = db().path() / instanceDir / meshSubDir;

	rm(meshFilesPath / "points");
	rm(meshFilesPath / "faces");
	rm(meshFilesPath / "surfZones");
}

void tnbLib::surfMesh::removeFiles() const
{
	removeFiles(instance());
}


void tnbLib::surfMesh::write(const fileName& name, const surfMesh& surf)
{
	MeshedSurfaceProxy<face>
		(
			surf.points(),
			surf.faces(),
			surf.surfZones()
			).write(name);
}


void tnbLib::surfMesh::write(const fileName& name)
{
	write(name, *this);
}


// ************************************************************************* //