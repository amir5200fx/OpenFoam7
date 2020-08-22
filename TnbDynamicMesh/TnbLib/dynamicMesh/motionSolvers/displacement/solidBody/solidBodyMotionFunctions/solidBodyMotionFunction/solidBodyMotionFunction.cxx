#include <solidBodyMotionFunction.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(solidBodyMotionFunction, 0);
	defineRunTimeSelectionTable(solidBodyMotionFunction, dictionary);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::solidBodyMotionFunction::solidBodyMotionFunction
(
	const dictionary& SBMFCoeffs,
	const Time& runTime
)
	:
	SBMFCoeffs_
	(
		SBMFCoeffs.optionalSubDict
		(
			word(SBMFCoeffs.lookup("solidBodyMotionFunction")) + "Coeffs"
		)
	),
	time_(runTime)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::solidBodyMotionFunction::~solidBodyMotionFunction()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool tnbLib::solidBodyMotionFunction::read(const dictionary& SBMFCoeffs)
{
	SBMFCoeffs_ = SBMFCoeffs.optionalSubDict(type() + "Coeffs");

	return true;
}


void tnbLib::solidBodyMotionFunction::writeData(Ostream& os) const
{
	os << SBMFCoeffs_;
}


// ************************************************************************* //