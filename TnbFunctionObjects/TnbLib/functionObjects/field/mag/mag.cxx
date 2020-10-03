#include <mag.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(mag, 0);
		addToRunTimeSelectionTable(functionObject, mag, dictionary);
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

bool tnbLib::functionObjects::mag::calc()
{
	bool processed = false;

	processed = processed || calcMag<scalar>();
	processed = processed || calcMag<vector>();
	processed = processed || calcMag<sphericalTensor>();
	processed = processed || calcMag<symmTensor>();
	processed = processed || calcMag<tensor>();

	return processed;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::mag::mag
(
	const word& name,
	const Time& runTime,
	const dictionary& dict
)
	:
	fieldExpression(name, runTime, dict)
{
	read(dict);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObjects::mag::~mag()
{}


// ************************************************************************* //