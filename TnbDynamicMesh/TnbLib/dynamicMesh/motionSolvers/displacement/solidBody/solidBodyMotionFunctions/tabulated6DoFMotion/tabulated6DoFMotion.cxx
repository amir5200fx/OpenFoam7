#include <tabulated6DoFMotion.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <Tuple2.hxx>
#include <IFstream.hxx>
#include <interpolateSplineXY.hxx>
#include <mathematicalConstants.hxx>

using namespace tnbLib::constant::mathematical;

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace solidBodyMotionFunctions
	{
		defineTypeNameAndDebug(tabulated6DoFMotion, 0);
		addToRunTimeSelectionTable
		(
			solidBodyMotionFunction,
			tabulated6DoFMotion,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::solidBodyMotionFunctions::tabulated6DoFMotion::tabulated6DoFMotion
(
	const dictionary& SBMFCoeffs,
	const Time& runTime
)
	:
	solidBodyMotionFunction(SBMFCoeffs, runTime)
{
	read(SBMFCoeffs);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::solidBodyMotionFunctions::tabulated6DoFMotion::~tabulated6DoFMotion()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

tnbLib::septernion
tnbLib::solidBodyMotionFunctions::tabulated6DoFMotion::transformation() const
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

	translationRotationVectors TRV = interpolateSplineXY
	(
		t,
		times_,
		values_
	);

	// Convert the rotational motion from deg to rad
	TRV[1] *= pi / 180.0;

	quaternion R(quaternion::XYZ, TRV[1]);
	septernion TR(septernion(-CofG_ + -TRV[0])*R*septernion(CofG_));

	DebugInFunction << "Time = " << t << " transformation: " << TR << endl;

	return TR;
}


bool tnbLib::solidBodyMotionFunctions::tabulated6DoFMotion::read
(
	const dictionary& SBMFCoeffs
)
{
	solidBodyMotionFunction::read(SBMFCoeffs);

	// If the timeDataFileName has changed read the file

	fileName newTimeDataFileName
	(
		fileName(SBMFCoeffs_.lookup("timeDataFileName")).expand()
	);

	if (newTimeDataFileName != timeDataFileName_)
	{
		timeDataFileName_ = newTimeDataFileName;

		IFstream dataStream(timeDataFileName_);

		if (dataStream.good())
		{
			List<Tuple2<scalar, translationRotationVectors>> timeValues
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

	SBMFCoeffs_.lookup("CofG") >> CofG_;

	return true;
}


// ************************************************************************* //