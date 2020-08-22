#include <dynamicFvMesh.hxx>

#include <volFields.hxx>
#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(dynamicFvMesh, 0);
	defineRunTimeSelectionTable(dynamicFvMesh, IOobject);
}


// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

tnbLib::IOobject tnbLib::dynamicFvMesh::dynamicMeshDictIOobject(const IOobject& io)
{
	// defaultRegion (region0) gets loaded from constant, other ones get loaded
	// from constant/<regionname>. Normally we'd use polyMesh::dbDir() but we
	// haven't got a polyMesh yet ...
	return tnbLib::IOobject
	(
		"dynamicMeshDict",
		io.time().constant(),
		(io.name() == polyMesh::defaultRegion ? "" : io.name()),
		io.db(),
		tnbLib::IOobject::READ_IF_PRESENT,
		tnbLib::IOobject::NO_WRITE,
		false
	);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::dynamicFvMesh::dynamicFvMesh(const IOobject& io)
	:
	fvMesh(io),
	dynamicMeshDict_(tnbLib::IOdictionary(dynamicMeshDictIOobject(io)))
{}


tnbLib::dynamicFvMesh::dynamicFvMesh
(
	const IOobject& io,
	pointField&& points,
	faceList&& faces,
	labelList&& allOwner,
	labelList&& allNeighbour,
	const bool syncPar
)
	:
	fvMesh
	(
		io,
		move(points),
		move(faces),
		move(allOwner),
		move(allNeighbour),
		syncPar
	),
	dynamicMeshDict_(tnbLib::IOdictionary(dynamicMeshDictIOobject(io)))
{}


tnbLib::dynamicFvMesh::dynamicFvMesh
(
	const IOobject& io,
	pointField&& points,
	faceList&& faces,
	cellList&& cells,
	const bool syncPar
)
	:
	fvMesh
	(
		io,
		move(points),
		move(faces),
		move(cells),
		syncPar
	),
	dynamicMeshDict_(tnbLib::IOdictionary(dynamicMeshDictIOobject(io)))
{}


tnbLib::dynamicFvMesh::velocityMotionCorrection::velocityMotionCorrection
(
	const dynamicFvMesh& mesh,
	const dictionary& dict
)
	:
	mesh_(mesh),
	velocityFields_(dict.lookupOrDefault("velocityFields", wordList()))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::dynamicFvMesh::~dynamicFvMesh()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::dynamicFvMesh::velocityMotionCorrection::update() const
{
	forAll(velocityFields_, i)
	{
		if (mesh_.foundObject<volVectorField>(velocityFields_[i]))
		{
			mesh_.lookupObjectRef<volVectorField>
				(
					velocityFields_[i]
					).correctBoundaryConditions();
		}
	}
}

// ************************************************************************* //