#include <enstrophy.hxx>

#include <fvcCurl.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(enstrophy, 0);

		addToRunTimeSelectionTable
		(
			functionObject,
			enstrophy,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

bool tnbLib::functionObjects::enstrophy::calc()
{
	if (foundObject<volVectorField>(fieldName_))
	{
		return store
		(
			resultName_,
			0.5*magSqr(fvc::curl(lookupObject<volVectorField>(fieldName_)))
		);
	}
	else
	{
		return false;
	}

	return true;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::enstrophy::enstrophy
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

tnbLib::functionObjects::enstrophy::~enstrophy()
{}


// ************************************************************************* //