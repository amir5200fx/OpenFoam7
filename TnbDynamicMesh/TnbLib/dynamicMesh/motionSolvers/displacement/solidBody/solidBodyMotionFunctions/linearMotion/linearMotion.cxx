#include <linearMotion.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace solidBodyMotionFunctions
	{
		defineTypeNameAndDebug(linearMotion, 0);
		addToRunTimeSelectionTable
		(
			solidBodyMotionFunction,
			linearMotion,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::solidBodyMotionFunctions::linearMotion::linearMotion
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

tnbLib::solidBodyMotionFunctions::linearMotion::~linearMotion()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

tnbLib::septernion
tnbLib::solidBodyMotionFunctions::linearMotion::transformation() const
{
	scalar t = time_.value();

	// Translation of centre of gravity with constant velocity
	const vector displacement = velocity_ * t;

	quaternion R(1);
	septernion TR(septernion(-displacement)*R);

	DebugInFunction << "Time = " << t << " transformation: " << TR << endl;

	return TR;
}


bool tnbLib::solidBodyMotionFunctions::linearMotion::read
(
	const dictionary& SBMFCoeffs
)
{
	solidBodyMotionFunction::read(SBMFCoeffs);

	SBMFCoeffs_.lookup("velocity") >> velocity_;

	return true;
}


// ************************************************************************* //