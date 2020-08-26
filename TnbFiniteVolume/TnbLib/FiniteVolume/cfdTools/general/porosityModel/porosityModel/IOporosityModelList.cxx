#include <IOporosityModelList.hxx>

#include <fvMesh.hxx>
#include <Time.hxx>

// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

tnbLib::IOobject tnbLib::IOporosityModelList::createIOobject
(
	const fvMesh& mesh
) const
{
	IOobject io
	(
		"porosityProperties",
		mesh.time().constant(),
		mesh,
		IOobject::MUST_READ,
		IOobject::NO_WRITE
	);

	if (io.typeHeaderOk<IOdictionary>(true))
	{
		Info << "Creating porosity model list from " << io.name() << nl << endl;

		io.readOpt() = IOobject::MUST_READ_IF_MODIFIED;
		return io;
	}
	else
	{
		Info << "No porosity models present" << nl << endl;

		io.readOpt() = IOobject::NO_READ;
		return io;
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::IOporosityModelList::IOporosityModelList
(
	const fvMesh& mesh
)
	:
	IOdictionary(createIOobject(mesh)),
	porosityModelList(mesh, *this)
{}


bool tnbLib::IOporosityModelList::read()
{
	if (regIOobject::read())
	{
		porosityModelList::read(*this);
		return true;
	}
	else
	{
		return false;
	}
}


// ************************************************************************* //