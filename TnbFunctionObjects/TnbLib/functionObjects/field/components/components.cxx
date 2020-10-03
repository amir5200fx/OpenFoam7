#include <components.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(components, 0);
		addToRunTimeSelectionTable(functionObject, components, dictionary);
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

bool tnbLib::functionObjects::components::calc()
{
	bool processed = false;

	processed = processed || calcComponents<vector>();
	processed = processed || calcComponents<sphericalTensor>();
	processed = processed || calcComponents<symmTensor>();
	processed = processed || calcComponents<tensor>();

	return processed;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::components::components
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

tnbLib::functionObjects::components::~components()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::functionObjects::components::write()
{
	bool written = true;

	forAll(resultNames_, i)
	{
		written = written && writeObject(resultNames_[i]);
	}

	return written;
}


bool tnbLib::functionObjects::components::clear()
{
	bool cleared = true;

	forAll(resultNames_, i)
	{
		cleared = cleared && clearObject(resultNames_[i]);
	}

	return cleared;
}


// ************************************************************************* //