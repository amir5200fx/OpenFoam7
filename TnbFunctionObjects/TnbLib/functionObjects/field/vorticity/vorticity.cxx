#include <vorticity.hxx>

#include <fvcCurl.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(vorticity, 0);

		addToRunTimeSelectionTable
		(
			functionObject,
			vorticity,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

bool tnbLib::functionObjects::vorticity::calc()
{
	if (foundObject<volVectorField>(fieldName_))
	{
		return store
		(
			resultName_,
			fvc::curl(lookupObject<volVectorField>(fieldName_))
		);
	}
	else
	{
		return false;
	}

	return true;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::vorticity::vorticity
(
	const word& name,
	const Time& runTime,
	const dictionary& dict
)
	:
	fieldExpression(name, runTime, dict, "U")
{
	setResultName(typeName, "U");
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObjects::vorticity::~vorticity()
{}


// ************************************************************************* //