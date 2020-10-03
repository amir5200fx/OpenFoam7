#include <processorField.hxx>

#include <volFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(processorField, 0);
		addToRunTimeSelectionTable(functionObject, processorField, dictionary);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::processorField::processorField
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

tnbLib::functionObjects::processorField::~processorField()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::functionObjects::processorField::read(const dictionary& dict)
{
	fvMeshFunctionObject::read(dict);

	return true;
}


bool tnbLib::functionObjects::processorField::execute()
{
	word name("processorID");

	tmp<volScalarField> tprocField
	(
		volScalarField::New
		(
			name,
			mesh_,
			dimensionedScalar(name, dimless, Pstream::myProcNo())
		)
	);

	return store(name, tprocField);
}


bool tnbLib::functionObjects::processorField::write()
{
	mesh_.lookupObject<volScalarField>("processorID").write();

	return true;
}


// ************************************************************************* //