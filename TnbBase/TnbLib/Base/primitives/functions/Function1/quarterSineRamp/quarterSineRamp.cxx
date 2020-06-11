#include <quarterSineRamp.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace Function1Types
	{
		makeScalarFunction1(quarterSineRamp);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::Function1Types::quarterSineRamp::quarterSineRamp
(
	const word& entryName,
	const dictionary& dict
)
	:
	ramp(entryName, dict)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::Function1Types::quarterSineRamp::~quarterSineRamp()
{}


// ************************************************************************* //