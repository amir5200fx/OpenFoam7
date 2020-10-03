#include <ddt.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(ddt, 0);
		addToRunTimeSelectionTable(functionObject, ddt, dictionary);
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

bool tnbLib::functionObjects::ddt::calc()
{
	if (functionObject::postProcess)
	{
		WarningInFunction
			<< "ddt is not supported with the postProcess utility"
			<< endl;

		return false;
	}

	bool processed = false;

	processed = processed || calcDdt<scalar>();
	processed = processed || calcDdt<vector>();
	processed = processed || calcDdt<sphericalTensor>();
	processed = processed || calcDdt<symmTensor>();
	processed = processed || calcDdt<tensor>();

	return processed;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::ddt::ddt
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

tnbLib::functionObjects::ddt::~ddt()
{}


// ************************************************************************* //