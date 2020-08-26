#include <IOMRFZoneList.hxx>

#include <fvMesh.hxx>
#include <Time.hxx>

// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

tnbLib::IOobject tnbLib::IOMRFZoneList::createIOobject
(
	const fvMesh& mesh
) const
{
	IOobject io
	(
		"MRFProperties",
		mesh.time().constant(),
		mesh,
		IOobject::MUST_READ,
		IOobject::NO_WRITE
	);

	if (io.typeHeaderOk<IOdictionary>(true))
	{
		Info << "Creating MRF zone list from " << io.name() << endl;

		io.readOpt() = IOobject::MUST_READ_IF_MODIFIED;
		return io;
	}
	else
	{
		Info << "No MRF models present" << nl << endl;

		io.readOpt() = IOobject::NO_READ;
		return io;
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::IOMRFZoneList::IOMRFZoneList
(
	const fvMesh& mesh
)
	:
	IOdictionary(createIOobject(mesh)),
	MRFZoneList(mesh, *this)
{}


bool tnbLib::IOMRFZoneList::read()
{
	if (regIOobject::read())
	{
		MRFZoneList::read(*this);
		return true;
	}
	else
	{
		return false;
	}
}


// ************************************************************************* //