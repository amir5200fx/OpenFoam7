#include <icoUncoupledKinematicCloud.hxx>

#include <singlePhaseTransportModel.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(icoUncoupledKinematicCloud, 0);
		addToRunTimeSelectionTable
		(
			functionObject,
			icoUncoupledKinematicCloud,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::icoUncoupledKinematicCloud::icoUncoupledKinematicCloud
(
	const word& name,
	const Time& runTime,
	const dictionary& dict
)
	:
	fvMeshFunctionObject(name, runTime, dict),
	g_
	(
		IOobject
		(
			"g",
			time_.constant(),
			mesh_,
			IOobject::READ_IF_PRESENT,
			IOobject::NO_WRITE
		),
		dimensionedVector(dimAcceleration, Zero)
	),
	laminarTransport_
	(
		mesh_.lookupObject<singlePhaseTransportModel>("transportProperties")
	),
	rhoValue_
	(
		"rho",
		dimDensity,
		laminarTransport_
	),
	rho_
	(
		IOobject
		(
			"rho",
			time_.timeName(),
			mesh_
		),
		mesh_,
		rhoValue_
	),
	mu_("mu", rhoValue_*laminarTransport_.nu()),
	U_
	(
		mesh_.lookupObject<volVectorField>(dict.lookupOrDefault<word>("U", "U"))
	),
	kinematicCloudName_
	(
		dict.lookupOrDefault<word>("kinematicCloud", "kinematicCloud")
	),
	kinematicCloud_
	(
		kinematicCloudName_,
		rho_,
		U_,
		mu_,
		g_
	)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObjects::icoUncoupledKinematicCloud::~icoUncoupledKinematicCloud()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::functionObjects::icoUncoupledKinematicCloud::read
(
	const dictionary& dict
)
{
	fvMeshFunctionObject::read(dict);

	return true;
}


bool tnbLib::functionObjects::icoUncoupledKinematicCloud::execute()
{
	mu_ = rhoValue_ * laminarTransport_.nu();
	kinematicCloud_.evolve();

	return true;
}


bool tnbLib::functionObjects::icoUncoupledKinematicCloud::write()
{
	return true;
}


// ************************************************************************* //