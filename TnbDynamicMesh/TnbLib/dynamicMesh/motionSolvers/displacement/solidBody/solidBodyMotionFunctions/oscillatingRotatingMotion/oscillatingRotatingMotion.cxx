#include <oscillatingRotatingMotion.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <mathematicalConstants.hxx>

using namespace tnbLib::constant::mathematical;

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace solidBodyMotionFunctions
	{
		defineTypeNameAndDebug(oscillatingRotatingMotion, 0);
		addToRunTimeSelectionTable
		(
			solidBodyMotionFunction,
			oscillatingRotatingMotion,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::solidBodyMotionFunctions::oscillatingRotatingMotion::
oscillatingRotatingMotion
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

tnbLib::solidBodyMotionFunctions::oscillatingRotatingMotion::
~oscillatingRotatingMotion()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

tnbLib::septernion
tnbLib::solidBodyMotionFunctions::oscillatingRotatingMotion::
transformation() const
{
	scalar t = time_.value();

	vector eulerAngles = amplitude_ * sin(omega_*t);

	// Convert the rotational motion from deg to rad
	eulerAngles *= pi / 180.0;

	quaternion R(quaternion::XYZ, eulerAngles);
	septernion TR(septernion(-origin_)*R*septernion(origin_));

	DebugInFunction << "Time = " << t << " transformation: " << TR << endl;

	return TR;
}


bool tnbLib::solidBodyMotionFunctions::oscillatingRotatingMotion::read
(
	const dictionary& SBMFCoeffs
)
{
	solidBodyMotionFunction::read(SBMFCoeffs);

	SBMFCoeffs_.lookup("origin") >> origin_;
	SBMFCoeffs_.lookup("amplitude") >> amplitude_;
	SBMFCoeffs_.lookup("omega") >> omega_;

	return true;
}


// ************************************************************************* //