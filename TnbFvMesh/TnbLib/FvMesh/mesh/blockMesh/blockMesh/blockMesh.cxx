#include <blockMesh.hxx>

#include <Time.hxx>
#include <IStringStream.hxx>
#include <OStringStream.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineDebugSwitch(blockMesh, 0);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::blockMesh::blockMesh(const IOdictionary& dict, const word& regionName)
	:
	meshDict_(dict),
	verboseOutput(meshDict_.lookupOrDefault<Switch>("verbose", true)),
	checkFaceCorrespondence_
	(
		meshDict_.lookupOrDefault<Switch>("checkFaceCorrespondence", true)
	),
	geometry_
	(
		tnbLib::IOobject
		(
			"geometry",                 // dummy name
			meshDict_.time().constant(),     // instance
			"geometry",                 // local
			meshDict_.time(),                // registry
			tnbLib::IOobject::MUST_READ,
			tnbLib::IOobject::NO_WRITE
		),
		meshDict_.found("geometry")
		? meshDict_.subDict("geometry")
		: dictionary(),
		true
	),
	scaleFactor_(1.0),
	blockVertices_
	(
		meshDict_.lookup("vertices"),
		blockVertex::iNew(meshDict_, geometry_)
	),
	vertices_(tnbLib::vertices(blockVertices_)),
	topologyPtr_(createTopology(meshDict_, regionName))
{
	Switch fastMerge(meshDict_.lookupOrDefault<Switch>("fastMerge", false));

	if (fastMerge)
	{
		calcMergeInfoFast();
	}
	else
	{
		calcMergeInfo();
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::blockMesh::~blockMesh()
{
	delete topologyPtr_;
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::blockMesh::verbose(const bool on)
{
	verboseOutput = on;
}


const tnbLib::pointField& tnbLib::blockMesh::vertices() const
{
	return vertices_;
}


const tnbLib::polyMesh& tnbLib::blockMesh::topology() const
{
	if (!topologyPtr_)
	{
		FatalErrorInFunction
			<< "topologyPtr_ not allocated"
			<< exit(FatalError);
	}

	return *topologyPtr_;
}


tnbLib::PtrList<tnbLib::dictionary> tnbLib::blockMesh::patchDicts() const
{
	const polyPatchList& patchTopologies = topology().boundaryMesh();

	PtrList<dictionary> patchDicts(patchTopologies.size());

	forAll(patchTopologies, patchi)
	{
		OStringStream os;
		patchTopologies[patchi].write(os);
		IStringStream is(os.str());
		patchDicts.set(patchi, new dictionary(is));
	}
	return patchDicts;
}


tnbLib::scalar tnbLib::blockMesh::scaleFactor() const
{
	return scaleFactor_;
}


const tnbLib::pointField& tnbLib::blockMesh::points() const
{
	if (points_.empty())
	{
		createPoints();
	}

	return points_;
}


const tnbLib::cellShapeList& tnbLib::blockMesh::cells() const
{
	if (cells_.empty())
	{
		createCells();
	}

	return cells_;
}


const tnbLib::faceListList& tnbLib::blockMesh::patches() const
{
	if (patches_.empty())
	{
		createPatches();
	}

	return patches_;
}


tnbLib::wordList tnbLib::blockMesh::patchNames() const
{
	return topology().boundaryMesh().names();
}


//tnbLib::wordList tnbLib::blockMesh::patchTypes() const
//{
//    return topology().boundaryMesh().types();
//}
//
//
//tnbLib::wordList tnbLib::blockMesh::patchPhysicalTypes() const
//{
//    return topology().boundaryMesh().physicalTypes();
//}


tnbLib::label tnbLib::blockMesh::numZonedBlocks() const
{
	label num = 0;

	forAll(*this, blocki)
	{
		if (operator[](blocki).zoneName().size())
		{
			num++;
		}
	}

	return num;
}


void tnbLib::blockMesh::writeTopology(Ostream& os) const
{
	const pointField& pts = topology().points();

	forAll(pts, pI)
	{
		const point& pt = pts[pI];

		os << "v " << pt.x() << ' ' << pt.y() << ' ' << pt.z() << endl;
	}

	const edgeList& edges = topology().edges();

	forAll(edges, eI)
	{
		const edge& e = edges[eI];

		os << "l " << e.start() + 1 << ' ' << e.end() + 1 << endl;
	}
}

// ************************************************************************* //