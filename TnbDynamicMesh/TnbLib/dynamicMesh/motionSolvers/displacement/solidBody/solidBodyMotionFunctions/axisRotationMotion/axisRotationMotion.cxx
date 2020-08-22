#include <axisRotationMotion.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <unitConversion.hxx>

using namespace tnbLib::constant::mathematical;

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace solidBodyMotionFunctions
	{
		defineTypeNameAndDebug(axisRotationMotion, 0);
		addToRunTimeSelectionTable
		(
			solidBodyMotionFunction,
			axisRotationMotion,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::solidBodyMotionFunctions::axisRotationMotion::axisRotationMotion
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

tnbLib::solidBodyMotionFunctions::axisRotationMotion::~axisRotationMotion()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

tnbLib::septernion
tnbLib::solidBodyMotionFunctions::axisRotationMotion::transformation() const
{
	scalar t = time_.value();

	// Rotation origin (in radians)
	vector omega
	(
		t*degToRad(radialVelocity_.x()),
		t*degToRad(radialVelocity_.y()),
		t*degToRad(radialVelocity_.z())
	);

	scalar magOmega = mag(omega);
	quaternion R(omega / magOmega, magOmega);
	septernion TR(septernion(-origin_)*R*septernion(origin_));

	DebugInFunction << "Time = " << t << " transformation: " << TR << endl;

	return TR;
}


bool tnbLib::solidBodyMotionFunctions::axisRotationMotion::read
(
	const dictionary& SBMFCoeffs
)
{
	solidBodyMotionFunction::read(SBMFCoeffs);

	SBMFCoeffs_.lookup("origin") >> origin_;
	SBMFCoeffs_.lookup("radialVelocity") >> radialVelocity_;

	return true;
}


// ************************************************************************* //