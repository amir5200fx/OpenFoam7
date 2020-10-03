#include <fieldAverage.hxx>

#include <volFields.hxx>
#include <fieldAverageItem.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(fieldAverage, 0);
		addToRunTimeSelectionTable(functionObject, fieldAverage, dictionary);
	}
}


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void tnbLib::functionObjects::fieldAverage::resetFields()
{
	forAll(faItems_, i)
	{
		if (faItems_[i].mean())
		{
			if (obr_.found(faItems_[i].meanFieldName()))
			{
				obr_.checkOut(*obr_[faItems_[i].meanFieldName()]);
			}
		}

		if (faItems_[i].prime2Mean())
		{
			if (obr_.found(faItems_[i].prime2MeanFieldName()))
			{
				obr_.checkOut(*obr_[faItems_[i].prime2MeanFieldName()]);
			}
		}
	}
}


void tnbLib::functionObjects::fieldAverage::initialize()
{
	if (!totalIter_.size())
	{
		totalIter_.setSize(faItems_.size(), 1);
	}

	if (!totalTime_.size())
	{
		totalTime_.setSize(faItems_.size(), obr_.time().deltaTValue());
	}
	else
	{
		// Check if totalTime_ has been set otherwise initialize
		forAll(totalTime_, fieldi)
		{
			if (totalTime_[fieldi] < 0)
			{
				totalTime_[fieldi] = obr_.time().deltaTValue();
			}
		}
	}

	resetFields();

	// Add mean fields to the field lists
	forAll(faItems_, fieldi)
	{
		addMeanField<scalar>(fieldi);
		addMeanField<vector>(fieldi);
		addMeanField<sphericalTensor>(fieldi);
		addMeanField<symmTensor>(fieldi);
		addMeanField<tensor>(fieldi);
	}

	// Add prime-squared mean fields to the field lists
	forAll(faItems_, fieldi)
	{
		addPrime2MeanField<scalar, scalar>(fieldi);
		addPrime2MeanField<vector, symmTensor>(fieldi);
	}

	// ensure first averaging works unconditionally
	prevTimeIndex_ = -1;

	initialised_ = true;
}


void tnbLib::functionObjects::fieldAverage::restart()
{
	TnbLog << "    Restarting averaging at time " << obr_.time().timeName()
		<< nl << endl;

	totalIter_.clear();
	totalTime_.clear();

	initialize();
}


void tnbLib::functionObjects::fieldAverage::calcAverages()
{
	if (!initialised_)
	{
		initialize();
	}

	const label currentTimeIndex = obr_.time().timeIndex();
	const scalar currentTime = obr_.time().value();

	if (prevTimeIndex_ == currentTimeIndex)
	{
		return;
	}
	else
	{
		prevTimeIndex_ = currentTimeIndex;
	}

	if (periodicRestart_ && currentTime > restartPeriod_*periodIndex_)
	{
		restart();
		periodIndex_++;
	}

	TnbLog << type() << " " << name() << " write:" << nl
		<< "    Calculating averages" << nl;

	addMeanSqrToPrime2Mean<scalar, scalar>();
	addMeanSqrToPrime2Mean<vector, symmTensor>();

	calculateMeanFields<scalar>();
	calculateMeanFields<vector>();
	calculateMeanFields<sphericalTensor>();
	calculateMeanFields<symmTensor>();
	calculateMeanFields<tensor>();

	calculatePrime2MeanFields<scalar, scalar>();
	calculatePrime2MeanFields<vector, symmTensor>();

	forAll(faItems_, fieldi)
	{
		totalIter_[fieldi]++;
		totalTime_[fieldi] += obr_.time().deltaTValue();
	}

	TnbLog << endl;
}


void tnbLib::functionObjects::fieldAverage::writeAverages() const
{
	TnbLog << "    Writing average fields" << endl;

	writeFields<scalar>();
	writeFields<vector>();
	writeFields<sphericalTensor>();
	writeFields<symmTensor>();
	writeFields<tensor>();

	TnbLog << endl;
}


void tnbLib::functionObjects::fieldAverage::writeAveragingProperties() const
{
	IOdictionary propsDict
	(
		IOobject
		(
			name() + "Properties",
			obr_.time().timeName(),
			"uniform",
			obr_,
			IOobject::NO_READ,
			IOobject::NO_WRITE,
			false
		)
	);

	forAll(faItems_, fieldi)
	{
		const word& fieldName = faItems_[fieldi].fieldName();
		propsDict.add(fieldName, dictionary());
		propsDict.subDict(fieldName).add("totalIter", totalIter_[fieldi]);
		propsDict.subDict(fieldName).add("totalTime", totalTime_[fieldi]);
	}

	propsDict.regIOobject::write();

	TnbLog << endl;
}


void tnbLib::functionObjects::fieldAverage::readAveragingProperties()
{
	if ((restartOnRestart_ || restartOnOutput_) && log)
	{
		Info << "    Starting averaging at time " << obr_.time().timeName()
			<< nl;
	}
	else
	{
		IOobject propsDictHeader
		(
			name() + "Properties",
			obr_.time().timeName(obr_.time().startTime().value()),
			"uniform",
			obr_,
			IOobject::MUST_READ_IF_MODIFIED,
			IOobject::NO_WRITE,
			false
		);

		if (!propsDictHeader.typeHeaderOk<IOdictionary>())
		{
			TnbLog << "    Starting averaging at time "
				<< obr_.time().timeName() << nl;

			return;
		}

		IOdictionary propsDict(propsDictHeader);

		TnbLog << "    Restarting averaging for fields:" << nl;

		totalIter_.setSize(faItems_.size(), 1);

		// Initialize totalTime with negative values
		// to indicate that it has not been set
		totalTime_.setSize(faItems_.size(), -1);

		forAll(faItems_, fieldi)
		{
			const word& fieldName = faItems_[fieldi].fieldName();
			if (propsDict.found(fieldName))
			{
				dictionary fieldDict(propsDict.subDict(fieldName));

				totalIter_[fieldi] = readLabel(fieldDict.lookup("totalIter"));
				totalTime_[fieldi] = readScalar(fieldDict.lookup("totalTime"));

				TnbLog << "        " << fieldName
					<< " iters = " << totalIter_[fieldi]
					<< " time = " << totalTime_[fieldi] << nl;
			}
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::fieldAverage::fieldAverage
(
	const word& name,
	const Time& runTime,
	const dictionary& dict
)
	:
	fvMeshFunctionObject(name, runTime, dict),
	prevTimeIndex_(-1),
	restartOnRestart_(false),
	restartOnOutput_(false),
	periodicRestart_(false),
	restartPeriod_(great),
	initialised_(false),
	faItems_(),
	totalIter_(),
	totalTime_(),
	periodIndex_(1)
{
	read(dict);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObjects::fieldAverage::~fieldAverage()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::functionObjects::fieldAverage::read(const dictionary& dict)
{
	fvMeshFunctionObject::read(dict);

	initialised_ = false;

	TnbLog << type() << " " << name() << ":" << nl;

	dict.readIfPresent("restartOnRestart", restartOnRestart_);
	dict.readIfPresent("restartOnOutput", restartOnOutput_);
	dict.readIfPresent("periodicRestart", periodicRestart_);
	dict.lookup("fields") >> faItems_;

	if (periodicRestart_)
	{
		dict.lookup("restartPeriod") >> restartPeriod_;
	}

	readAveragingProperties();

	TnbLog << endl;

	return true;
}


bool tnbLib::functionObjects::fieldAverage::execute()
{
	calcAverages();

	return true;
}


bool tnbLib::functionObjects::fieldAverage::write()
{
	writeAverages();
	writeAveragingProperties();

	if (restartOnOutput_)
	{
		restart();
	}

	return true;
}


// ************************************************************************* //