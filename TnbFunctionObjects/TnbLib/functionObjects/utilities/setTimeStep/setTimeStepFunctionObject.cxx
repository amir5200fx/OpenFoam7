#include <setTimeStepFunctionObject.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(setTimeStepFunctionObject, 0);

		addToRunTimeSelectionTable
		(
			functionObject,
			setTimeStepFunctionObject,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::setTimeStepFunctionObject::setTimeStepFunctionObject
(
	const word& name,
	const Time& runTime,
	const dictionary& dict
)
	:
	functionObject(name),
	time_(runTime)
{
	read(dict);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObjects::setTimeStepFunctionObject::~setTimeStepFunctionObject()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::Time&
tnbLib::functionObjects::setTimeStepFunctionObject::time() const
{
	return time_;
}


bool tnbLib::functionObjects::setTimeStepFunctionObject::setTimeStep()
{
	const_cast<Time&>(time()).setDeltaTNoAdjust
	(
		timeStepPtr_().value(time_.timeOutputValue())
	);

	return true;
}


bool tnbLib::functionObjects::setTimeStepFunctionObject::read
(
	const dictionary& dict
)
{
	timeStepPtr_ = Function1<scalar>::New("deltaT", dict);

	return true;
}


bool tnbLib::functionObjects::setTimeStepFunctionObject::execute()
{
	bool adjustTimeStep =
		time().controlDict().lookupOrDefault("adjustTimeStep", false);

	if (!adjustTimeStep)
	{
		return setTimeStep();
	}

	return true;
}


bool tnbLib::functionObjects::setTimeStepFunctionObject::write()
{
	return true;
}


// ************************************************************************* //