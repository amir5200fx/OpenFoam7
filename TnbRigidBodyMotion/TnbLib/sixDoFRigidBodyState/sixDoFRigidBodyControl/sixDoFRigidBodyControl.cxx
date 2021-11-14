#include <sixDoFRigidBodyControl.hxx>

#include <Time.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(sixDoFRigidBodyControl, 0);

		addToRunTimeSelectionTable
		(
			functionObject,
			sixDoFRigidBodyControl,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::sixDoFRigidBodyControl::sixDoFRigidBodyControl
(
	const word& name,
	const Time& runTime,
	const dictionary& dict
)
	:
	sixDoFRigidBodyState(name, runTime, dict),
	time_(runTime),
	meanVelocity_(Zero),
	meanAngularVelocity_(Zero)
{
	read(dict);
	resetName(typeName);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObjects::sixDoFRigidBodyControl::~sixDoFRigidBodyControl()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::functionObjects::sixDoFRigidBodyControl::read(const dictionary& dict)
{
	sixDoFRigidBodyState::read(dict);

	dict.lookup("window") >> w_;
	dict.lookup("convergedVelocity") >> convergedVelocity_;
	dict.lookup("convergedAngularVelocity") >> convergedAngularVelocity_;

	return true;
}


bool tnbLib::functionObjects::sixDoFRigidBodyControl::execute()
{
	if (time_.timeIndex() <= time_.startTimeIndex() + 1)
	{
		meanVelocity_ = cmptMag(velocity());
		meanAngularVelocity_ = cmptMag(angularVelocity());
	}
	else
	{
		const scalar dt = time_.deltaTValue();
		const scalar beta = min(dt / w_, 1);

		meanVelocity_ = (1 - beta)*meanVelocity_ + beta * cmptMag(velocity());

		meanAngularVelocity_ =
			(1 - beta)*meanAngularVelocity_ + beta * cmptMag(angularVelocity());
	}

	if
		(
			time_.value() - time_.startTime().value() > w_
			&& meanVelocity_ < convergedVelocity_
			&& meanAngularVelocity_ < convergedAngularVelocity_
			)
	{
		time_.stopAt(Time::stopAtControl::writeNow);
	}

	return true;
}


// ************************************************************************* //