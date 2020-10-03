#include <magSqr.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(magSqr, 0);
		addToRunTimeSelectionTable(functionObject, magSqr, dictionary);
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

bool tnbLib::functionObjects::magSqr::calc()
{
	bool processed = false;

	processed = processed || calcMagSqr<scalar>();
	processed = processed || calcMagSqr<vector>();
	processed = processed || calcMagSqr<sphericalTensor>();
	processed = processed || calcMagSqr<symmTensor>();
	processed = processed || calcMagSqr<tensor>();

	return processed;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::magSqr::magSqr
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

tnbLib::functionObjects::magSqr::~magSqr()
{}


// ************************************************************************* //