#include <XiReactionRate.hxx>

#include <volFields.hxx>
#include <fvcGrad.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(XiReactionRate, 0);
		addToRunTimeSelectionTable(functionObject, XiReactionRate, dictionary);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::XiReactionRate::XiReactionRate
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

tnbLib::functionObjects::XiReactionRate::~XiReactionRate()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::functionObjects::XiReactionRate::execute()
{
	return true;
}


bool tnbLib::functionObjects::XiReactionRate::write()
{
	const volScalarField& b =
		mesh_.lookupObject<volScalarField>("b");

	const volScalarField& Su =
		mesh_.lookupObject<volScalarField>("Su");

	const volScalarField& Xi =
		mesh_.lookupObject<volScalarField>("Xi");

	volScalarField St
	(
		IOobject
		(
			"St",
			time_.timeName(),
			mesh_
		),
		Xi*Su
	);

	TnbLog << "    Writing turbulent flame-speed field " << St.name()
		<< " to " << time_.timeName() << endl;

	St.write();

	volScalarField wdot
	(
		IOobject
		(
			"wdot",
			time_.timeName(),
			mesh_
		),
		St*mag(fvc::grad(b))
	);

	TnbLog << "    Writing reaction-rate field " << wdot.name()
		<< " to " << time_.timeName() << endl;

	wdot.write();

	return true;
}


// ************************************************************************* //