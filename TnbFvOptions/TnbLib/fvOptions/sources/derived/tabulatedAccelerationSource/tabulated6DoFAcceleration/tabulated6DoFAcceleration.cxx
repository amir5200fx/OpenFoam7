#include <tabulated6DoFAcceleration.hxx>

#include <Tuple2.hxx>
#include <IFstream.hxx>
#include <interpolateSplineXY.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(tabulated6DoFAcceleration, 0);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::tabulated6DoFAcceleration::tabulated6DoFAcceleration
(
	const dictionary& accelerationCoeffs,
	const Time& runTime
)
	:
	time_(runTime),
	accelerationCoeffs_(accelerationCoeffs)
{
	read(accelerationCoeffs);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::tabulated6DoFAcceleration::~tabulated6DoFAcceleration()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

tnbLib::tabulated6DoFAcceleration::accelerationVectors
tnbLib::tabulated6DoFAcceleration::acceleration() const
{
	scalar t = time_.value();

	if (t < times_[0])
	{
		FatalErrorInFunction
			<< "current time (" << t
			<< ") is less than the minimum in the data table ("
			<< times_[0] << ')'
			<< exit(FatalError);
	}

	if (t > times_.last())
	{
		FatalErrorInFunction
			<< "current time (" << t
			<< ") is greater than the maximum in the data table ("
			<< times_.last() << ')'
			<< exit(FatalError);
	}

	accelerationVectors avs = interpolateSplineXY
	(
		t,
		times_,
		values_
	);

	InfoInFunction
		<< "Time = " << t << " accelerations: " << avs << endl;

	return avs;
}


bool tnbLib::tabulated6DoFAcceleration::read
(
	const dictionary& accelerationCoeffs
)
{
	accelerationCoeffs_ = accelerationCoeffs;

	// If the timeDataFileName has changed read the file

	fileName newTimeDataFileName
	(
		fileName(accelerationCoeffs_.lookup("timeDataFileName")).expand()
	);

	if (newTimeDataFileName != timeDataFileName_)
	{
		timeDataFileName_ = newTimeDataFileName;

		IFstream dataStream(timeDataFileName_);

		if (dataStream.good())
		{
			List<Tuple2<scalar, accelerationVectors>> timeValues
			(
				dataStream
			);

			times_.setSize(timeValues.size());
			values_.setSize(timeValues.size());

			forAll(timeValues, i)
			{
				times_[i] = timeValues[i].first();
				values_[i] = timeValues[i].second();
			}
		}
		else
		{
			FatalErrorInFunction
				<< "Cannot open time data file " << timeDataFileName_
				<< exit(FatalError);
		}
	}

	return true;
}


// ************************************************************************* //