#include <scale.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <dictionary.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(scale, 0);
		addToRunTimeSelectionTable(functionObject, scale, dictionary);
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

bool tnbLib::functionObjects::scale::calc()
{
	bool processed = false;

	processed = processed || calcScale<scalar>();
	processed = processed || calcScale<vector>();
	processed = processed || calcScale<sphericalTensor>();
	processed = processed || calcScale<symmTensor>();
	processed = processed || calcScale<tensor>();

	return processed;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::scale::scale
(
	const word& name,
	const Time& runTime,
	const dictionary& dict
)
	:
	fieldExpression(name, runTime, dict),
	scale_(0)
{
	read(dict);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObjects::scale::~scale()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::functionObjects::scale::read(const dictionary& dict)
{
	fieldExpression::read(dict);

	if (resultName_.empty())
	{
		resultName_ = "scale(" + fieldName_ + ")";
	}

	dict.lookup("scale") >> scale_;

	return true;
}


// ************************************************************************* //