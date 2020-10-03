#include <blendingFactor.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <dictionary.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(blendingFactor, 0);
		addToRunTimeSelectionTable(functionObject, blendingFactor, dictionary);
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

bool tnbLib::functionObjects::blendingFactor::calc()
{
	bool processed = false;

	processed = processed || calcBF<scalar>();
	processed = processed || calcBF<vector>();

	return processed;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::blendingFactor::blendingFactor
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

tnbLib::functionObjects::blendingFactor::~blendingFactor()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::functionObjects::blendingFactor::read(const dictionary& dict)
{
	fieldExpression::read(dict);

	phiName_ = dict.lookupOrDefault<word>("phi", "phi");

	resultName_ = "blendingFactor:" + fieldName_;

	return true;
}


// ************************************************************************* //