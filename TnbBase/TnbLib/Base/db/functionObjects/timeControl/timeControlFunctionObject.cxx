#include <timeControlFunctionObject.hxx>

#include <polyMesh.hxx>
#include <mapPolyMesh.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(timeControl, 0);
	}
}


// * * * * * * * * * * * * * * * Private Members * * * * * * * * * * * * * * //

void tnbLib::functionObjects::timeControl::readControls()
{
	if (!dict_.readIfPresent("startTime", startTime_))
	{
		dict_.readIfPresent("timeStart", startTime_);
	}

	if (!dict_.readIfPresent("endTime", endTime_))
	{
		dict_.readIfPresent("timeEnd", endTime_);
	}

	dict_.readIfPresent("nStepsToStartTimeChange", nStepsToStartTimeChange_);
}


bool tnbLib::functionObjects::timeControl::active() const
{
	return
		time_.value() >= startTime_
		&& time_.value() <= endTime_;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::timeControl::timeControl
(
	const word& name,
	const Time& t,
	const dictionary& dict
)
	:
	functionObject(name),
	time_(t),
	dict_(dict),
	startTime_(-vGreat),
	endTime_(vGreat),
	nStepsToStartTimeChange_
	(
		dict.lookupOrDefault("nStepsToStartTimeChange", 3)
	),
	executeControl_(t, dict, "execute"),
	writeControl_(t, dict, "write"),
	foPtr_(functionObject::New(name, t, dict_))
{
	readControls();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::functionObjects::timeControl::execute()
{
	if (active() && (postProcess || executeControl_.execute()))
	{
		foPtr_->execute();
	}

	return true;
}


bool tnbLib::functionObjects::timeControl::write()
{
	if (active() && (postProcess || writeControl_.execute()))
	{
		foPtr_->write();
	}

	return true;
}


bool tnbLib::functionObjects::timeControl::end()
{
	if (active() && (executeControl_.execute() || writeControl_.execute()))
	{
		foPtr_->end();
	}

	return true;
}



tnbLib::scalar tnbLib::functionObjects::timeControl::timeToNextWrite()
{
	if
		(
			active()
			&& writeControl_.control() ==
			tnbLib::timeControl::timeControls::adjustableRunTime
			)
	{
		const label  writeTimeIndex = writeControl_.executionIndex();
		const scalar writeInterval = writeControl_.interval();

		return
			max
			(
				0.0,
				(writeTimeIndex + 1)*writeInterval
				- (time_.value() - time_.startTime().value())
			);
	}

	return vGreat;
}


bool tnbLib::functionObjects::timeControl::read
(
	const dictionary& dict
)
{
	if (dict != dict_)
	{
		dict_ = dict;

		writeControl_.read(dict);
		executeControl_.read(dict);
		readControls();

		return true;
	}
	else
	{
		return false;
	}
}


void tnbLib::functionObjects::timeControl::updateMesh
(
	const mapPolyMesh& mpm
)
{
	if (active())
	{
		foPtr_->updateMesh(mpm);
	}
}


void tnbLib::functionObjects::timeControl::movePoints
(
	const polyMesh& mesh
)
{
	if (active())
	{
		foPtr_->movePoints(mesh);
	}
}


// ************************************************************************* //