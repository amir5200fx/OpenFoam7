#include <log.hxx>

#include <volFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(log, 0);

		addToRunTimeSelectionTable
		(
			functionObject,
			log,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

bool tnbLib::functionObjects::log::calc()
{
	if (foundObject<volScalarField>(fieldName_))
	{
		const volScalarField& x = lookupObject<volScalarField>(fieldName_);

		return store
		(
			resultName_,
			tnbLib::log(max(x, clip_))
		);
	}
	else
	{
		return false;
	}

	return true;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::log::log
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

tnbLib::functionObjects::log::~log()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::functionObjects::log::read(const dictionary& dict)
{
	fieldExpression::read(dict);

	if (resultName_.empty())
	{
		resultName_ = "log(" + fieldName_ + ")";
	}

	clip_ = dict.lookupOrDefault<scalar>("clip", 0);

	return true;
}


// ************************************************************************* //