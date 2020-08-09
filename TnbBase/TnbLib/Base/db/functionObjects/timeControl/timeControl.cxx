#include <timeControl.hxx>

#include <PstreamReduceOps.hxx>

// * * * * * * * * * * * * * Static Member Data  * * * * * * * * * * * * * * //

namespace tnbLib
{
	template<>
	const char* NamedEnum<timeControl::timeControls, 8>::
		names[] =
	{
		"timeStep",
		"writeTime",
		"outputTime",
		"adjustableRunTime",
		"runTime",
		"clockTime",
		"cpuTime",
		"none"
	};
}

const tnbLib::NamedEnum<tnbLib::timeControl::timeControls, 8>
tnbLib::timeControl::timeControlNames_;


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::timeControl::timeControl
(
	const Time& t,
	const dictionary& dict,
	const word& prefix
)
	:
	time_(t),
	prefix_(prefix),
	timeControl_(timeControls::timeStep),
	intervalSteps_(0),
	interval_(-1),
	executionIndex_(0)
{
	read(dict);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::timeControl::~timeControl()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::timeControl::read(const dictionary& dict)
{
	word controlName(prefix_ + "Control");
	word intervalName(prefix_ + "Interval");

	// For backward compatibility support the deprecated 'outputControl' option
	// now superseded by 'writeControl' for compatibility with Time
	if (prefix_ == "write" && dict.found("outputControl"))
	{
		IOWarningInFunction(dict)
			<< "Using deprecated 'outputControl'" << nl
			<< "    Please use 'writeControl' with 'writeInterval'"
			<< endl;

		// Change to the old names for this option
		controlName = "outputControl";
		intervalName = "outputInterval";
	}

	if (dict.found(controlName))
	{
		timeControl_ = timeControlNames_.read(dict.lookup(controlName));
	}
	else
	{
		timeControl_ = timeControls::timeStep;
	}

	switch (timeControl_)
	{
	case timeControls::timeStep:
	{
		intervalSteps_ = dict.lookupOrDefault<label>(intervalName, 0);
		break;
	}

	case timeControls::writeTime:
	case timeControls::outputTime:
	{
		intervalSteps_ = dict.lookupOrDefault<label>(intervalName, 1);
		break;
	}

	case timeControls::clockTime:
	case timeControls::runTime:
	case timeControls::cpuTime:
	case timeControls::adjustableRunTime:
	{
		interval_ = readScalar(dict.lookup(intervalName));
		break;
	}

	default:
	{
		break;
	}
	}
}


bool tnbLib::timeControl::execute()
{
	switch (timeControl_)
	{
	case timeControls::timeStep:
	{
		return
			(
			(intervalSteps_ <= 1)
				|| !(time_.timeIndex() % intervalSteps_)
				);
		break;
	}

	case timeControls::writeTime:
	case timeControls::outputTime:
	{
		if (time_.writeTime())
		{
			executionIndex_++;
			return !(executionIndex_ % intervalSteps_);
		}
		break;
	}

	case timeControls::runTime:
	case timeControls::adjustableRunTime:
	{
		label executionIndex = label
		(
			(
			(time_.value() - time_.startTime().value())
				+ 0.5*time_.deltaTValue()
				)
			/ interval_
		);

		if (executionIndex > executionIndex_)
		{
			executionIndex_ = executionIndex;
			return true;
		}
		break;
	}

	case timeControls::cpuTime:
	{
		label executionIndex = label
		(
			returnReduce(time_.elapsedCpuTime(), maxOp<double>())
			/ interval_
		);
		if (executionIndex > executionIndex_)
		{
			executionIndex_ = executionIndex;
			return true;
		}
		break;
	}

	case timeControls::clockTime:
	{
		label executionIndex = label
		(
			returnReduce(label(time_.elapsedClockTime()), maxOp<label>())
			/ interval_
		);
		if (executionIndex > executionIndex_)
		{
			executionIndex_ = executionIndex;
			return true;
		}
		break;
	}

	case timeControls::none:
	{
		return false;
	}

	default:
	{
		FatalErrorInFunction
			<< "Undefined output control: "
			<< timeControlNames_[timeControl_] << nl
			<< abort(FatalError);
		break;
	}
	}

	return false;
}


// ************************************************************************* //