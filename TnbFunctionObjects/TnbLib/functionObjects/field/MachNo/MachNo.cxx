#include <MachNo.hxx>

#include <fluidThermo.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(MachNo, 0);

		addToRunTimeSelectionTable
		(
			functionObject,
			MachNo,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

bool tnbLib::functionObjects::MachNo::calc()
{
	if
		(
			foundObject<volVectorField>(fieldName_)
			&& foundObject<fluidThermo>(fluidThermo::dictName)
			)
	{
		const fluidThermo& thermo =
			lookupObject<fluidThermo>(fluidThermo::dictName);

		const volVectorField& U = lookupObject<volVectorField>(fieldName_);

		return store
		(
			resultName_,
			mag(U) / sqrt(thermo.gamma()*thermo.p() / thermo.rho())
		);
	}
	else
	{
		return false;
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::MachNo::MachNo
(
	const word& name,
	const Time& runTime,
	const dictionary& dict
)
	:
	fieldExpression(name, runTime, dict, "U")
{
	setResultName("Ma", "U");
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObjects::MachNo::~MachNo()
{}


// ************************************************************************* //