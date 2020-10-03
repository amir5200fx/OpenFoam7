#include <turbulenceIntensity.hxx>

#include <turbulenceModel.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(turbulenceIntensity, 0);

		addToRunTimeSelectionTable
		(
			functionObject,
			turbulenceIntensity,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::functionObjects::turbulenceIntensity::writeFileHeader(const label i)
{
	writeHeader(file(), "I ()");
	writeCommented(file(), "Time");
	writeTabbed(file(), "min");
	writeTabbed(file(), "max");
	writeTabbed(file(), "average");
	file() << endl;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::turbulenceIntensity::turbulenceIntensity
(
	const word& name,
	const Time& runTime,
	const dictionary& dict
)
	:
	fvMeshFunctionObject(name, runTime, dict),
	logFiles(obr_, name),
	writeLocalObjects(obr_, log)
{
	read(dict);
	resetName(typeName);
	resetLocalObjectName("I");
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObjects::turbulenceIntensity::~turbulenceIntensity()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::functionObjects::turbulenceIntensity::read(const dictionary& dict)
{
	fvMeshFunctionObject::read(dict);
	writeLocalObjects::read(dict);

	return true;
}


bool tnbLib::functionObjects::turbulenceIntensity::execute()
{
	if (mesh_.foundObject<turbulenceModel>(turbulenceModel::propertiesName))
	{
		const turbulenceModel& turbModel = mesh_.lookupObject<turbulenceModel>
			(
				turbulenceModel::propertiesName
				);

		volScalarField uPrime(sqrt((2.0 / 3.0)*turbModel.k()));

		word name("I");

		return
			store
			(
				name,
				uPrime
				/ max
				(
					max(uPrime, mag(turbModel.U())),
					dimensionedScalar(dimVelocity, small)
				)
			);
	}
	else
	{
		FatalErrorInFunction
			<< "Unable to find turbulence model in the "
			<< "database" << exit(FatalError);

		return false;
	}
}


bool tnbLib::functionObjects::turbulenceIntensity::write()
{
	TnbLog << type() << " " << name() << " write:" << nl;

	writeLocalObjects::write();

	logFiles::write();

	const volScalarField& turbulenceIntensity =
		mesh_.lookupObject<volScalarField>("I");

	const scalar minTurbulenceIntensity = min(turbulenceIntensity).value();
	const scalar maxTurbulenceIntensity = max(turbulenceIntensity).value();
	const scalar avgTurbulenceIntensity = turbulenceIntensity.average().value();

	if (Pstream::master())
	{
		TnbLog << "    I : min = " << minTurbulenceIntensity
			<< ", max = " << maxTurbulenceIntensity
			<< ", average = " << avgTurbulenceIntensity << nl;

		writeTime(file());
		file()
			<< tab << minTurbulenceIntensity
			<< tab << maxTurbulenceIntensity
			<< tab << avgTurbulenceIntensity
			<< endl;
	}

	TnbLog << endl;

	return true;
}


// ************************************************************************* //