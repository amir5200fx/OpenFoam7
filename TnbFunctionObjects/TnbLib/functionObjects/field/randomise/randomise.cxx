#include <randomise.hxx>

#include <randomise.hxx>
#include <addToRunTimeSelectionTable.hxx>

#include <dictionary.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(randomise, 0);
		addToRunTimeSelectionTable(functionObject, randomise, dictionary);
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

bool tnbLib::functionObjects::randomise::calc()
{
	bool processed = false;

	processed = processed || calcRandomised<scalar>();
	processed = processed || calcRandomised<vector>();
	processed = processed || calcRandomised<sphericalTensor>();
	processed = processed || calcRandomised<symmTensor>();
	processed = processed || calcRandomised<tensor>();

	return processed;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::randomise::randomise
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

tnbLib::functionObjects::randomise::~randomise()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::functionObjects::randomise::read(const dictionary& dict)
{
	fieldExpression::read(dict);

	dict.lookup("magPerturbation") >> magPerturbation_;

	return true;
}


// ************************************************************************* //