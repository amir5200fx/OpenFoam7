#include <subtract.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(subtract, 0);
		addToRunTimeSelectionTable(functionObject, subtract, dictionary);
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

bool tnbLib::functionObjects::subtract::calc()
{
	return calcAllTypes(*this);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::subtract::subtract
(
	const word& name,
	const Time& runTime,
	const dictionary& dict
)
	:
	fieldsExpression(name, runTime, dict)
{
	setResultName("subtract");
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObjects::subtract::~subtract()
{}


// ************************************************************************* //