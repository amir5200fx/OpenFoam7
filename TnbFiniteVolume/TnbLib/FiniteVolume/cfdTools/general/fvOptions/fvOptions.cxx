#include <fvOptions.hxx>

#include <fvMesh.hxx>
#include <Time.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fv
	{
		defineTypeNameAndDebug(options, 0);
	}
}


// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

tnbLib::IOobject tnbLib::fv::options::createIOobject
(
	const fvMesh& mesh
) const
{
	IOobject io
	(
		typeName,
		mesh.time().constant(),
		mesh,
		IOobject::MUST_READ,
		IOobject::NO_WRITE
	);

	if (io.typeHeaderOk<IOdictionary>(true))
	{
		Info << "Creating finite volume options from "
			<< io.instance() / io.name() << nl
			<< endl;

		io.readOpt() = IOobject::MUST_READ_IF_MODIFIED;
		return io;
	}
	else
	{
		// Check if the fvOptions file is in system
		io.instance() = mesh.time().system();

		if (io.typeHeaderOk<IOdictionary>(true))
		{
			Info << "Creating finite volume options from "
				<< io.instance() / io.name() << nl
				<< endl;

			io.readOpt() = IOobject::MUST_READ_IF_MODIFIED;
			return io;
		}
		else
		{
			io.readOpt() = IOobject::NO_READ;
			return io;
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fv::options::options
(
	const fvMesh& mesh
)
	:
	IOdictionary(createIOobject(mesh)),
	optionList(mesh, *this)
{}


tnbLib::fv::options& tnbLib::fv::options::New(const fvMesh& mesh)
{
	if (mesh.thisDb().foundObject<options>(typeName))
	{
		return const_cast<options&>
			(
				mesh.lookupObject<options>(typeName)
				);
	}
	else
	{
		if (debug)
		{
			InfoInFunction
				<< "Constructing " << typeName
				<< " for region " << mesh.name() << endl;
		}

		options* objectPtr = new options(mesh);
		regIOobject::store(objectPtr);
		return *objectPtr;
	}
}


bool tnbLib::fv::options::read()
{
	if (IOdictionary::regIOobject::read())
	{
		optionList::read(*this);
		return true;
	}
	else
	{
		return false;
	}
}


// ************************************************************************* //