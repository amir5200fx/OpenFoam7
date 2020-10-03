#include <add.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(add, 0);
		addToRunTimeSelectionTable(functionObject, add, dictionary);
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

bool tnbLib::functionObjects::add::calc()
{
	return calcAllTypes(*this);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::add::add
(
	const word& name,
	const Time& runTime,
	const dictionary& dict
)
	:
	fieldsExpression(name, runTime, dict)
{
	setResultName("add");
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObjects::add::~add()
{}


// ************************************************************************* //