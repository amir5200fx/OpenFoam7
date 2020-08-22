#include <rotatingMotion.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <mathematicalConstants.hxx>

using namespace tnbLib::constant::mathematical;

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace solidBodyMotionFunctions
	{
		defineTypeNameAndDebug(rotatingMotion, 0);
		addToRunTimeSelectionTable
		(
			solidBodyMotionFunction,
			rotatingMotion,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::solidBodyMotionFunctions::rotatingMotion::rotatingMotion
(
	const dictionary& SBMFCoeffs,
	const Time& runTime
)
	:
	solidBodyMotionFunction(SBMFCoeffs, runTime),
	origin_(SBMFCoeffs_.lookup("origin")),
	axis_(SBMFCoeffs_.lookup("axis")),
	omega_(Function1<scalar>::New("omega", SBMFCoeffs_))
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::solidBodyMotionFunctions::rotatingMotion::~rotatingMotion()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

tnbLib::septernion
tnbLib::solidBodyMotionFunctions::rotatingMotion::transformation() const
{
	scalar t = time_.value();

	// Rotation around axis
	scalar angle = omega_->integrate(0, t);

	quaternion R(axis_, angle);
	septernion TR(septernion(-origin_)*R*septernion(origin_));

	DebugInFunction << "Time = " << t << " transformation: " << TR << endl;

	return TR;
}


bool tnbLib::solidBodyMotionFunctions::rotatingMotion::read
(
	const dictionary& SBMFCoeffs
)
{
	solidBodyMotionFunction::read(SBMFCoeffs);

	omega_.reset
	(
		Function1<scalar>::New("omega", SBMFCoeffs_).ptr()
	);

	return true;
}


// ************************************************************************* //