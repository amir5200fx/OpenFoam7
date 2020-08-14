#include <decompositionModel.hxx>

#include <polyMesh.hxx>
#include <Time.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(decompositionModel, 0);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::decompositionModel::decompositionModel
(
	const polyMesh& mesh,
	const fileName& decompDictFile
)
	:
	MeshObject
	<
	polyMesh,
	tnbLib::UpdateableMeshObject,
	decompositionModel
	>(mesh),
	IOdictionary
	(
		selectIO
		(
			tnbLib::IOobject
			(
				"decomposeParDict",
				mesh.time().system(),
				mesh.local(),
				mesh,
				tnbLib::IOobject::MUST_READ,
				tnbLib::IOobject::NO_WRITE,
				false   // io.registerObject()
			),
			decompDictFile
		)
	)
{}


tnbLib::decompositionModel::decompositionModel
(
	const polyMesh& mesh,
	const dictionary& dict,
	const fileName& decompDictFile
)
	:
	MeshObject
	<
	polyMesh,
	tnbLib::UpdateableMeshObject,
	decompositionModel
	>(mesh),
	IOdictionary
	(
		selectIO
		(
			tnbLib::IOobject
			(
				"decomposeParDict",
				mesh.time().system(),
				mesh.local(),
				mesh,
				(dict.size() ? tnbLib::IOobject::NO_READ : tnbLib::IOobject::MUST_READ),
				tnbLib::IOobject::NO_WRITE,
				false   // io.registerObject()
			),
			decompDictFile
		),
		dict
	)
{}


// * * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * //

const tnbLib::decompositionModel& tnbLib::decompositionModel::New
(
	const polyMesh& mesh,
	const fileName& decompDictFile
)
{
	return
		MeshObject
		<
		polyMesh,
		tnbLib::UpdateableMeshObject,
		decompositionModel
		>::New(mesh, decompDictFile);
}


const tnbLib::decompositionModel& tnbLib::decompositionModel::New
(
	const polyMesh& mesh,
	const dictionary& dict,
	const fileName& decompDictFile
)
{
	return
		MeshObject
		<
		polyMesh,
		tnbLib::UpdateableMeshObject,
		decompositionModel
		>::New(mesh, dict, decompDictFile);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::IOobject tnbLib::decompositionModel::selectIO
(
	const IOobject& io,
	const fileName& f
)
{
	return
		(
			f.size()
			? tnbLib::IOobject        // construct from filePath instead
			(
				fileName(f).toAbsolute(),
				io.db(),
				io.readOpt(),
				io.writeOpt(),
				io.registerObject()
			)
			: io
			);
}


// ************************************************************************* //