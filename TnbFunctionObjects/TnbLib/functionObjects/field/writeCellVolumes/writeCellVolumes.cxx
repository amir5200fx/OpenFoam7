#include <writeCellVolumes.hxx>

#include <volFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(writeCellVolumes, 0);
		addToRunTimeSelectionTable(functionObject, writeCellVolumes, dictionary);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::writeCellVolumes::writeCellVolumes
(
	const word& name,
	const Time& runTime,
	const dictionary& dict
)
	:
	fvMeshFunctionObject(name, runTime, dict)
{
	read(dict);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObjects::writeCellVolumes::~writeCellVolumes()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::functionObjects::writeCellVolumes::execute()
{
	return true;
}


bool tnbLib::functionObjects::writeCellVolumes::write()
{
	volScalarField V
	(
		tnbLib::IOobject
		(
			mesh_.V().name(),
			time_.timeName(),
			mesh_,
			tnbLib::IOobject::NO_READ,
			tnbLib::IOobject::NO_WRITE,
			false
		),
		mesh_,
		dimensionedScalar(mesh_.V().name(), mesh_.V().dimensions(), 0),
		calculatedFvPatchField<scalar>::typeName
	);

	V.ref() = mesh_.V();

	TnbLog << "    Writing cell-volumes field " << V.name()
		<< " to " << time_.timeName() << endl;

	V.write();

	return true;
}


// ************************************************************************* //