#include <oscillatingLinearMotion.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace solidBodyMotionFunctions
	{
		defineTypeNameAndDebug(oscillatingLinearMotion, 0);
		addToRunTimeSelectionTable
		(
			solidBodyMotionFunction,
			oscillatingLinearMotion,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::solidBodyMotionFunctions::oscillatingLinearMotion::oscillatingLinearMotion
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

tnbLib::solidBodyMotionFunctions::oscillatingLinearMotion::
~oscillatingLinearMotion()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

tnbLib::septernion
tnbLib::solidBodyMotionFunctions::oscillatingLinearMotion::transformation() const
{
	scalar t = time_.value();

	const vector displacement = amplitude_ * sin(omega_*t);

	quaternion R(1);
	septernion TR(septernion(-displacement)*R);

	DebugInFunction << "Time = " << t << " transformation: " << TR << endl;

	return TR;
}


bool tnbLib::solidBodyMotionFunctions::oscillatingLinearMotion::read
(
	const dictionary& SBMFCoeffs
)
{
	solidBodyMotionFunction::read(SBMFCoeffs);

	SBMFCoeffs_.lookup("amplitude") >> amplitude_;
	SBMFCoeffs_.lookup("omega") >> omega_;

	return true;
}


// ************************************************************************* //